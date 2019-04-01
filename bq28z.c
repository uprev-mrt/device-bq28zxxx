/**
  *@file bq28z.c
  *@brief driver for bq28zxx fueld gauge
  *@author
  *@date 03/25/2019
  */

#include "bq28z.h"

#define DESIGN_CAPACITY 5400 // mAh
#define TERMINATE_VOLTAGE 3000 // mV
#define CHG_TERM_VOLTAGE 4200
#define DESIGN_ENERGY 19510 // mWh
#define CC_OFFSET -1376 // mV

static mrt_i2c_handle_t handle= 0; 
static OsiLockObj_t    _fgLock;
static BatteryModes    _fgLastMode = BATTERY_GOOD; 
static uint16_t _fgLastPct = 0;
static uint8_t _designCap = 0;
static uint8_t _termVoltage = 0; 
static uint8_t _designNrg = 0; 
static uint8_t _VChgTerm = 0;
#define SWAP16(x) ( (0xFF00 & ((x) << 8)) | (0xFF & ((x) >> 8)))

#define LED_TEST_FLASH_MS 400

#define CMD_CTL       0x00//01
#define CMD_TEMP      0x02//03
#define CMD_VOLTS     0x04//05
#define CMD_FLAGS     0x06//07
#define CMD_NAC       0x08//09
#define CMD_FAC       0x0A//0B
#define CMD_REMC      0x0C//0D
#define CMD_FCC       0x0E//0F
#define CMD_AVG_C     0x10//11
#define CMD_AVG_P     0x18//19
#define CMD_SOC       0x1C//1D
#define CMD_INT_TEMP  0x1E//1F
#define CMD_SOH       0x20//21
#define CMD_OP_CFG    0x3A//3B
#define CMD_DES_CAP   0x3C//3D

#define CMD_DATA_CLASS    0x3E
#define CMD_DATA_BLOCK    0x3F
#define CMD_DATA_CHKSUM   0x60
#define CMD_DATA_CTL      0x61

#define CMD_BLOCK_DATA_BASE 0x40
// Offsets into State block (82)
#define DESIGN_CAP_OFFSET 12
#define TERM_VOLTAGE_OFFSET 18
#define DESIGN_NRG_OFFSET 14
#define V_CHG_TERM_OFFSET (36%32) // I2 Def 4190
// Offsets into CC Data block (104)
#define CAL_CC_OFFSET_OFFSET 0
#define CAL_BOARD_OFFSET     2
#define CAL_INT_TEMP_OFFSET  3
#define CAL_PACK_V_OFFSET_OFFSET 4
#define CAL_BLOCK_SIZE 32

// Sub-commands are 0x00XX, but since they need to be sent LSB first,
// and all have MSB=0, only defining LSB, will insert MSB in FgControlCmd()
#define SC_CTL_STAT 0x00
#define SC_DEV_TYPE 0x01
#define SC_FW_VER   0x02
#define SC_CFGUPD   0x13
#define SC_RESET    0x41
#define SC_SOFT_RESET 0x42

// Data Block SubClass IDs
#define DB_SCID_STATE 82
#define DB_SCID_CAL_DATA 104
#define DB_SEALED_KEY 112
//**************************************************************************
// Structs
//**************************************************************************
// The first 32-byte block of Gas Gauging Data Block Subclass ID 82 (0x52)
typedef struct
{
  uint8_t unused1[2]; // 0-1
  uint8_t updateStatus; // 2
  uint8_t resCap; // 3-4
  uint16_t opCfg; // 5-6
  uint8_t unused2[5]; // 7-11
  uint8_t designCap; // 12-13
  uint8_t designNRG; // 14-15
  uint8_t unused3[2]; // 16-17
  uint8_t termVoltage; // 18-19
  uint8_t unused4[2]; // 20-21
  uint8_t SOHLoadl; // 22-23
  uint8_t unused5[5]; // 24-28
  uint8_t SOCIDelta; // 29
  uint8_t taperCurrent; // 30-31
} NvmState1;

// Enter ROM Mode
#define ROM_MODE_I2C_ADDR 0x0B
// Write 0xF000 to REG 0x00 to enter ROM mode
// To confirm, read at 0xCC (should fail), read at 0x0B should pass)


//****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS                          
//****************************************************************************
bool FgControlCmd(uint8_t subCmd, uint8_t* pRx, uint8_t rxSize);
bool FgWriteRead(uint8_t* pTx, uint8_t txLen, uint8_t* pRx, uint8_t rxLen);
bool FgReadNvmState1(uint8_t* pData, uint8_t* pChkSum);
bool FgReadNvmState2(uint8_t* pData, uint8_t* pChkSum);
bool FgReadCalData(uint8_t* pData, uint8_t* pChkSum);
bool FgUnsealCmd();

/**
  *@brief read registers from device
  *@param dev ptr to device
  *@param regAddr address of register
  *@param data ptr to data to store data
  *@param len length in bytes of data
  */
