#include "PrivateMessage.h"

PrivateMessage::PrivateMessage()
{
	_numMessage = -1;
}

PrivateMessage::PrivateMessage(int numMessage, string&& message, string&& sendFrom, string&& sendTo)
{
	_numMessage = numMessage;
	_message = message;
	_sendFrom = sendFrom;
	_sendTo = sendTo;
}

void PrivateMessage::setNumMessage(int numMessage)
{
	_numMessage = numMessage;
}

void PrivateMessage::setMessage(string&& message)
{
	_message = message;
}

void PrivateMessage::setSendFrom(string&& sendFrom)
{
	_sendFrom = sendFrom;
}

void PrivateMessage::setSendTo(string&& sendTo)
{
	_sendTo = sendTo;
}
 
int PrivateMessage::getNumMessage() const
{
	return _numMessage;
}

string* PrivateMessage::getMessage() 
{
	return &_message;
}

string* PrivateMessage::getSendFrom()
{
	return &_sendFrom;
}

string* PrivateMessage::getSendTo()
{
	return &_sendTo;
}

bool PrivateMessage::isItPrinted() const
{
	return _isItPrinted;
}

void PrivateMessage::printMessage()
{
	cout << "Вам новое сообщение:\n";
	cout << "Отправитель " <<_sendFrom << ": " << _message << endl;
	_isItPrinted = true;
}

void PrivateMessage::readMessage(User* pUserFrom, User* pUserTo)
{
	cout << "Получатель " << pUserTo->getNickname() << ": Введите сообщение : ";
	string input;
	getline(cin, input);

	_message = input;
	_sendFrom  = pUserFrom->getNickname();
	_sendTo = pUserTo->getNickname();
}
