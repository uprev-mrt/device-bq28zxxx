/**
  *@file bq28z.c
  *@brief driver for bq28zxx fueld gauge
  *@author
  *@date 03/25/2019
  */

#include "bq28z.h"



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