static mrt_i2c_status_t bq28z_read_regs(bq28z_t* dev, uint16_t regAddr, uint8_t* data, int len)
{

  MRT_I2C_MEM_READ(dev->mI2c, BQ28Z_I2C_ADDR, regAddr, BQ28Z_REGADDR_SIZE, data, len, 100 );

  return MRT_STATUS_OK;
}

/**
  *@brief write registers to device
  *@param dev ptr to device
  *@param regAddr address of register
  *@param data ptr to data to write
  *@param len length in bytes of data
  */
static mrt_i2c_status_t bq28z_write_regs(bq28z_t* dev, uint16_t regAddr,const uint8_t* data, int len)
{
  MRT_I2C_MEM_WRITE(dev->mI2c, BQ28Z_I2C_ADDR, regAddr, BQ28Z_REGADDR_SIZE, data, len, 100 );

  return MRT_STATUS_OK;
}

mrt_status_t bq28z_init(bq28z_t* dev, mrt_i2c_handle_t handle)
{
  //set handle for i2c
  dev->mI2c = handle;

  return MRT_STATUS_OK;
}


bool FgBatteryIsAlarmMode()
{
  return ((FgBatteryStatus(TRUE) == BATTERY_VERY_LOW) || (FgBatteryStatus(TRUE) == BATTERY_MISSING) || (FgBatteryStatus(TRUE) == BATTERY_CRITICAL));
}

// Used by processes other than MainTask() so the fuel gauge is not 
// read by multiple tasks
BatteryModes FgLastBatteryStatus()
{
  return _fgLastMode;
}

uint8_t FgLastBatteryPct()
{
  return _fgLastPct;
}
bool I2C_transfer(mrt_i2c_handle_t handle, I2C_Transaction *transaction)
{
  return true; 
}
BatteryModes FgBatteryStatus(bool useCachedVal)
{
  BatteryModes mode = BATTERY_GOOD;

  if (Gpio_BatteryCharging())
    mode = BATTERY_CHARGING;
  // If requesting a new reading
  if (!useCachedVal)
    _fgLastPct = FgPercentCharged();

  if (mode != BATTERY_CHARGING)
  {
    //DebugConsoleOutV("Battery is %d%%%% charged\r", battPct);
    // set red/green based on charge %
    //#warn "Undo Battery Patch"
    if (_fgLastPct > BATTERY_LOW_PCT)
    {
      mode = BATTERY_GOOD;
    }
   
    else if ((_fgLastPct > BATTERY_CRITICAL_PCT) && (_fgLastPct <= BATTERY_LOW_PCT)) // 11-20%
    {
      mode = BATTERY_LOW;
    }
    else //if (_fgLastPct <= BATTERY_CRITICAL_PCT) //&& include 0 (_fgLastPct == 0)) // 0-10%
    {
      mode = BATTERY_CRITICAL;
    }
   
  } // battery LED logic
  // Never let it be zero
  _fgLastMode = mode;
  return mode;
}


void FgTest(int val)
{
  testMode = val;
  DebugConsoleOutV("Fuel Gauge Test Mode: %d\r", testMode);
}

uint8_t CalcCheckSum(uint8_t* data, uint8_t len)
{
  int i = 0;
  uint8_t chkSum = 0;
  for (i = 0; i < len; i++)
  {
    chkSum += data[i];
  }
  chkSum = 0xFF - chkSum;
  return chkSum;
}

//****************************************************************************
//
//! Initialize the device with defaults
//!
//! \param None
//!
//! This function
//!    1. Reads the CHIP ID.
//!
//! \return 0: Success, < 0: Failure.
//
//****************************************************************************

