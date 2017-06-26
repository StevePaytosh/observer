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
#include "config.h"
void flashNotification(gumdrop *a, gumdrop *b);
void diagnostic( gumdrop *a, gumdrop *b, seg_display *l, seg_display *r); 

 int main (void)
{

	seg_display *right = new seg_display(LEFT_SEG_TOP_LEFT,LEFT_SEG_TOP,LEFT_SEG_TOP_RIGHT,LEFT_SEG_BOTTOM_RIGHT,LEFT_SEG_BOTTOM,LEFT_SEG_BOTTOM_LEFT,LEFT_SEG_MIDDLE,LEFT_SEG_DOT, LEFT_SEG_SANS, LEFT_SEG_COMMON);
	seg_display *left = new seg_display(RIGHT_SEG_TOP_LEFT,RIGHT_SEG_TOP,RIGHT_SEG_TOP_RIGHT,RIGHT_SEG_BOTTOM_RIGHT,RIGHT_SEG_BOTTOM,RIGHT_SEG_BOTTOM_LEFT,RIGHT_SEG_MIDDLE,RIGHT_SEG_DOT, RIGHT_SEG_SANS, RIGHT_SEG_COMMON);
	temp_sensor *sensor = new temp_sensor(DTH11PIN);
	tact_switch *tc= new tact_switch(TACT_SWITCH,TACT_SWITCH_ACTIVE);
	gumdrop *red= new gumdrop(RED_GUMDROP);
	gumdrop *blue = new gumdrop(BLUE_GUMDROP);
	data_controller *dc = new data_controller(FILE_PATH);

	int switch_lock=0; //indicates if the switch has hit zero since it was read as high
	int display_state=0; //determines what data should be displayed
	
	diagnostic(red,blue,left,right);
	
	float temp=0; //sensor->getTempCelcius();
	float humidity =0;// sensor -> getHumidity();
	int res=0;
	int useImperialUnits = 1;
	int readHumidity=0; // when this flag is high, print the humidity instead of the temperature
	
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
			
		if( difftime(time(0),dc->lastSampleTime() ) >= 30)
		{
			dc->store(temp,humidity);
			flashNotification(red,blue);
			
			long long int last_sample = dc->lastSampleTime();
			time_t ls=(time_t)last_sample;
			printf("sample time: %s\n",asctime(localtime(&ls)));
		}
			

	}
}


void diagnostic( gumdrop *a, gumdrop *b, seg_display *l, seg_display *r)
{
		l->clear_all();
		r->clear_all();
		
		l->set_all();
		r->set_all();
		delay(500);
		
		l->clear_all();
		r->clear_all();
		
		l->turn_on(7);
		r->turn_on(7);
		delay(200);
		l->turn_off(7);
		r->turn_off(7);
		
		l->turn_on(4);
		r->turn_on(4);
		delay(200);
		l->turn_off(4);
		r->turn_off(4);
		
		l->turn_on(5);
		r->turn_on(5);
		delay(200);
		l->turn_off(5);
		r->turn_off(5);
		
		l->turn_on(6);
		r->turn_on(6);
		delay(200);
		l->turn_off(6);
		r->turn_off(6);
		
		l->turn_on(1);
		r->turn_on(1);
		delay(200);
		l->turn_off(1);
		r->turn_off(1);
		
		l->turn_on(2);
		r->turn_on(2);
		delay(200);
		l->turn_off(2);
		r->turn_off(2);
		
		l->turn_on(3);
		r->turn_on(3);
		delay(200);
		l->turn_off(3);
		r->turn_off(3);
		
		l->turn_on(8);
		r->turn_on(8);
		delay(200);
		l->turn_off(8);
		r->turn_off(8);
		
		
		for(int i=0; i<4; i++)
		{
			delay(125);
			a->turn_on();
			b->turn_on();
			delay(125);
			a->turn_off();
			b->turn_off();
			
		}		
	
}

void flashNotification(gumdrop *a, gumdrop *b)
{
			a->turn_on();
			b->turn_on();
			delay(100);
			a->turn_off();
			b->turn_off();
			delay(100);
			a->turn_on();
			b->turn_on();
			delay(100);
			a->turn_off();
			b->turn_off();
}


