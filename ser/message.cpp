#include "message.h"

Message::Message(const std::string& sender, const std::string& recipient, const std::string& letter) : _sender(sender), _recipient(recipient), _letter(letter)
{
}

std::string Message::getSender() const
{
	return _sender;
}
std::string  Message::getRecipient() const
{
	return _recipient;
}
std::string  Message::getLetter() const
{
	return _letter;
}
