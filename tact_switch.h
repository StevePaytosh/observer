#include "GPIOClass.h"
#include <string>
#include <iostream>

class tact_switch
{
	public:
	tact_switch();
	tact_switch(int gpio_pin, int init_state=0);
	tact_switch(std::string gpio_pin, int init_state=0);
	int getState();
	int setPin(int gpio_pin);
	int setPin(std::string gpio_pin);
	
	private:
	int state;
	int pin;
	GPIOClass *tc;

};
