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

GPIOClass* getLEDByNumber(int num)
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
