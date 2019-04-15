/**
  *@file bq28z.c
  *@brief driver for bq28zxx fueld gauge
  *@author
  *@date 03/25/2019
  */

#include "bq28z.h"

#define DESIGN_CAPACITY 4400 // mAh --
#define TERMINATE_VOLTAGE 6000 // mV --
#define CHG_TERM_VOLTAGE 4200 // --
#define DESIGN_ENERGY 6336 // mWh --
#define CC_OFFSET -32768 // mV --

static mrt_i2c_handle_t handle= 0; 
static OsiLockObj_t    _fgLock;
static BatteryModes    _fgLastMode = BATTERY_GOOD; 
static uint16_t _fgLastPct = 0;
static uint8_t _termVoltage = 0; 
static uint8_t _VChgTerm = 0;
#define SWAP16(x) ( (0xFF00 & ((x) << 8)) | (0xFF & ((x) >> 8)))



#define CMD_CTL       0x00//01 
#define CMD_TEMP      0x06//07 
#define CMD_VOLTS     0x08//09 
       
#define CMD_REMC      0x10//11 
#define CMD_FCC       0x12//13 
#define CMD_AVG_C     0x14//15 
#define CMD_AVG_P     0x22//23 
#define CMD_SOC       0x2C//2D 
#define CMD_INT_TEMP  0x28//29 
#define CMD_SOH       0x2E//2F 
#define CMD_CHG_VOLT  0x30//0x31   
#define CMD_DES_CAP   0x3C//3D 


#define DESIGN_CAP_OFFSET 12
#define TERM_VOLTAGE_OFFSET 18

// Offsets into CC Data block (104)
#define CAL_CC_OFFSET_OFFSET 3 //
#define CAL_BOARD_OFFSET     0 // 
#define CAL_INT_TEMP_OFFSET  0 //
#define CAL_PACK_V_OFFSET_OFFSET 4
#define CAL_BLOCK_SIZE 32

// Sub-commands are 0x00XX, but since they need to be sent LSB first,
// and all have MSB=0, only defining LSB, will insert MSB in FgControlCmd()
#define SC_CTL_STAT 0x00 
#define SC_DEV_TYPE 0x01
#define SC_FW_VER   0x02
#define SC_RESET    0x12 




// Enter ROM Mode
#define ROM_MODE_I2C_ADDR 0x0B
// Write 0xF000 to REG 0x00 to enter ROM mode
// To confirm, read at 0xCC (should fail), read at 0x0B should pass)


//****************************************************************************
//                      LOCAL FUNCTION DEFINITIONS                          
//****************************************************************************
bool FgControlCmd(uint8_t subCmd, uint8_t* pRx, uint8_t rxSize);
bool FgWriteRead(uint8_t* pTx, uint8_t txLen, uint8_t* pRx, uint8_t rxLen);


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

uint8_t FgLastBatteryPct()
{
  return _fgLastPct;
}

int FgBatteryStatus(int bits)
{
  uint8_t *data;
  uint16_t* length;
  int batteryData; 
  bool status; 
  status = bq28z_read_regs(dev->mI2c, BATTERY_STATUS, data, length);
    if(status)
    {
      //Battery Status
      batteryData = data & (1 << bits - 1); 
      
    } 
  return batteryData; 
}

void FgReset()
{
  
}

uint8_t FgReadByteReg(uint8_t reg)
{
  uint16_t* length; 
  uint8_t* data;
  status = bq28z_read_regs(dev->mI2c, reg, data, length);
  if(status)
  {
    return data;
  }
  return;
}

int FgAvgCurrent()
{
  int avgCurrent;
  avgCurrent = FgReadByteReg(CMD_AVG_C); 
  return avgCurrent; 
}

uint8_t FgPercentCharged()
{
  //read current state of charge
  uint8_t pct = FgReadByteReg(CMD_SOC);
  if (pct < 5)
  pct += 1;
  return pct;
}

uint16_t FgFullChgCapacity()
{
  return FgReadByteReg(CMD_FCC);
}

uint16_t FgFlags()
{
  return FgReadByteReg(CMD_FLAGS);
}

uint16_t FgTemp()
{
  return FgReadByteReg(CMD_TEMP);
}

uint16_t FgIntTemp()
{
  return FgReadByteReg(CMD_INT_TEMP);
}

uint16_t FgBatteryMVolts()
{
  return FgReadByteReg(CMD_VOLTS);
}

uint16_t FgRemCapacity()
{
  return FgReadByteReg(CMD_REMC);
}

BatteryModes FgChargeStatus()
{ 
  //Bit 5 charge status
  int chargeBit = 5;
  int status = FgBatteryStatus(5);
  // bit set to 0 battery not fully charged
  if(status!=0)
  {
     return mode = BATTERY_GOOD; 
  }
  else{
     return mode = BATTERY_NOT_FULLY_CHARGED;
  }
}
// Build a sub-string of values for debug
void FgStatsStr(char* pBuffer, int buffLen)
{
  sprintf(pBuffer, "SOC[%d],FCC[%d],RM[%d],ITEMP[%d],TEMP[%d],FLAGS[0x%04X],VOLT[%d],AI[%d],%d:%d:%d:%d:%d:0x%04X:%d:%d",
    FgPercentCharged(), FgFullChgCapacity(), FgRemCapacity(), FgIntTemp(), FgTemp(), FgFlags(), FgBatteryMVolts(), FgAvgCurrent(),
    FgPercentCharged(), FgFullChgCapacity(), FgRemCapacity(), FgIntTemp(), FgTemp(), FgFlags(), FgBatteryMVolts(), FgAvgCurrent());
}


