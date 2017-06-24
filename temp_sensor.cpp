#include "temp_sensor.h"

temp_sensor::temp_sensor()
{

}  

temp_sensor::temp_sensor(int pin)
{
	wiringPiSetup();
	temp_celcius=0;
	humidity=0;
	DHT11PIN=pin;
	
	int res=0;
		
	while(!res)
		res=read();
}

temp_sensor::temp_sensor(std::string pin)
{
	wiringPiSetup();
	temp_celcius=0;
	humidity=0;
	DHT11PIN=std::atoi(pin.c_str());
	
	int res=0;
		
	while(!res)
		res=read();
}

temp_sensor::~temp_sensor()
{
	
}

void temp_sensor::set_pin(std::string pin)
{
	DHT11PIN = std::stoi(pin.c_str());
}

void temp_sensor::set_pin(int pin)
{
	DHT11PIN = pin;
}


float temp_sensor::getTempCelcius()
{
	return temp_celcius;
}

float temp_sensor::getTempFarenheight()
{
	// temp[farenheight]= temp[celcius] (9/5) + 32
	return temp_celcius*9./5.+32;  
}

float temp_sensor::getHumidity()
{
	return humidity;
}
int temp_sensor::read()
{
  //initialization
  uint8_t lststate=HIGH;  
  uint8_t counter=0;  
  uint8_t j=0,i; 
  
    for(i=0;i<5;i++)  
     dht11_val[i]=0;  
     
  pinMode(DHT11PIN,OUTPUT); 
  digitalWrite(DHT11PIN,LOW); //signal to the sensor for a reading
  
  //wait, then sent signal high
	delay(18); 
	digitalWrite(DHT11PIN,HIGH);  
	delayMicroseconds(40);  
	  
	pinMode(DHT11PIN,INPUT);  //pin can now read in data
	  
	  //
  for(i=0;i<MAX_TIME;i++)  
  {  
		counter=0;  
		while(digitalRead(DHT11PIN)==lststate)
		{  
		  counter++;  
		  delayMicroseconds(1);  
		  if(counter==255)  
			break;  
		}  
    
		lststate=digitalRead(DHT11PIN);  
		if(counter==255)  
		   break;  
       
		// top 3 transistions are ignored  
		if((i>=4)&&(i%2==0))
		{  
		  dht11_val[j/8]<<=1;  
		  if(counter>16)  
			dht11_val[j/8]|=1;  
		  j++;  
		}
    
  } 
  
     // verify cheksum and print the verified data  
	  if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF)))  
	  {  
		float farenheit=dht11_val[2]*9./5.+32;  
		temp_celcius=dht11_val[2]+(float)dht11_val[3]/100;
		humidity=dht11_val[0]+(float)dht11_val[1]/100;
		//printf("Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3],farenheit);  
		//printf("vars: Humidity = %f , Temp = %f\n\n", temp_celcius, humidity);
		return 1;
	  }   
  else
	return 0;
	  
	  
}

