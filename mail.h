#include <string>

class mail
{
	public:
	mail(std::string send_to, std::string subject, std::string body);
	void send();
	void send(std::string send_to, std::string subject, std::string body);
	void setDefaultSendTo(std::string send_to);
	void setDefaultBody(std::string body);
	void setDefaultSubject(std::string subject);
	
	
	private:
	std::string default_send_to;
	std::string default_body;
	std::string default_subject;
};
