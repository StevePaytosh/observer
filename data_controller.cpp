#include "data_controller.h"

data_controller::data_controller(std::string d)
{
	file_path=d;
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
	out.open(file_path.c_str(), std::ios::binary | std::ofstream::app);
	out.write((char*)&current, sizeof(data_controller));
	out.close();
	return 1;
		
}

int data_controller::read()
{
	
	in.open(file_path.c_str(), std::ios::binary);
	data_controller::data d;
	while(1)
	{
		in.read((char*)&d, sizeof(data_controller));
		if(in.eof())
		{
			printf("eof\n");
			break;
		}	
			
		printf("%s %.2f*c %.2f%\n", asctime(localtime(&d.sample_time)), d.temp, d.humidity);
	}
	
	in.close();
	return 1;
}

std::time_t data_controller::lastSampleTime()
{
	return current.sample_time;
}
