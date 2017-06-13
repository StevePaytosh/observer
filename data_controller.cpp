#include "data_controller.h"

data_controller::data_controller(std::string d)
{
	file_path=d;
	out.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary | std::ofstream::app);
}

int data_controller::store(data_controller::data *d)
{
	out.write((char*)&d, sizeof(d));
	return 1;
}
