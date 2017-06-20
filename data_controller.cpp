#include "data_controller.h"

data_controller::data_controller(std::string d)
{
	file_path=d;
	//out.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary | std::ofstream::app);
}

data_controller::~data_controller()
{
	out.close();
}

int data_controller::update(float temp, float humidity)
{
	current.temp=temp;
	current.humidity=humidity;
	std::time(&current.sample_time);
	
}

int data_controller::store(float temp, float humidity)
{	
	update(temp,humidity);
	return store();
}

int data_controller::store()
{
	out.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary | std::ofstream::app);
	out.write((char*)&current, sizeof(data_controller));
	out.close();
	return 1;
		
}

int data_controller::read()
{
	
	in.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary);
	data_controller::data d;
	in.read((char*)&d, sizeof(data_controller));
	in.close();
	return 1;
}

std::time_t data_controller::lastSampleTime()
{
	return current.sample_time;
}