bool FuelGaugeOpen(mrt_i2c_handle_t handle, bool doConfig)
{
  uint8_t pData[32];
  mrt_i2c_handle_t _handle; 
  unsigned char txData[2], rxData[4];
  memset(pData, 0, 32);
  memset(rxData, 0, 4);
  int needsReset = 0;
  uint8_t chkSum;
  //save handle
  _handle = handle;
  // Create the thread safe lock
  osi_LockObjCreate(&_fgLock);


  //if (FgControlCmd(SC_DEV_TYPE, rxData, 2))
  //{
  //  DebugConsoleOutV("BQ27425 Type: 0x%02X%02X\r", rxData[1], rxData[0]);
  //}
  //if (FgControlCmd(SC_FW_VER, rxData, 2))
  //{
  //  DebugConsoleOutV("Fuel Gauge BQ27425 FW: %02X.%02X\r", rxData[1], rxData[0]);
  //}
  //FgReadKey(pData);
  //DebugConsoleOutV("BQ27425 KEY: %02X,%02X,%02X,%02X\r", pData[0], pData[1], pData[2], pData[3]);
  //FgUnsealCmd();


  if (FgReadNvmState1(pData, &chkSum))
  {
    //DebugConsoleOutV("FG: Read CS: 0x%02X Calc CS: 0x%02X\r", chkSum, CalcCheckSum(pData, 32));

    _designCap = (pData[DESIGN_CAP_OFFSET] << 8) + pData[DESIGN_CAP_OFFSET + 1];
    _termVoltage = (pData[TERM_VOLTAGE_OFFSET] << 8) + pData[TERM_VOLTAGE_OFFSET + 1];
    _designNrg = (pData[DESIGN_NRG_OFFSET] << 8) + pData[DESIGN_NRG_OFFSET + 1];

    //DebugConsoleOutV("BQ27425 DC: %d mAh (0x%02X%02X), TV: %d mV (0x%02X%02X), NRG: %d mWh (0x%02X%02X)\r", 
    //  _designCap, pData[12], pData[13], 
    //  _termVoltage, pData[18], pData[19],
    //  _designNrg, pData[14], pData[15]);
    // If not already configured
    if (doConfig && ((_termVoltage != TERMINATE_VOLTAGE) || (_designCap != DESIGN_CAPACITY) || (_designNrg != DESIGN_ENERGY)))
    {
      needsReset = 1;
      // Set the design capacity to 3200 mAH (0x0C80)
      txData[0] = CMD_BLOCK_DATA_BASE + DESIGN_CAP_OFFSET;
      pData[DESIGN_CAP_OFFSET] = (uint8_t)((DESIGN_CAPACITY & 0xFF00) >> 8); // 0x0C;
      txData[1] = pData[DESIGN_CAP_OFFSET];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      txData[0] = CMD_BLOCK_DATA_BASE + DESIGN_CAP_OFFSET + 1;
      pData[DESIGN_CAP_OFFSET + 1] = (uint8_t)(DESIGN_CAPACITY & 0x00FF); // 0x80
      txData[1] = pData[DESIGN_CAP_OFFSET+1];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      // Set the terminate voltage to 3100 mV (0x0C1C)
      txData[0] = CMD_BLOCK_DATA_BASE + TERM_VOLTAGE_OFFSET;
      pData[TERM_VOLTAGE_OFFSET] = (uint8_t)((TERMINATE_VOLTAGE & 0xFF00) >> 8); // 0x0C;
      txData[1] = pData[TERM_VOLTAGE_OFFSET];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      txData[0] = CMD_BLOCK_DATA_BASE + TERM_VOLTAGE_OFFSET + 1;
      pData[TERM_VOLTAGE_OFFSET + 1] = (uint8_t)(TERMINATE_VOLTAGE & 0x00FF); // 0x1C
      txData[1] = pData[TERM_VOLTAGE_OFFSET + 1];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      // Set the Design Energy
      txData[0] = CMD_BLOCK_DATA_BASE + DESIGN_NRG_OFFSET;
      pData[DESIGN_NRG_OFFSET] = (uint8_t)((DESIGN_ENERGY & 0xFF00) >> 8); // 0x0C;
      txData[1] = pData[DESIGN_NRG_OFFSET];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      txData[0] = CMD_BLOCK_DATA_BASE + DESIGN_NRG_OFFSET + 1;
      pData[DESIGN_NRG_OFFSET + 1] = (uint8_t)(DESIGN_ENERGY & 0x00FF); // 0x1C
      txData[1] = pData[DESIGN_NRG_OFFSET + 1];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);

      // Update the checksum to commit the changes
      txData[0] = CMD_DATA_CHKSUM;
      txData[1] = CalcCheckSum(pData, 32);
      //DebugConsoleOutV("FG: Calc CS: 0x%02\r", txData[1]);
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(1000);
    }
  } // if read nvram
  // Read State block 2
  if (FgReadNvmState2(pData, &chkSum))
  {
    //DebugConsoleOutV("FG: Read2 CS: 0x%02X Calc CS: 0x%02X\r", chkSum, CalcCheckSum(pData, 32));

    _vChgTerm = (pData[V_CHG_TERM_OFFSET] << 8) + pData[V_CHG_TERM_OFFSET + 1];
    //DebugConsoleOutV("BQ27425 VTERM: %d (0x%02X%02X)\r",  _vChgTerm, pData[4], pData[5]);
    // If not already configured
    if (doConfig && (_vChgTerm != CHG_TERM_VOLTAGE))
    {
      needsReset = 1;
      txData[0] = CMD_BLOCK_DATA_BASE + V_CHG_TERM_OFFSET;
      pData[V_CHG_TERM_OFFSET] = (uint8_t)((CHG_TERM_VOLTAGE & 0xFF00) >> 8); // 0x0C;
      txData[1] = pData[V_CHG_TERM_OFFSET];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      txData[0] = CMD_BLOCK_DATA_BASE + V_CHG_TERM_OFFSET + 1;
      pData[V_CHG_TERM_OFFSET + 1] = (uint8_t)(CHG_TERM_VOLTAGE & 0x00FF); // 0x80
      txData[1] = pData[V_CHG_TERM_OFFSET + 1];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);

      // Update the checksum to commit the changes
      txData[0] = CMD_DATA_CHKSUM;
      txData[1] = CalcCheckSum(pData, 32);
      //DebugConsoleOutV("FG: Calc CS: 0x%02\r", txData[1]);
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(1000);
    }
  } // if read nvram

  // Set Cal Data values
  /*if (FgReadCalData(pData, &chkSum))
  {
    ccOffset = (pData[CAL_CC_OFFSET_OFFSET] << 8) + pData[CAL_CC_OFFSET_OFFSET + 1];
    DebugConsoleOutV("BQ27425 CC Offset: %d mV (0x%02X%02X), CS: 0x%02X, (Calc)CS: 0x%02X\r",
      ccOffset, pData[CAL_CC_OFFSET_OFFSET], pData[CAL_CC_OFFSET_OFFSET + 1], chkSum, CalcCheckSum(pData, CAL_BLOCK_SIZE));
    if (ccOffset != CC_OFFSET)
    {
      needsReset = 1;
      // Set the Design Energy
      txData[0] = CMD_BLOCK_DATA_BASE + CAL_CC_OFFSET_OFFSET;
      pData[CAL_CC_OFFSET_OFFSET] = (uint8_t)((CC_OFFSET & 0xFF00) >> 8); // 0x0C;
      txData[1] = pData[CAL_CC_OFFSET_OFFSET];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);
      txData[0] = CMD_BLOCK_DATA_BASE + CAL_CC_OFFSET_OFFSET + 1;
      pData[CAL_CC_OFFSET_OFFSET + 1] = (uint8_t)(CC_OFFSET & 0x00FF); // 0x1C
      txData[1] = pData[CAL_CC_OFFSET_OFFSET + 1];
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(100);

      // Update the checksum to commit the changes
      txData[0] = CMD_DATA_CHKSUM;
      txData[1] = CalcCheckSum(pData, CAL_BLOCK_SIZE);
      FgWriteRead(txData, 2, NULL, 0);
      osi_Sleep(1000);
      // Re-read to verify
      FgReadCalData(pData, &chkSum);
      ccOffset = (pData[CAL_CC_OFFSET_OFFSET] << 8) + pData[CAL_CC_OFFSET_OFFSET + 1];
      DebugConsoleOutV("Post SET: CC Offset: %d mV (0x%02X%02X)\r", ccOffset, pData[CAL_CC_OFFSET_OFFSET], pData[CAL_CC_OFFSET_OFFSET + 1]);
    }
  }
  */

  if (needsReset)
  {
    // Last, reset to come out of Cfg Update mode
    FgControlCmd(SC_SOFT_RESET, NULL, 0);
    osi_Sleep(3000); // wait for reset to complete
    // Re-read to verify write took
    FgReadNvmState1(pData, &chkSum);
    _designCap = (pData[DESIGN_CAP_OFFSET] << 8) + pData[DESIGN_CAP_OFFSET + 1];
    _termVoltage = (pData[TERM_VOLTAGE_OFFSET] << 8) + pData[TERM_VOLTAGE_OFFSET + 1];
    _designNrg = (pData[DESIGN_NRG_OFFSET] << 8) + pData[DESIGN_NRG_OFFSET + 1];

    DebugConsoleOutV("BQ28Z RECONFIG DC: %d mAh (0x%02X%02X), TV: %d mV (0x%02X%02X), NRG: %d mWh (0x%02X%02X)\r",
      _designCap, pData[12], pData[13],
      _termVoltage, pData[18], pData[19],
      _designNrg, pData[14], pData[15]);

    FgReadNvmState2(pData, &chkSum);
    _vChgTerm = (pData[V_CHG_TERM_OFFSET] << 8) + pData[V_CHG_TERM_OFFSET + 1];
    DebugConsoleOutV("BQ28Z VTERM: %d (0x%02X%02X)\r",   _vChgTerm, pData[4], pData[5]);

    // Re-read to verify
//    FgReadCalData(pData, &chkSum);
//    ccOffset = (pData[CAL_CC_OFFSET_OFFSET] << 8) + pData[CAL_CC_OFFSET_OFFSET + 1];
//    DebugConsoleOutV(", CC Offset: %d mV (0x%02X%02X)\r", ccOffset, pData[CAL_CC_OFFSET_OFFSET], pData[CAL_CC_OFFSET_OFFSET + 1]);
    // Last, reset to come out of Cfg Update mode
    FgControlCmd(SC_SOFT_RESET, NULL, 0);
  }
  return TRUE;
}

