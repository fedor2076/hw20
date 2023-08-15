#pragma once
#include"user.h"

class Message
{
public:
	Message(const std::string& sender, const std::string& recipient, const std::string& letter);
	~Message() = default;

	std::string getSender() const;
	std::string getRecipient() const;
	std::string getLetter() const;

private:
	const std::string _sender;
	const std::string _recipient;
	const std::string _letter;

};
