/**
  *@file bq28z.h
  *@brief driver for bq28zxx fueld gauge
  *@author
  *@date 03/25/2019
  */

#pragma once

#include "Platforms/Common/mrt_platform.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//TODO find real values for these
#define BQ28Z_REGADDR_SIZE 2  /* register address size for this device  */
#define BQ28Z_I2C_ADDR 0xAA

typedef enum
{
  BATTERY_CHARGING,
  BATTERY_GOOD,
  BATTERY_LOW,
  BATTERY_VERY_LOW,
  BATTERY_MISSING,
  BATTERY_CRITICAL,
} BatteryModes;

typedef struct i2C_Transaction{
			void *writeBuf; 
			size_t writeCount; 
			void *readBuf;
			size_t readCount; 
			unsigned char slaveAddress; 
			void *arg;
			void *nextPtr; 
		}I2C_Transaction;

/* define struct for device */
typedef struct{
  mrt_i2c_handle_t mI2c;  //i2c_handle
}bq28z_t;

// Used by processes other than MainTask() so the fuel gauge is not 
// read by multiple tasks
BatteryModes FgLastBatteryStatus();
uint8_t FgLastBatteryPct();

BatteryModes FgBatteryStatus(bool useCachedVal);
bool FgBatteryIsAlarmMode();

void FgReset();
//*****************************************************************************
//
// API Function prototypes
//
//*****************************************************************************
extern void FgLoadGoldenImage();
bool FuelGaugeOpen(mrt_i2c_handle_t handle, bool doConfig);
uint8_t FgPercentCharged();
uint16_t FgBatteryMVolts();
int FuelGaugeClose();
void FgTest(int val);
bool I2C_transfer(mrt_i2c_handle_t handle, I2C_Transaction *transaction); 
void FgStatsStr(char* pBuffer, int buffLen);

/**
  *@brief initialize bq28z device
  *@param dev ptr to device struct
  *@param handle mrt_i2c_handle
  *@return MRT_STATUS_OK if successful
  *@return MRT_STATUS_ERROR if there was a problem
  */
mrt_status_t bq28z_init(bq28z_t* dev, mrt_i2c_handle_t handle);
MRT_I2C_MEM_READ(dev->mI2c, BQ28Z_I2C_ADDR, regAddr, BQ28Z_REGADDR_SIZE, data, len, 100 );
MRT_I2C_MEM_WRITE(dev->mI2c, BQ28Z_I2C_ADDR, regAddr, BQ28Z_REGADDR_SIZE, data, len, 100 );