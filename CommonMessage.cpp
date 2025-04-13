#include "CommonMessage.h"

CommonMessage::CommonMessage()
{
	_numMessage = 0;
}

CommonMessage::CommonMessage(int numMessage, string& message, string& sendFrom)
{
	_numMessage = numMessage;
	_message = message;
	_sendFrom = sendFrom;
}

CommonMessage::~CommonMessage()
{
}

int CommonMessage::getNumMessage() const
{
	return _numMessage;
}

string CommonMessage::getMessage() const
{
	return _message;
}

string CommonMessage::getSendFrom() const
{
	return _sendFrom;
}

void CommonMessage::setNumMessage(int num)
{
	_numMessage = num;
}

void CommonMessage::setMessage(string message)
{
	_message = message;
}

void CommonMessage::setSendFrom(string sendFrom)
{
	_sendFrom = sendFrom;
}
