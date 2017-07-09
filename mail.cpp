#include "mail.h"

mail::mail(std::string send_to, std::string subject, std::string body)
{
	default_send_to=send_to;
	default_body=body;
	default_subject=subject;
}

void mail::send()
{
	std::string msg;
	//create some form of validation
	msg="echo \""+default_body+" | mail -s \"$(echo  '" +default_subject+ " \\nContent-Type: text/html\\nMime-Version: 1.0')\" -r SunLabObserver"+default_send_to+" "; 
	system(msg.c_str());
}

void mail::send(std::string send_to, std::string subject, std::string body)
{
	std::string msg;
	//create some form of validation
	msg="echo \""+body+"\" | mail -s \"$(echo '" +subject+ " \\nContent-Type: text/html\\nMime-Version: 1.0')\" -r SunLabObserver "+send_to+" "; 
	system(msg.c_str());
	//printf("%s\n",msg.c_str());
}

void mail::setDefaultSendTo(std::string sendTo)
{ default_send_to=sendTo;}

void mail::setDefaultBody(std::string body)
{ default_body = body;}

void mail::setDefaultSubject(std::string subject)
{default_subject=subject;}
