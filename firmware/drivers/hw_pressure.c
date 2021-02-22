#include "hw_pressure.h"
#include <stdint.h>
#include <pigpio.h>

#define SLAVE_ADDRESS 0x38
#define PRESSURE_OUTPUT_MIN 1638
#define PRESSURE_OUTPUT_MAX 14745
#define PRESSURE_MIN_VAL 0.0  // range is from 0 to 60 PSI
#define PRESSURE_MAX_VAL 60.0
#define PRESSURE_MAX_SAMPLES 5

int16_t read_pressure(){
	int16_t pressure;
	unsigned char data[4];
	int handle;	

	handle = i2cOpen(1, SLAVE_ADDRESS, 0); // get i2c handle on sensor

	i2cReadDevice(handle, data, 4); // read flow rate information
	pressure = (data[0] << 8) | data[1]; // unpack bytes
	pressure = (((pressure - PRESSURE_OUTPUT_MIN) * (PRESSURE_MAX_VAL - PRESSURE_MIN_VAL)) / (PRESSURE_OUTPUT_MAX - PRESSURE_OUTPUT_MIN)) + PRESSURE_MIN_VAL; // convert to PSI

	i2cClose(handle);
	return pressure;
}



