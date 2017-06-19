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

int data_controller::store(float temp, float humidity)
{
	out.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary | std::ofstream::app);
	current_temp=temp;
	current_humidity=humidity;
	time(&last_sample);
	
	data_controller::data d;
	d.sample_time=last_sample;
	d.temp=current_temp;
	d.humidity=current_humidity;
	printf("data write:: temp=%.3f humidity=%.3f\n",d.temp, d.humidity);
	out.write((char*)&d, sizeof(data_controller));
	
	out.close();
	return 1;
}

void data_controller::read()
{
	
	in.open("/home/pi/Desktop/code/git/observer/save.dat", std::ios::binary);
	data_controller::data d;
	
	in.read((char*)&d, sizeof(data_controller));
	printf("data read:: temp=%.3f humidity=%.3f\n",d.temp, d.humidity);
	printf("print out after read\n");
	in.close();
	return;
}
