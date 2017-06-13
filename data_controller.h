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
		
		time_t sample_time;
		float temp;
		float humidity;
		
	};
	data_controller(std::string a);
	std::string file_path;
	int store(float temp, float humidity);
	
	private:
	std::ofstream out;
	

};
