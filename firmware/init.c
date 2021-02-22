#include <pigpio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "system.h"
#include "remote.h"
#include "pins.h"
#include "drivers/afm3000.h"

void init_hardware(){	
	// initialize pigpio
	gpioInitialise();

	// --- AIR PUMP PWM --- //
	// configue air pump pwm
	gpioSetPWMrange(AIR_PUMP_PWM, AIR_PUMP_RANGE); // range of acceptable values is 0 to 1000
	gpioSetPWMfrequency(AIR_PUMP_PWM, AIR_PUMP_FREQ); // frequency of 2 KHz

	// default to 100% duty cycle (OFF)
	gpioPWM(AIR_PUMP_PWM, AIR_PUMP_RANGE);

	// --- OXYGEN SERVO CONTORL --- //
	// default to most clockwise position (servo 100% -> oxygen regulator 0%)
	gpioServo(OXYGEN_VALVE_PWM, OXYGEN_VALVE_MIN);

	// --- HUMIDIFIER CONTROL --- //
	gpioSetMode(HUMIDIFIER_CONTROL_PIN, PI_OUTPUT);

	printf("[INIT] Finished hardware initialization\n");
}

int main(){
	int count = 0;

	// 'POST'
//	init_hardware();
	init_remote();


	// scan
	while(1){
//		sys_read_airflow();
		//printf("%d LPM\n", sys_airflow);
		usleep(75000); 
	}
}
