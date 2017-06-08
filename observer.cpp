/* 
 * Observers primary function will be to monitor
 * tempeture conditions in a room, display that data to
 * a screen and store that data in a database.
 * 
 * 
 * The program is intended to be run on a raspberry pi or similar microcontroller
 * 
 * When tempetures exceed a minimum threshold, the program
 * should send out an email to relevant parties the room has become to
 * hot. The email should be repeated only once per hour while the room
 * is still too hot.
 * 
 * Similar behaivor should be enabled for cold tempetures.
 * 
 * database storage and emails should be handled
 * as API requests in order to minimize stress on the unit hosting this program
 * 
 * 
 * 
 * */
#include "gpiotest.h"
#include "seg_display.h"
#include "temp_sensor.h"
#include "tact_switch.h"
#include "gumdrop.h"
#include <iostream>
void flashSegment(seg_display *a);



 int main (void)
{
	seg_display *right= new seg_display("27","15","17","14","22","2","3","18");
	seg_display *left = new seg_display("10","24","23","8","7","11","9","5"); 
	temp_sensor *sensor = new temp_sensor();
	tact_switch *tc = new tact_switch("26",1);
	gumdrop *red= new gumdrop("20");
	gumdrop *blue = new gumdrop("21");

	flashSegment(left);
	flashSegment(right);
	
	int temp=sensor->getTempCelcius();
	int humidity = sensor -> getHumidity();
	int res=0;
	int useImperialUnits = 1;
	int readHumidity=0; // when this flag is high, print the humidity instead of the temperature
	std::string in="";
	
	//printf("test: temp= %d",temp);
	while(1)
	{
		if(sensor->read())
		{
			temp=sensor->getTempCelcius();
			humidity = sensor-> getHumidity();
			
		useImperialUnits=tc->getState();
		
		if(useImperialUnits)
		{
			//set red gumdrop, kill blue
			red->turn_on();
			blue->turn_off();
			 
		}
		else
		{
			red->turn_off();
			blue->turn_on();
		}
		
	//	std::cout<<"\ngpio input = "<<in<<"\n";
	//	std::cout<<"\nuse imperial = "<<useImperialUnits<<"\n";
		if(!readHumidity)
		{
			if(useImperialUnits)
			{
				temp=sensor->getTempFarenheight();
				left->display(temp/10);
				right->display(temp%10);//display the lower portion of the temperature
			}
			else
			{
				left->display(temp/10);
				right->display(temp%10);//display the lower portion of the temperature
			}
		}
		else
		{
				humidity = sensor->getHumidity();
				left -> display(humidity/10);
				right -> display (humidity%10);
			
		}	
		
		}
			
	}
}

void flashSegment(seg_display *a)
{
	int i=0;
	for(;i<4; i++)
	{
		a->clear_all();
		delay(1000);
		a->set_all();
		delay(1000);
	}
	
	a->clear_all();
}


