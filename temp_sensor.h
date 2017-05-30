#include <wiringPi.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
#define MAX_TIME 85  

class temp_sensor
{
	
	
public:	
temp_sensor();
temp_sensor(int pin);
~temp_sensor();
void set_pin();
int read();
float getTempCelcius();
float getHumidity();

private:
int DHT11PIN;
float temp_celcius;
float humidity;
int dht11_val[5];
//TODO add timestamps

};