// returns 0 if in normal mode, 1 if in ROM mode
int GetROMMode()
{
  I2C_Transaction i2cTransaction;
  unsigned char tx[3];
  unsigned char rxData[2];
  memset(rxData, 0, 2);

  tx[0] = CMD_CTL;
  tx[1] = SC_DEV_TYPE;
  tx[2] = 0x00; // MSB of subCmd is always 0

  i2cTransaction.writeBuf = tx;
  i2cTransaction.writeCount = 3;
  i2cTransaction.readBuf = rxData;
  i2cTransaction.readCount = 0;
  i2cTransaction.slaveAddress = BQ28Z_I2C_ADDR;

  if (I2C_transfer(_handle, &i2cTransaction) != 0)
  {
    osi_Sleep(1000);
    // Now try to read
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = 2;

    if (I2C_transfer(_handle, &i2cTransaction) != 0)
    {
      DebugConsoleOutV("BQ27425 Type: 0x%02X%02X, Normal Mode\r", rxData[1], rxData[0]);
      return 0;
    }
  }
  // if got here, normal mode failed, try ROM mode read
  i2cTransaction.writeBuf = tx;
  i2cTransaction.writeCount = 3;
  i2cTransaction.readBuf = rxData;
  i2cTransaction.readCount = 0;
  i2cTransaction.slaveAddress = ROM_MODE_I2C_ADDR;
  if (I2C_transfer(_handle, &i2cTransaction) != 0)
  {
    osi_Sleep(1000);
    // Now try to read
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = 2;

    if (I2C_transfer(_hI2C, &i2cTransaction) != 0)
    {
      DebugConsoleOutV("BQ27425 Type: 0x%02X%02X, ROM Mode\r", rxData[1], rxData[0]);
      return 1;
    }
  }
  return -1;
} // GetROMMode()

