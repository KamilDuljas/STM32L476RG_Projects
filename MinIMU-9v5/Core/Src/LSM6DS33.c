#include "LSM6DS33.h"
#include "i2c.h"
#include <stdio.h>
#include <stdint.h>
#include "ioputchar.h"

#define LSM6DS33_ADDRESS 0xD7
#define LSM6DS33_WHO_AM_I_VALUE 	0x69

static void
LSM6DS33_write_register (uint16_t reg, uint8_t val)
{
  HAL_StatusTypeDef result = HAL_I2C_Mem_Write (&hi2c1, LSM6DS33_ADDRESS, reg,
						1, val, sizeof(val),
						HAL_MAX_DELAY);
  if (result != HAL_OK)
    {
      printf ("Write error\n");
    }
  else
    {
      printf ("reg: 0x%X: val: 0x%X Write ok\n", reg, val);
    }
}
static uint8_t
LSM6DS33_read_register (uint16_t reg)
{

  uint8_t value;
  HAL_StatusTypeDef result = HAL_I2C_Mem_Read (&hi2c1, LSM6DS33_ADDRESS, reg, 1,
					       &value, sizeof(value),
					       HAL_MAX_DELAY);
  if (result != HAL_OK)
    {
      printf ("Read error\n");
    }
  return value;
}

void
LSM6DS33_enable_acc ()
{
  LSM6DS33_write_register (LSM6DS33_CTRL1_XL, 0x30);
  // LSM6DS33_write_register(LSM6DS33_CTRL9_XL, 0x38);
}

void
LSM6DS33_enable_gyro ()
{
  LSM6DS33_write_register (LSM6DS33_CTRL2_G, 0x30);
  //LSM6DS33_write_register(LSM6DS33_CTRL9_XL, 0x38);
}
void
LSM6DS33_read_acc_data (LSM6DS33 *device)
{
  uint8_t gyroXL = LSM6DS33_read_register (LSM6DS33_OUTX_L_G);
  uint8_t gyroXH = LSM6DS33_read_register (LSM6DS33_OUTX_H_G);

  uint8_t gyroYL = LSM6DS33_read_register (LSM6DS33_OUTY_L_G);
  uint8_t gyroYH = LSM6DS33_read_register (LSM6DS33_OUTY_H_G);

  uint8_t gyroZL = LSM6DS33_read_register (LSM6DS33_OUTZ_L_G);
  uint8_t gyroZH = LSM6DS33_read_register (LSM6DS33_OUTZ_H_G);

  uint8_t acclXL = LSM6DS33_read_register (LSM6DS33_OUTX_L_XL);
  uint8_t acclXH = LSM6DS33_read_register (LSM6DS33_OUTX_H_XL);

  uint8_t acclYL = LSM6DS33_read_register (LSM6DS33_OUTY_L_XL);
  uint8_t acclYH = LSM6DS33_read_register (LSM6DS33_OUTY_H_XL);

  uint8_t acclZL = LSM6DS33_read_register (LSM6DS33_OUTZ_L_XL);
  uint8_t acclZH = LSM6DS33_read_register (LSM6DS33_OUTZ_H_XL);

  // Update gyro data
  device->gyroX = (gyroXH << 8) | (gyroXL);
  device->gyroY = (gyroYH << 8) | (gyroYL);
  device->gyroZ = (gyroZH << 8) | (gyroZL);

  // Update accelerometer data
  device->acclX = (acclXH << 8) | (acclXL);
  device->acclY = (acclYH << 8) | (acclYL);
  device->acclZ = (acclZH << 8) | (acclZL);
  //float x = device->acclX * 2.0f / 32678.0f;
 // float y = device->acclY * 2.0f / 32678.0f;
 // float z = device->acclZ * 2.0f / 32678.0f;
  //printf ("Acc: X = %.2f   Y = %.2f   Z = %.2f\n", x, y, z);

 // printf ("Gyro: X = %d   Y = %d   Z = %d\n", device->gyroX, device->gyroY, device->gyroZ);
  //printf("Acc: X = %d   Y = %d   Z = %d\n", acclX, acclY, acclZ);

}

void
LSM6DS33_init ()
{
  uint8_t who_am_i = LSM6DS33_read_register (LSM6DS33_WHO_AM_I);

  if (who_am_i == LSM6DS33_WHO_AM_I_VALUE)
    {
      printf ("Init ok\n");
    }
  else
    {
      printf ("Init error\n");
      Error_Handler ();
    }
}
