/**
  *@file bq28z.h
  *@brief driver for bq28zxx fueld gauge
  *@author
  *@date 03/25/2019
  */

#pragma once

#include "Platforms/Common/mrt_platform.h"

//TODO find real values for these
#define BQ28Z_REGADDR_SIZE 2  /* register address size for this device  */
#define BQ28Z_I2C_ADDR 0xAA

/* define struct for device */
typedef struct{
  mrt_i2c_handle_t mI2c;  //i2c_handle
}bq28z_t;


/**
  *@brief initialize bq28z device
  *@param dev ptr to device struct
  *@param handle mrt_i2c_handle
  *@return MRT_STATUS_OK if successful
  *@return MRT_STATUS_ERROR if there was a problem
  */
mrt_status_t bq28z_init(bq28z_t* dev, mrt_i2c_handle_t handle);
