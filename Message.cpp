#include "Message.h"

Message::Message(User sender, std::string msg) : _sender(std::make_shared<User>(sender)), _msg(msg)
{
}

Message::Message(const Message& other) : _msg(other._msg), _sender(std::make_shared<User>(*(other._sender))) {}
Message::Message(Message&& other) noexcept : _msg(std::move(other._msg)), _sender(std::make_shared<User>(*(other._sender))) {}

void Message::setMessage(std::string& msg)
{
	_msg = msg;
}

void Message::setSender(User sender)
{
	_sender = std::make_shared<User>(sender);
}

std::string Message::getMessage()
{
	return _msg;
}

const User& Message::getSendFrom()
{
	return *_sender;
}

