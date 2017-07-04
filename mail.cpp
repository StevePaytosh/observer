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
	msg="echo \""+default_body+"\" | mail -s \"" + default_subject + "\" "+default_send_to+" ";
	system(msg.c_str());
}

void mail::send(std::string send_to, std::string subject, std::string body)
{
	std::string msg;
	//create some form of validation
	msg="echo \""+body+"\" | mail -s \"" + subject + "\" "+send_to+" ";
	system(msg.c_str());
}

void mail::setDefaultSendTo(std::string sendTo)
{ default_send_to=sendTo;}

void mail::setDefaultBody(std::string body)
{ default_body = body;}

void mail::setDefaultSubject(std::string subject)
{default_subject=subject;}
