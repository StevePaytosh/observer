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
	time_t a;
	std::time(&a);
	current.sample_time=(long long int)a;
	
}

int data_controller::store(float temp, float humidity)
{	
	update(temp,humidity);
	return store();
}

int data_controller::store()
{
	out.open(file_path.c_str(), std::ios::binary | std::ofstream::app);
	//out.write((char*)&current, sizeof(data_controller));
	out.write((char*)&current.sample_time, sizeof(long long int) );
	out.write((char*)&current.temp, sizeof(float) );
	out.write((char*)&current.humidity, sizeof(float) );
	out.close();
	return 1;
		
}

int data_controller::read()
{
	
	in.open(file_path.c_str(), std::ios::binary|std::ios::in);
	long long int read_time;
	float read_temp;
	float read_humidity;
	
	while(1)
	{
		if(in.eof())	break;
			in.read((char*)&read_time, sizeof(long long int));
		
		if(in.eof())	break;
			in.read((char*)&read_temp, sizeof(float));
		
		if(in.eof())	break;
			in.read((char*)&read_humidity, sizeof(float));
		
		
		
		time_t a=(time_t)read_time;	
		printf("%s%.2f*c\n%.2f%\n\n", asctime(localtime(&a)), read_temp, read_humidity);
	}
	
	in.close();
	return 1;
}

long long int data_controller::lastSampleTime()
{
	return current.sample_time;
}
