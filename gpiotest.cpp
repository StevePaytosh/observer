#include "gpiotest.h"
#include "seg_display.h"
#include "temp_sensor.h"
#define	LED 2


/*
 * blink.c:
 *	Standard "blink" program in wiringPi. Blinks an LED connected
 *	to the first GPIO pin.
 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */



// LED Pin - wiringPi pin 0 is BCM_GPIO 17.

void run()
{
printf ("Raspberry Pi blink\n") ;

  wiringPiSetup () ;
  pinMode (LED, OUTPUT) ;
  
  for (;;)
  {
    digitalWrite (LED, HIGH) ;	// On
    delay (500) ;		// mS
    digitalWrite (LED, LOW) ;	// Off
    delay (500) ;
  }
 
 printf("end of blink program\n");
 
}

int readTemp()
{
	return 0;
}

void run2()
{
	//same test as run but using a different library
	
	printf ("Raspberry Pi blink 2.2\n") ;

	//BCM 25
	GPIOClass* gpio25 = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO1
	gpio25->export_gpio(); //export GPIO
	gpio25->setdir_gpio("out"); // GPIO25 set to input
  //wiringPiSetup () ;
  //pinMode (LED, OUTPUT) ;
  
  for (;;)
  {
    //digitalWrite (LED, HIGH) ;	// On
     gpio25->setval_gpio("1");
    delay (500) ;		// mS
    //digitalWrite (LED, LOW) ;	// Off
      gpio25->setval_gpio("0");
    delay (500) ;
   
  }
 
 printf("end of blink 2 program\n");
 
	
}

void runNumberTest()
{
	//sets up an led, and cyles between 0 and 3 on the display
	//config: m=3, tl = 27, t=15, tr=17, dot=18, br=14, b=4, bl=2
	seg_display *seg1 = new seg_display("27","15","17","14","22","2","3","18");
	
	for(;;)
	{
		seg1 -> display(0);
		delay(500);
		seg1-> display(1);
		delay(500);
		seg1-> display(2);
		delay(500);
		seg1-> display(3);
		delay(500);
		seg1-> display(4);
		delay(500);
		seg1-> display(5);
		delay(500);
		seg1-> display(6);
		delay(500);
		seg1-> display(7,1);
		delay(500);
		seg1-> display(8);
		delay(500);
		seg1-> display(9);
		delay(500);
	}
	
}

void blinkSegment()
{
	printf("\nsegment blinking test:\n");
	seg_display *seg1 = new seg_display("22","3","4","14","15","2","17","18");
	
		for(;;)
	{
		seg1->turn_on(1);
		seg1->turn_on(2);
		seg1->turn_on(3);
		seg1->turn_on(4);
		seg1->turn_on(5);
		seg1->turn_on(6);
		seg1->turn_on(7);
		seg1->turn_on(8);
		delay(500);
		seg1->turn_off(1);
		seg1->turn_off(2);
		seg1->turn_off(3);
		seg1->turn_off(4);
		seg1->turn_off(5);
		seg1->turn_off(6);
		seg1->turn_off(7);
		seg1->turn_off(8);
		delay(500);
	}
	
}

void testOdds()
{
	
	//test pins that are always high
	
	printf ("Test odd pins:\n") ;

	//BCM 25
	GPIOClass* gpio0= new GPIOClass("27"); //create new GPIO object to be attached to  GPIO1
	gpio0->export_gpio(); //export GPIO
	gpio0->setdir_gpio("out"); // GPIO0 set to output
  //wiringPiSetup () ;
 // pinMode (LED, OUTPUT) ;
  
  for (;;)
  {
    //digitalWrite (LED, HIGH) ;	// On
     gpio0->setval_gpio("1");
    delay (500) ;		// mS
    //digitalWrite (LED, LOW) ;	// Off
    gpio0->setval_gpio("0");
    delay (500) ;
   
  }
 
 printf("end of blink 2 program\n");
}

void tempTest()
{
	
	temp_sensor *ts= new temp_sensor();
	
	//ts->dht11_read_val();
	while(1)
	{
		int temp=ts->read();
		delay(3000); 
	}
	//printf("sensor returned %d on read\n",temp);
	//~ts();
	//printf("Interfacing Temperature and Humidity Sensor (DHT11) With Raspberry Pi\n");  
  //if(wiringPiSetup()==-1)  
    //return; 
  //while(1)  
  //{  
     //dht11_read_val();  
     //delay(3000);  
  //} 
}
