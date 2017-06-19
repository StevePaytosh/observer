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
	~data_controller();
	std::string file_path;
	int store(float temp, float humidity);
	void read();
	
	private:
	std::ofstream out;
	std::ifstream in;
	float current_temp;
	float current_humidity;
	time_t last_sample;
	

};
