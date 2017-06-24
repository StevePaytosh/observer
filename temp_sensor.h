#include <wiringPi.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#include <string>
#define MAX_TIME 85  

class temp_sensor
{
	
	
public:	
temp_sensor();
temp_sensor(int pin);
temp_sensor(std::string pin);
~temp_sensor();
void set_pin(std::string pin);
void set_pin(int pin);
int read();
float getTempCelcius();
float getTempFarenheight();
float getHumidity();

private:
int DHT11PIN;
float temp_celcius;
float humidity;
int dht11_val[5];

};
