#include "data_controller.h"

data_controller::data_controller(std::string d)
{
	file_path=d;
	out.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary | std::ofstream::app);
}

int data_controller::store(float temp, float humidity)
{
	data_controller::data d;
	time_t tm;
	time(&tm);
	d.sample_time=tm;
	d.temp=temp;
	d.humidity=humidity;
	out.write((char*)&d, sizeof(d));
	return 1;
}
