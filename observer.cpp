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
#include <fstream>
#include "data_controller.h"
void flashSegment(seg_display *a);
void flashGumdrop(gumdrop *a);



 int main (void)
{
	seg_display *right= new seg_display("27","15","17","14","22","2","3","18");
	seg_display *left = new seg_display("10","24","23","8","7","11","9","5"); 
	temp_sensor *sensor = new temp_sensor();
	tact_switch *tc = new tact_switch("26",1);
	gumdrop *red= new gumdrop("20");
	gumdrop *blue = new gumdrop("21");
	int switch_lock=0; //indicates if the switch has hit zero since it was read as high
	int display_state=0; //determines what data should be displayed
	std::string output_path="/home/pi/Desktop/code/git/observer/save.dat";
	data_controller *dc = new data_controller(output_path);
	
	//run diagnostic on LEDs
	//flashSegment(left);
	//flashSegment(right);
	//flashGumdrop(red);
	//flashGumdrop(blue);
	
	float temp=0; //sensor->getTempCelcius();
	float humidity =0;// sensor -> getHumidity();
	int res=0;
	int useImperialUnits = 1;
	int readHumidity=0; // when this flag is high, print the humidity instead of the temperature

	

	int a =sensor->getTempCelcius();
	int b =sensor->getHumidity();
	
	temp=a?a:temp;
	humidity=b?b:humidity;
	printf("data pre-write:: temp=%f humidity=%f\n",temp, humidity);
	dc->store(temp,humidity);
//	dc->read();
	
	while(1)
	{
		
		if(tc->getState() && !switch_lock)
		{
				display_state++;
				switch_lock=1;
					
				
			if(display_state>2 || display_state<0)
				display_state=0;
				
			switch(display_state)
			{
				case 0: useImperialUnits=1; readHumidity=0; break;
				case 1: useImperialUnits=0; readHumidity=0; break;
				case 2: useImperialUnits=0; readHumidity=1; break;
			}
		
		}
		else if(!tc->getState())
			switch_lock=0;
			
				
		
		if(sensor->read())
		{
			temp=sensor->getTempCelcius();
			humidity = sensor-> getHumidity();
			
		
	
		if(!readHumidity)
		{
			//display temperature
			if(useImperialUnits)
			{
				temp=sensor->getTempFarenheight();
				left->display(temp/10);
				right->display((int)temp%10);//display the lower portion of the temperature
				
				red->turn_on();
				blue->turn_off();
			}
			else
			{
				left->display(temp/10);
				right->display((int)temp%10);//display the lower portion of the temperature
				
				red->turn_off();
				blue->turn_on();
			}
		}
		else
		{
			humidity = sensor->getHumidity();
			left -> display(humidity/10);
			right -> display ((int)humidity%10);
				
			red->turn_on();
			blue->turn_on();	
			
		}	
		
		}
			
	}
}

void flashSegment(seg_display *a)
{
	int i=0;
	for(;i<2; i++)
	{
		a->clear_all();
		delay(700);
		a->set_all();
		delay(700);
	}
	
	a->clear_all();
}

void flashGumdrop(gumdrop *a)
{
	int i=0;
	for(;i<2;i++)
	{
		a->turn_off();
		delay(700);
		a->turn_on();
		delay(700);
		
	}
	
	a->turn_off();
	
}

