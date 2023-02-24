#ifndef INC_LSM6DS33_H_
#define INC_LSM6DS33_H_

#include <stdint.h>

// Represents a LSM6DS33 device
typedef struct {

	int16_t 			acclX; // Last set of accelerometer readings
	int16_t 			acclY;
	int16_t				acclZ;

	int16_t 			gyroX; // Last set of gyroscope readings
	int16_t				gyroY;
	int16_t				gyroZ;

} LSM6DS33;

enum LSM6DS33RegAddr {
	LSM6DS33_FUNC_CFG_ACCESS = 0x01, // Embedded functions configuration register

	LSM6DS33_FIFO_CTRL1 = 	   0x06, // FIFO Configuration registers
	LSM6DS33_FIFO_CTRL2 = 	   0x07,
	LSM6DS33_FIFO_CTRL3 = 	   0x08,
	LSM6DS33_FIFO_CTRL4 = 	   0x09,
	LSM6DS33_FIFO_CTRL5 = 	   0x0A,
	LSM6DS33_ORIENT_CFG_G =    0x0B,

	LSM6DS33_INT1_CTRL =       0x0D, // INT1 pin control
	LSM6DS33_INT2_CTRL = 	   0x0E, // INT2 pin control
	LSM6DS33_WHO_AM_I =        0x0F, // Who I am ID

	LSM6DS33_CTRL1_XL =        0x10, // Accl and gyro control registers
	LSM6DS33_CTRL2_G = 	       0x11,
	LSM6DS33_CTRL3_C =         0x12,
	LSM6DS33_CTRL4_C =         0x13,
	LSM6DS33_CTRL5_C =         0x14,
	LSM6DS33_CTRL6_C =         0x15,
	LSM6DS33_CTRL7_G =         0x16,
	LSM6DS33_CTRL8_XL =        0x17,
	LSM6DS33_CTRL9_XL =        0x18,
	LSM6DS33_CTRL10_C =        0x19,

	LSM6DS33_WAKE_UP_SRC =     0x1B, // Interrupt registers
	LSM6DS33_TAP_SRC =         0x1C,
	LSM6DS33_D6D_SRC =         0x1D,

	LSM6DS33_STATUS_REG =      0x1E, // Status data register

	LSM6DS33_OUT_TEMP_L =      0x20, // Temperature output data register
	LSM6DS33_OUT_TEMP_H =      0x21,

	LSM6DS33_OUTX_L_G =        0x22, // Gyro output register
	LSM6DS33_OUTX_H_G =        0x23,
	LSM6DS33_OUTY_L_G =        0x24,
	LSM6DS33_OUTY_H_G =        0x25,
	LSM6DS33_OUTZ_L_G =        0x26,
	LSM6DS33_OUTZ_H_G =        0x27,

	LSM6DS33_OUTX_L_XL =       0x28, // Accl output register
	LSM6DS33_OUTX_H_XL =       0x29,
	LSM6DS33_OUTY_L_XL =       0x2A,
	LSM6DS33_OUTY_H_XL =       0x2B,
	LSM6DS33_OUTZ_L_XL =       0x2C,
	LSM6DS33_OUTZ_H_XL =       0x2D,

	LSM6DS33_FIFO_STATUS1 =    0x3A, // FIFO status registers
	LSM6DS33_FIFO_STATUS2 =    0x3B,
	LSM6DS33_FIFO_STATUS3 =    0x3C,
	LSM6DS33_FIFO_STATUS4 =    0x3D,

	LSM6DS33_FIFO_DATA_OUT_L = 0x3E, // FIFO data output registers
	LSM6DS33_FIFO_DATA_OUT_H = 0x3F,

	LSM6DS33_TIMESTAMP0_REG =  0x40, // Time-stamp output registers
	LSM6DS33_TIMESTAMP1_REG =  0x41,
	LSM6DS33_TIMESTAMP2_REG =  0x42,

	LSM6DS33_STEP_TIMESTAMP_L= 0x49, // Step counter timestamp registers
	LSM6DS33_STEP_TIMESTAMP_H= 0x4A,

	LSM6DS33_STEP_COUNTER_L =  0x4B, // Step counter output registers
	LSM6DS33_STEP_COUNTER_H =  0x4C,

	LSM6DS33_FUNC_SRC =        0x53, // Interrupt register

	LSM6DS33_TAP_CFG =         0x58, // Interrupt registers
	LSM6DS33_TAP_THS_6D =      0x59,
	LSM6DS33_INT_DUR2 =        0x5A,
	LSM6DS33_WAKE_UP_THS =     0x5B,
	LSM6DS33_WAKE_UP_DUR =     0x5C,
	LSM6DS33_FREE_FALL =       0x5D,
	LSM6DS33_MD1_CFG =         0x5E,
	LSM6DS33_MD2_CFG =         0x5F
};

void LSM6DS33_init();
void LSM6DS33_enable_acc();
void LSM6DS33_read_acc_data();

#endif /* INC_LSM6DS33_H_ */
