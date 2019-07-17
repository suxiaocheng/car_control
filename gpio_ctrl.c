#include "gpio_ctrl.h"

#ifdef __RASPBERRY_PI__

// GPIO0-1 Control right-back wheel
// GPIO2-3 Control left-back wheel
// GPIO4-5 Control right-front wheel
// GPIO28-29 Control left-front wheel
#include <wiringPi.h>


#else

#ifndef INPUT
#define INPUT                    0
#endif

#ifndef OUTPUT
#define OUTPUT                   1
#endif

#ifndef LOW
#define LOW                      0
#endif

#ifndef HIGH
#define HIGH                     1
#endif

void wiringPiSetup(void){}
void pinMode(int num, int mode){}
void digitalWrite(int num, int status){}

#endif

int pin_num_list[] = { \
	GPIO_LEFT_FRONT_FORWARD, \
	GPIO_LEFT_FRONT_BACKWARD, \
	GPIO_RIGHT_FRONT_FORWARD, \
	GPIO_RIGHT_FRONT_BACKWARD, \
	GPIO_LEFT_BACK_FORWARD, \
	GPIO_LEFT_BACK_BACKWARD, \
	GPIO_RIGHT_BACK_FORWARD, \
	GPIO_RIGHT_BACK_BACKWARD};

int pin_mode_status_list[][8] = {\
	{0, 1, 1, 0, 0, 1, 1, 0}, \
	{1, 0, 1, 0, 1, 0, 1, 0}, \
	{1, 0, 0, 1, 1, 0, 0, 1}, \
	{0, 0, 0, 0, 0, 0, 0, 0}, \
	{0, 1, 0, 1, 0, 1, 0, 1}};

int init_gpio(void)
{
	int i;
	wiringPiSetup();
	for (i=0; i<sizeof(pin_num_list)/sizeof(int); i++) {
		pinMode(pin_num_list[i], OUTPUT);
		digitalWrite(pin_num_list[i], LOW);
	}
	return 0;
}

int set_mode(int mode)
{
	int i;
	if (mode >= MODE_MAX) {
		return -1;
	}
	for (i=0; i<sizeof(pin_num_list)/sizeof(int); i++) {
		digitalWrite(pin_num_list[i], pin_mode_status_list[mode][i]);
	}
	return 0;
}