bool EnableROMMode()
{
  I2C_Transaction i2cTransaction;
  unsigned char tx[4];
  char ch = ' ';
  if (GetROMMode() == 0)
  {
    // Write 0xF000 to REG 0x00

    tx[0] = CMD_CTL;
    tx[1] = 0x00;
    tx[2] = 0x00;
    tx[3] = 0xF0;

    i2cTransaction.writeBuf = &tx[1];
    i2cTransaction.writeCount = 3;
    i2cTransaction.readBuf = &ch;
    i2cTransaction.readCount = 0;
    i2cTransaction.slaveAddress = BQ28Z_I2C_ADDR;

    if (I2C_transfer(_handle, &i2cTransaction) != 0)
    {
      osi_Sleep(1000);
      return  GetROMMode() == 0;
    }
  }
  return false;
}

void WriteRom(unsigned char* pData, int len)
{
  I2C_Transaction i2cTransaction;
  char ch = ' ';
  i2cTransaction.writeBuf = pData;
  i2cTransaction.writeCount = len;
  i2cTransaction.readBuf = &ch;
  i2cTransaction.readCount = 0;
  i2cTransaction.slaveAddress = BQ28Z_I2C_ADDR; //ROM_MODE_I2C_ADDR;

  if (I2C_transfer(_handle, &i2cTransaction) == 0)
  {
    //DebugOut("FUEL GAUGE: CFG: WriteROM failed\r");
  }
  osi_Sleep(100);
}

