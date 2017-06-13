#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

class data_controller
{
	public:
	struct data
	{
		
		int sample_time;
		float temp;
		float humidity;
		
	};
	data_controller(std::string a);
	std::string file_path;
	int store(data *d);
	
	private:
	std::ofstream out;
	

};
