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


 int main (void)
{
	seg_display *right= new seg_display("27","15","17","14","22","2","3","18");
	seg_display *left = new seg_display(); //this segment not yet wired
	temp_sensor *sensor = new temp_sensor();
	
	int temp=sensor->getTempCelcius();
	int humidity = sensor -> getHumidity();
	int res=0;
	
	printf("test: temp= %d",temp);
	while(1)
	{
		if(sensor->read())
		{
			temp=sensor->getTempCelcius();
			humidity = sensor-> getHumidity();
			
			//left->display(temp/10);
			right->display(temp%10);//display the lower portion of the temperature
		}
		
		delay(3000);
			
	}
}


