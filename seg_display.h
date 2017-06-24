#include <string>
#include "GPIOClass.h"

class seg_display
{
public:
seg_display();
seg_display(std::string tl, std::string t, std::string tr, std::string br, std::string b, std::string bl, std::string m, std::string d, int sans_flag=0, int common=0);
seg_display(int tl, int t, int tr, int br, int b, int bl, int m, int d, int sans_flag=0, int common=0);
int set(std::string a, int b);
int set(int a, int b);
int init(std::string tl, std::string t, std::string tr, std::string br, std::string b, std::string bl, std::string m, std::string d);
int assign(int led_num, int on);
int getCurrentState(int pin_num);
int getCurrentState(std::string pin_name);
int turn_on(int a);
int turn_off(int a);
int display(int num, int font=0);
void clear_all();
void set_all();
void set_sans(int sans_flag);
void set_common(int common);
int sans;
int active;

private:
GPIOClass* TOP_LEFT;
GPIOClass* TOP;
GPIOClass* TOP_RIGHT;
GPIOClass* BOTTOM_RIGHT;
GPIOClass* BOTTOM;
GPIOClass* BOTTOM_LEFT; 
GPIOClass* MIDDLE ;
GPIOClass* DOT;
GPIOClass* getLEDByNumber(int num);
void set_zero(int font = 0);
void set_one(int font = 0);
void set_two(int font =0);
void set_three(int font=0);
void set_four(int font=0);
void set_five(int font=0);
void set_six(int font=0);
void set_seven(int font=0);
void set_eight(int font=0);
void set_nine(int font=0);



};
