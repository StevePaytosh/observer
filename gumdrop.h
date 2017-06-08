#include "GPIOClass.h"
#include <string>

class gumdrop
{
	private:
	int state;
	GPIOClass *LED;

	public:
	gumdrop(std::string p);
	int getState();
	void setState(int a);
	void toggle();
	void turn_on();
	void turn_off();
	
};
