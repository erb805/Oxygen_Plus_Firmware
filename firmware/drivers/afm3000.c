/* Flow Rate Sensor Code
   Make sure i2c is turned on in raspi-config.
   Also pigpio daemon should be off.
   Uses sda1 and scl1.
   stdio.h is only included for printf() and can
   be removed if not using printf().
*/
#include "afm3000.h"
#include <stdint.h>
#include <stdio.h>
#include <pigpio.h>

#define SLAVE_ADDRESS 0x40

uint16_t read_flow_rate(){
	uint16_t value;
	uint16_t flow;
	uint8_t direction;

	unsigned char data[2];
	unsigned char command[2];
	int handle;
		
	handle = i2cOpen(1, SLAVE_ADDRESS, 0); // get i2c handle on sensor
	command[0] = 0x10; //Set flow collection command 0x1000
	command[1] = 0x00;

	i2cWriteDevice(handle, command, 2); // send gather flow data command
	i2cReadDevice(handle, data, 2); // read flow rate information
		
	value = (data[0] << 8) | (data[1] & 0xFF); // unpack bytes
		
	// check direction of the flow
	// forward
	if(value > 0x7D00){
		flow = ((value - 32000) / 140);
		direction = 1;
	}
	// backward
	else if(value < 0x7D00)
	{
		flow = ((32000 - value) / 140);
		direction = -1; 
	}
	else
	{
		flow = 0;
		direction = 1;
	}
	i2cClose(handle);
	return flow;
}

/*
uint16_t read_flow_rate()
{
	uint16_t value;
	uint16_t flow;
	uint8_t direction;

	unsigned char data[2];
	unsigned char command[2];
	int handle;
		
	handle = i2cOpen(1, SLAVE_ADDRESS, 0); //Get handle(id) for sensor
	command[0] = 0x10;	//Set flow collection command,0x1000
	command[1] = 0x00;

	i2cWriteDevice(handle, command, 2);	//Tell sensor to prepare data
	i2cReadDevice(handle, data, 2); 		//Read bytes into value array
	
	//Get flow rate
	value = (data[0] << 8) | (data[1] & 0xFF);
	
	if(value > 0x7D00)	//check direction of flow
	{
		flow = ((value - 32000)/140);
		direction = 1; //Forward direction
	}
	else if(value < 0x7D00)
	{
		flow = ((32000-value)/140);
		direction = 0; //Reverse direction
	}
	else
	{
		flow = 0;
		direction =1;
	}	
	return(flow);
}
*/