int CompareRom(unsigned char reg, unsigned char* pData, int len)
{
  I2C_Transaction i2cTransaction;
  unsigned char tx[3];
  unsigned char rxData[10];
  memset(rxData, 0, 10);
  int i = 0;

  // Read the register from the device
  tx[0] = CMD_CTL;
  tx[1] = reg;
  tx[2] = 0x00; // MSB of subCmd is always 0

  i2cTransaction.writeBuf = tx;
  i2cTransaction.writeCount = 3;
  i2cTransaction.readBuf = rxData;
  i2cTransaction.readCount = 0;
  i2cTransaction.slaveAddress = BQ28Z_I2C_ADDR; //ROM_MODE_I2C_ADDR;

  // Read loaded reg
  if (reg == 0)
  {
    //DebugConsoleOutV("BQ27425 Comapare last REG\r");
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = len;
    if (I2C_transfer(_handle, &i2cTransaction) != 0)
    {
      // Compare 
      for (i = 0; i < len; i++)
      {
        if (pData[i] != rxData[i])
        {
          //DebugOut("FUEL GAUGE: CFG: Compare Fail idx[%d] src[%d], read[%d]\r", i, pData[i], rxData[i]);
          return 0;
        }
      }
      return 1;
    }
  }
  else // load the reg, then read it
  {
    tx[0] = reg;
    i2cTransaction.writeCount = 1;
    i2cTransaction.readCount = len;

    if (I2C_transfer(_handle, &i2cTransaction) != 0)
    {
      //osi_Sleep(1000);
      // Now try to read
      //i2cTransaction.writeCount = 1;
      //i2cTransaction.readCount = len;

      if (I2C_transfer(_handle, &i2cTransaction) != 0)
      {
        // Compare 
        for (i = 0; i < len; i++)
        {
          if (pData[i] != rxData[i])
          {
            //DebugOut("FUEL GAUGE: CFG:  Compare Fail idx[%d] src[%d], read[%d]\r", i, pData[i], rxData[i]);
            return 0;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

// File format is
// "W: I2CAddr RegAddr Byte0 Byte1 Byte2�".
// "R: I2CAddr RegAddr NumBytes
// "C: i2cAddr RegAddr Byte0 Byte1 Byte2".
// X: YYY, where YYY= ms
// W = Write, R = Read, C= Read and compare, X = pause for YYY msec
// Line format is X: XX XX XX...0x0A, wher XX = ASCII coded hex e.g. 0x30 0x30 = AA
#define MAX_FILE_SIZE        8192  //(64L*1024L)-512       /* 64KB file */
#define FG_FILE_NAME         "FuelGaugeCfg.txt"
#define MAX_LINE 128
unsigned char fgBytes[MAX_LINE];
char fgVerStr[MAX_FG_CFG_VER_LEN+1];

void FgLoadGoldenImage()
{
  SlFsFileInfo_t fInfo;
  long hFile = -1;
  int status;
  char line[MAX_LINE + 1];
  int tmpInt;
  bool error = FALSE;

  fgVerStr[0] = 0;

  //DebugOut("FUEL GAUGE: Loading Config File [%s] \r", FG_FILE_NAME);

  // Appears this is not necessary for golden image flashing
  //if (EnableROMMode())
  {
    // Open the file
    // Open the file and read it into the local buffer
    status = sl_FsGetInfo((unsigned char*)FG_FILE_NAME, 0, &fInfo);
    if (status >= 0)
    {
      // Open
      status = sl_FsOpen((unsigned char*)FG_FILE_NAME, FS_MODE_OPEN_READ, NULL, &hFile);
      if (status == 0)
      {
        int fileIdx = 0;
        int lineIdx = 0;
        int byteIdx = 0;
        char* pTok;
        char* pSource = (char*)mem_Malloc(fInfo.FileLen + 1);
        memset(pSource, 0, fInfo.FileLen + 1);
        // Read the entire file
        status = sl_FsRead(hFile, 0, (unsigned char*)pSource, fInfo.FileLen);
        // Now parse into lines
        while ((fileIdx < fInfo.FileLen) && !error)
        {
          memset(line, 0, MAX_LINE + 1);
          lineIdx = 0;
          // Copy to line
          while (pSource[fileIdx] != 0x0A)
          {
            line[lineIdx++] = pSource[fileIdx++];
          }
          fileIdx++;
          line[lineIdx] = 0;

          // Must have a line, process it
          switch (line[0])
          {
          case 'W':
            //W: AA 40 02 26 00 00 32 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
            // Write N bytes to I2C
            //DebugOut("FUEL GAUGE: CFG: ROM Write [%s] \r", &line[6]);
            byteIdx = 0;
            pTok = strtok(&line[6], " "); // skip W: AA
            if (pTok != NULL)
            {
              while (pTok != NULL)
              {
                fgBytes[byteIdx++] = strtol(pTok, NULL, 16);
                pTok = strtok(NULL, " ");
              }
              //DebugOut("FUEL GAUGE: CFG: ROM Write %d bytes\r", byteIdx);
              WriteRom(fgBytes, byteIdx);
            }
            else
            {
              //DebugOut("FUEL GAUGE: CFG: ROM Write parse error - exiting\r");
              error = TRUE;
            }
            break;
          case 'R':
            //DebugOut("!!!!!!BQ27425 ROM Read - NOT Implemented!!!!!\r");
            break;
          case 'C':
            // C: AA 55 AB CD EF 00
            // Read 4 bytes from REG 55 and compare
            byteIdx = 0;
            pTok = strtok(&line[6], " "); // skip W: AA
            if (pTok != NULL)
            {
              unsigned char reg = (unsigned char)strtol(pTok, NULL, 16);
              pTok = strtok(NULL, " ");
              while (pTok != NULL)
              {
                fgBytes[byteIdx++] = strtol(pTok, NULL, 16);
                pTok = strtok(NULL, " ");
              }
              //DebugOut("FUEL GAUGE: CFG: ROM Comparing %d bytes\r", byteIdx);

              if (CompareRom(reg, fgBytes, byteIdx) == 0)
              {
               // DebugOut("FUEL GAUGE: CFG: ROM Compare error - exiting\r");
                error = TRUE;
              }
            }
            else
            {
             // DebugOut("FUEL GAUGE: CFG: ROM Write parse error - exiting\r");
              error = TRUE;
            }
            break;
          case 'X':
            // "X: yyy"
            tmpInt = (int)strtol(&line[3], NULL, 10);
            //DebugOut("FUEL GAUGE: CFG: Sleeping %dms\r", tmpInt);
            osi_Sleep(tmpInt);
            break;
          case 'V':
            // Version str added by us V: xxxxxxx
            strncpy_ex(fgVerStr, &line[2], MAX_FG_CFG_VER_LEN + 1);
            break;
          case ';':
          default:
            // ignore comments other lines
            break;
          }
        } // while not EOF

        // close the file
        sl_FsClose(hFile, NULL, NULL, 0);
        // Delete temp buffer
        mem_Free(pSource);
        //DebugOut("FUEL GAUGE: CFG: %s\r", error ? "FAILED" : "COMPLETED");
        if (!error)
        {
          if (strlen(fgVerStr) > 0)
            SaveFgCfgVer(fgVerStr);
          //else
            //DebugOut("FUEL GAUGE: CFG: ERROR - No Version Line in cfg file\r");
        }
      } // if file open
    } // if file get
    else
    {
      //DebugOut("FUEL GAUGE: ERROR: Config File [%s] not in flash\r", FG_FILE_NAME);
    }
  }
}

void FgReset()
{
  FgControlCmd(SC_SOFT_RESET, NULL, 0);
}

uint16_t FgReadIntReg(uint8_t reg)
{
  uint16_t temp = 0;
  uint8_t rx[2];
  uint8_t tx = reg;
  if (FgWriteRead(&tx, 1, rx, 2))
  {
    temp = (rx[1] << 8) | rx[0];
  }
  return temp;
}

uint8_t FgReadByteReg(uint8_t reg)
{
  uint8_t rx = 0;
  uint8_t tx = reg;
  if (FgWriteRead(&tx, 1, &rx, 1))
  {

  }
  return rx;
}

uint8_t FgPercentCharged()
{
  if (testMode == TEST_MODE_OFF)
  {
    // Prevent returning zero by bumping if < 5%
    uint8_t pct = FgReadByteReg(CMD_SOC);
    if (pct < 5)
      pct += 1;
    return pct;
  }
  else
    return testMode;
}

uint16_t FgFullChgCapacity()
{
  return FgReadIntReg(CMD_FCC);
}

uint16_t FgFlags()
{
  return FgReadIntReg(CMD_FLAGS);
}

uint16_t FgTemp()
{
  return FgReadIntReg(CMD_TEMP);
}

uint16_t FgIntTemp()
{
  return FgReadIntReg(CMD_INT_TEMP);
}

uint16_t FgBatteryMVolts()
{
  return FgReadIntReg(CMD_VOLTS);
}

uint16_t FgRemCapacity()
{
  return FgReadIntReg(CMD_REMC);
}

uint8_t FgAvgCurrent()
{
  uint8_t temp = 0;
  uint8_t rx[2];
  uint8_t tx = CMD_AVG_C;
  if (FgWriteRead(&tx, 1, rx, 2))
  {
    temp = (rx[1] << 8) | rx[0];
  }
  return temp;
}

// Build a sub-string of values for debug
void FgStatsStr(char* pBuffer, int buffLen)
{
  sprintf(pBuffer, "SOC[%d],FCC[%d],RM[%d],ITEMP[%d],TEMP[%d],FLAGS[0x%04X],VOLT[%d],AI[%d],%d:%d:%d:%d:%d:0x%04X:%d:%d",
    FgPercentCharged(), FgFullChgCapacity(), FgRemCapacity(), FgIntTemp(), FgTemp(), FgFlags(), FgBatteryMVolts(), FgAvgCurrent(),
    FgPercentCharged(), FgFullChgCapacity(), FgRemCapacity(), FgIntTemp(), FgTemp(), FgFlags(), FgBatteryMVolts(), FgAvgCurrent());
}

// As implemented must be called after
bool FgReadCalData(uint8_t* pData, uint8_t* pChkSum)
{
  int i = 0;
  uint8_t txData[4];
  memset(pData, 0xEE, 32);
  // Set Cfg Update Mode, if fails, can't talk to chip, probably because no battery connected, abort the process
  if (!FgControlCmd(SC_CFGUPD, NULL, 0))
    return FALSE;
  osi_Sleep(100);
  // Set data class subclass to Calibration block
  txData[0] = CMD_DATA_CLASS;
  txData[1] = DB_SCID_CAL_DATA;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Set DataBlock to 1st 32 byte chunk
  txData[0] = CMD_DATA_BLOCK;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Enable BlockData()
  txData[0] = CMD_DATA_CTL;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Read the block
  for (i = 0; i < CAL_BLOCK_SIZE; i++)
  {
    txData[0] = CMD_BLOCK_DATA_BASE + i;
    FgWriteRead(txData, 1, pData + i, 1);
    osi_Sleep(10);
  }
  // Read the checksum
  txData[0] = CMD_DATA_CHKSUM;
  FgWriteRead(txData, 1, pChkSum, 1);
  osi_Sleep(1000);

  return TRUE;
}

// Read the 1st 32 bytes of State NVM (Block 82)
bool FgReadNvmState1(uint8_t* pData, uint8_t* pChkSum)
{
#define CMD_DELAY_MS 50
  int i = 0;
  uint8_t txData[4];
  memset(pData, 0, 32);
  // Set Cfg Update Mode, if fails, can't talk to chip, probably because no battery connected, abort the process
  if (!FgControlCmd(SC_CFGUPD, NULL, 0))
    return FALSE;
  osi_Sleep(CMD_DELAY_MS);
  // Set data class
  txData[0] = CMD_DATA_CLASS;
  txData[1] = DB_SCID_STATE;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(CMD_DELAY_MS);
  // Set DataBlock to 1st 32 byte chunk
  txData[0] = CMD_DATA_BLOCK;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(CMD_DELAY_MS);
  // Enable BlockData()
  txData[0] = CMD_DATA_CTL;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(CMD_DELAY_MS);
  // Read the block
  for (i = 0; i < 32; i++)
  {
    txData[0] = CMD_BLOCK_DATA_BASE + i;
    FgWriteRead(txData, 1, pData+i, 1);
    osi_Sleep(10);
  }
  // Read the checksum
  txData[0] = CMD_DATA_CHKSUM;
  FgWriteRead(txData, 1, pChkSum, 1);
// JFK Changed to reduce boot time  osi_Sleep(1000);
  osi_Sleep(CMD_DELAY_MS);

  return TRUE;
}

// Read the 2nd 32 bytes of State NVM (Block 82)
bool FgReadNvmState2(uint8_t* pData, uint8_t* pChkSum)
{
  int i = 0;
  uint8_t txData[4];
  memset(pData, 0, 32);
  // Set Cfg Update Mode, if fails, can't talk to chip, probably because no battery connected, abort the process
  if (!FgControlCmd(SC_CFGUPD, NULL, 0))
    return FALSE;
  osi_Sleep(100);
  // Set data class
  txData[0] = CMD_DATA_CLASS;
  txData[1] = DB_SCID_STATE;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Set DataBlock to 2nd 32 byte chunk
  txData[0] = CMD_DATA_BLOCK;
  txData[1] = 0x01;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Enable BlockData()
  txData[0] = CMD_DATA_CTL;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Read the block
  for (i = 0; i < 32; i++)
  {
    txData[0] = CMD_BLOCK_DATA_BASE + i;
    FgWriteRead(txData, 1, pData + i, 1);
    osi_Sleep(10);
  }
  // Read the checksum
  txData[0] = CMD_DATA_CHKSUM;
  FgWriteRead(txData, 1, pChkSum, 1);
  osi_Sleep(1000);

  return TRUE;
}

// Reads the sealed key
bool FgReadKey(uint8_t* pData)
{
  int i = 0;
  uint8_t txData[4];
  uint8_t chkSum = 0;
  memset(pData, 0, 32);
  // Set Cfg Update Mode, if fails, can't talk to chip, probably because no battery connected, abort the process
  if (!FgControlCmd(SC_CFGUPD, NULL, 0))
    return FALSE;
  osi_Sleep(100);
  // Set data class subclass to Calibration block
  txData[0] = CMD_DATA_CLASS;
  txData[1] = DB_SEALED_KEY;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Set DataBlock to 1st 32 byte chunk
  txData[0] = CMD_DATA_BLOCK;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Enable BlockData()
  txData[0] = CMD_DATA_CTL;
  txData[1] = 0x00;
  FgWriteRead(txData, 2, NULL, 0);
  osi_Sleep(100);
  // Read the block
  for (i = 0; i < 32; i++)
  {
    txData[0] = CMD_BLOCK_DATA_BASE + i;
    FgWriteRead(txData, 1, pData + i, 1);
    osi_Sleep(10);
  }
  // Read the checksum
  txData[0] = CMD_DATA_CHKSUM;
  FgWriteRead(txData, 1, &chkSum, 1);
  //osi_Sleep(1000);

  return TRUE;
}


// pRx results are LSB first
bool FgControlCmd(uint8_t subCmd, uint8_t* pRx, uint8_t rxSize)
{
  uint8_t tx[3];

  tx[0] = CMD_CTL;
  tx[1] = subCmd;
  tx[2] = 0x00; // MSB of subCmd is always 0
  FgWriteRead(tx, 3, NULL, 0);
  osi_Sleep(1000);

  return FgWriteRead(tx, 1, pRx, rxSize);
}

bool FgUnsealCmd()
{
  uint8_t rx;
  uint8_t tx[5];

  tx[0] = CMD_CTL;
  tx[1] = 0x14;
  tx[2] = 0x04;
  tx[3] = 0x72;
  tx[4] = 0x36;
  FgWriteRead(tx, 5, NULL, 0);
  osi_Sleep(500);

  return FgWriteRead(tx, 1, &rx, 1);
}
bool FgWriteRead(uint8_t* pTx, uint8_t txLen, uint8_t* pRx, uint8_t rxLen)
{
  bool res = FALSE;
  uint8_t ch;
  I2C_Transaction i2cTransaction;


  i2cTransaction.writeBuf = pTx;
  i2cTransaction.writeCount = txLen;
  i2cTransaction.readBuf = pRx != NULL ? pRx : &ch;
  i2cTransaction.readCount = rxLen;
  i2cTransaction.slaveAddress = BQ28Z_I2C_ADDR;

  osi_LockObjLock(&_fgLock, OSI_WAIT_FOREVER);

  if (I2C_transfer(_handle, &i2cTransaction) != 0)
  {
    //DebugConsoleOut("BQ27425 I2C write OK\n\r");
    res = TRUE;
  }
  else
  {
    //DebugConsoleOut("BQ27425 I2C write FAILED\n\r");
  }
  osi_LockObjUnlock(&_fgLock);
  // Per datasheet, required to wait 66 microsec between cmds
  osi_Sleep(1);
  return res;
}

int FuelGaugeClose()
{
    return 0;
}

