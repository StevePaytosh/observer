#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

class data_controller
{
	public:
	struct data
	{
		
		long long int sample_time;
		float temp;
		float humidity;
		
	};
	data_controller(std::string a);
	~data_controller();
	std::string file_path;
	int store(float temp, float humidity);
	int store();
	int read();
	int update(float temp, float humidity);
	long long int lastSampleTime();
	
	private:
	std::ofstream out;
	std::ifstream in;
	data current;
	

};
