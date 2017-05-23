#include <string>
#include "GPIOClass.h"

class seg_display
{
public:
seg_display();
seg_display(std::string tl, std::string t, std::string tr, std::string br, std::string b, std::string bl, std::string m, std::string d);
void setUnitName(std::string n);
void setUnitNumber(int n);
int compare(seg_display *a);
int set(std::string a, int b);
int set(int a, int b);
int init(std::string tl, std::string t, std::string tr, std::string br, std::string b, std::string bl, std::string m, std::string d);
int assign(int led_num, std::string pin_num);
int getCurrentState(int pin_num);
int getCurrentState(std::string pin_name);

private:
GPIOClass* TOP_LEFT;
GPIOClass* TOP;
GPIOClass* TOP_RIGHT;
GPIOClass* BOTTOM_RIGHT;
GPIOClass* BOTTOM;
GPIOClass* BOTTOM_LEFT; 
GPIOClass* MIDDLE ;
GPIOClass* DOT;
int number;
std::string name;
GPIOClass* getLEDByNumber(int num);


};
