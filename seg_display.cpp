#include "seg_display.h"

	
seg_display::seg_display()
{
	//initializing a logical segment display with nothing
}	

seg_display::seg_display(std::string tl, std::string t, std::string tr, std::string br, std::string b, std::string bl, std::string m, std::string d)
{
	//initializes a logical segment display with the pin number for each pin assigned by the string
	TOP_LEFT=new GPIOClass(tl);
	TOP=new GPIOClass(t);
	TOP_RIGHT=new GPIOClass(tr);
	BOTTOM_RIGHT=new GPIOClass(br);
	BOTTOM=new GPIOClass(b);
	BOTTOM_LEFT=new GPIOClass(bl);
	MIDDLE=new GPIOClass(m);
	DOT=new GPIOClass(d);
	
	TOP_LEFT->export_gpio(); 
	TOP_LEFT->setdir_gpio("out");
	
	TOP->export_gpio(); 
	TOP->setdir_gpio("out");
	
	TOP_RIGHT->export_gpio(); 
	TOP_RIGHT->setdir_gpio("out");
	
	BOTTOM_RIGHT->export_gpio(); 
	BOTTOM_RIGHT->setdir_gpio("out");
	
	BOTTOM->export_gpio(); 
	BOTTOM->setdir_gpio("out");
	
	BOTTOM_LEFT->export_gpio(); 
	BOTTOM_LEFT->setdir_gpio("out");
	
	MIDDLE->export_gpio(); 
	MIDDLE->setdir_gpio("out");
	
	MIDDLE->export_gpio(); 
	MIDDLE->setdir_gpio("out");
	 
}

GPIOClass* seg_display::getLEDByNumber(int num)
{
	//retrieve the LED by position number
	
	switch(num)
	{
		case 1: return TOP_LEFT; break;
		case 2: return TOP; break;
		case 3: return TOP_RIGHT; break;
		case 4: return BOTTOM_RIGHT; break;
		case 5: return BOTTOM; break;
		case 6: return BOTTOM_LEFT; break;
		case 7: return MIDDLE; break;
		case 8: return DOT; break;
		Default: return new GPIOClass(); break;
		
	}
	
}

int seg_display::assign (int num, int value)
{
	GPIOClass *reff = getLEDByNumber(num);
	
	if(reff != NULL)
	{
		if(value)
			{
				reff->setval_gpio("1");
				return 1;
			}
		else
			{
				reff->setval_gpio("0");
				return 1;
			}
	}
	return 0;
	
}

int seg_display::turn_on(int a)
{
	return assign(a,1);
}
int seg_display::turn_off(int a)
{
	return assign(a,0);
}

int seg_display::display(int a)
{
	//displays the given number on the segment_display
	
	if(a>10 || a<0)
		return 0; //invalid number return false
		

	turn_off(1);
	turn_off(2);
	turn_off(3);
	turn_off(4);
	turn_off(5);
	turn_off(6);
	turn_off(7);
	turn_off(8);
	
	switch(a)
	{
		case 0: set_zero(); return 1; break;
		case 1: set_one(); return 1; break;
		case 2: set_two(); return 1; break;
		case 3: set_three(); return 1; break;
		case 4: set_four(); return 1; break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		default: return 0;
	}
	
}

void seg_display::set_zero(int sans)
{
	//writes out "0" to the segment display
	//top, top right, bottom right, bottom, bottom left, top left
	turn_on(1);
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(5);
	turn_on(6);
}

void seg_display::set_one(int sans)
{
	//writes out "1" to the segment display
	turn_on(3);
	turn_on(4);
}

void seg_display::set_two(int sans)
{
	//writes out "2" to the segment display
	turn_on(2);
	turn_on(3);
	turn_on(7);
	turn_on(5);
	turn_on(6);
}

void seg_display::set_three(int sans)
{
	//writes out "3" to the segment display
	//top,top right, bottom right, bottom, middle
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(5);
	turn_on(7);	
}

void seg_display::set_four(int sans)
{
	//writes out "4" to the segment display
	turn_on(1);
	turn_on(3);
	turn_on(4);
	turn_on(7);
	
}
