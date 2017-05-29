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

int seg_display::display(int num,int font)
{
	//displays the given number on the segment_display
	
	if(num>10 || num<0)
		return 0; //invalid number return false
		

	clear_all();
	
	switch(num)
	{
		case 0: set_zero(); return 1; break;
		case 1: set_one(); return 1; break;
		case 2: set_two(); return 1; break;
		case 3: set_three(); return 1; break;
		case 4: set_four(); return 1; break;
		case 5: set_five(); return 1; break;
		case 6: set_six(); return 1; break;
		case 7: set_seven(font); return 1; break;
		case 8: set_eight(); return 1; break;
		case 9: set_nine(font); return 1; break;
		default: return 0;
	}
	
}

void seg_display::set_zero(int font)
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

void seg_display::set_one(int font)
{
	//writes out "1" to the segment display
	turn_on(3);
	turn_on(4);
}

void seg_display::set_two(int font)
{
	//writes out "2" to the segment display
	turn_on(2);
	turn_on(3);
	turn_on(7);
	turn_on(5);
	turn_on(6);
}

void seg_display::set_three(int font)
{
	//writes out "3" to the segment display
	//top,top right, bottom right, bottom, middle
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(5);
	turn_on(7);	
}

void seg_display::set_four(int font)
{
	//writes out "4" to the segment display
	turn_on(1);
	turn_on(3);
	turn_on(4);
	turn_on(7);
	
}

void seg_display::set_five(int font)
{
	//writes out "5" to the segment display
	turn_on(1);
	turn_on(2);
	turn_on(4);
	turn_on(5);
	turn_on(7);
	
}

void seg_display::set_six(int font)
{
	//writes out "6" to the segment display
	turn_on(1);
	turn_on(2);
	turn_on(4);
	turn_on(5);
	turn_on(6);
	turn_on(7);
	
	
}

void seg_display::set_seven(int font)
{
	//writes out "7" to the segment display
	turn_on(2);
	turn_on(3);
	turn_on(4);
	
	//if the sans flag is on, a seriff will print on the digit
	if(font)
		turn_on(1);
	
}

void seg_display::set_eight(int font)
{
	//writes out "8" to the segment display
	turn_on(1);
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(5);
	turn_on(6);
	turn_on(7);
}

void seg_display::set_nine(int font)
{
	//writes out "9" to the segment display
		turn_on(1);
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(7);
	
	//if sans flag is on, a seriff will print on the digit
	if(font)
		turn_on(5);
}

void seg_display::set_all()
{
	//turns on all LEDs in the segment
	turn_on(1);
	turn_on(2);
	turn_on(3);
	turn_on(4);
	turn_on(5);
	turn_on(6);
	turn_on(7);
	turn_on(8);
}

void seg_display::clear_all()
{
	turn_off(1);
	turn_off(2);
	turn_off(3);
	turn_off(4);
	turn_off(5);
	turn_off(6);
	turn_off(7);
	turn_off(8);
}

//int compare(seg_display *a)
//{
	////compare return 1 if this segment is "greater than" the a gven segment display (parameter)
	////if they are equal return 0 and -1 for less than.
	////First compare off of the unit number, if they are equal than by unit name. No name/number are treated as "less than" any other name/number
	
	//if(this.number != null || a.number != null)
	//{
		////if one of the segments has a number, we can compare
		//if(this.number == null && a.number != null)
			//return -1;
		//else if(a.number == null && this.number != null)
			//return 1;
		//else
		//{
			//if(this.number > a.number)
			//return 1;
			//else if (this. number < a.number)
			//return -1;
			//else
			//return 0;
		//}
	//}
	
	////if we could not compare on numbers, we must compare on name
	
	//if(this.name != null && a.name != null )
	//{
		////if of the segments has a name, we can compare
		//if(this.name == null && a.name != null)
			//return -1;
		//else if(a.name == null && this.name != null)
			//return 1;
		//else
		//{
			//return strcmp(this.name, a.name);
		//}
		
	//}
	//else
	//{
			//return 0;
	//}
	
//}
