// CHIP NAME: HTU21D(F) RH/T Sensor
#include <pigpio.h>
#include <stdint.h>
#include <unistd.h>
#include "htu21d.h"

#define SLAVE_ADDRESS 0x40
#define READ_TEMP_CMD 0xF3
#define READ_HUM_CMD 0xF5

void read_temp_hum(double *temp, double *hum){	
	unsigned char data[2];
	uint16_t raw_data;
	double calculated_temp;
	double calculated_hum;
	int handle;

	handle = i2cOpen(0, SLAVE_ADDRESS, 0); // get i2c handle on sensor (use bus 0)

	i2cWriteByte(handle, READ_TEMP_CMD); // send read temp command
	usleep(500000); 
	i2cReadDevice(handle, data, 2); // read temperature data
	raw_data = (data[0] << 8) | data[1]; // unpack bytes
	calculated_temp = (-46.85 + 175.72 * (raw_data / (1 << 16))); // 1 << 16 = 2^16
	*temp = calculated_temp; // store in parameter reference
	usleep(500000); 

	i2cWriteByte(handle, READ_HUM_CMD); // send read hum command
	usleep(500000);
	i2cReadDevice(handle, data, 2); // read hum data
	raw_data = (data[0] << 8) | data[1]; // unpack bytes
	calculated_hum = (-6 + 125 * (raw_data / (1 << 16)));
	*hum = calculated_hum;
	usleep(500000);
}

