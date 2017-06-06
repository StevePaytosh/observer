#include "tact_switch.h"

tact_switch::tact_switch(std::string gpio_pin, int init_state)
{
	state=init_state;
	
	tc = new GPIOClass(gpio_pin);
	tc -> export_gpio();
	tc -> setdir_gpio("in");
}

int tact_switch::getState()
{
	std::string str_state="";
	 tc->getval_gpio(str_state);
	return	str_state.compare("1")?1:0;
	
}

