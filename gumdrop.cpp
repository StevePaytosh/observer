#include "gumdrop.h"

gumdrop::gumdrop(std::string pin)
{
	LED=new GPIOClass(pin);
	LED->export_gpio(); 
	LED->setdir_gpio("out");
	turn_off();
}

int gumdrop::getState()
{
	return state;
}

void gumdrop::setState(int s)
{
	if(s)
		turn_on();
	else
		turn_off();
}

void gumdrop::turn_off()
{
	LED->setval_gpio("0");
	state=0;
}

void gumdrop::turn_on()
{
	LED->setval_gpio("1");
	state=1;
}

void gumdrop::toggle()
{
		if(state)
			turn_off();
		else
			turn_on();
}
