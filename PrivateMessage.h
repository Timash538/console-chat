#pragma once
#include <string>
#include <iostream>
#include "User.h"

using namespace std;

class PrivateMessage
{
private:
	int _numMessage;
	string _message;
	string _sendFrom;
	string _sendTo;
	bool _isItPrinted{false};
public:
	// Конструкторы:
	PrivateMessage();
	PrivateMessage(int, string&&, string&&, string&&);

	// Деструктор
	~PrivateMessage()=default;

	// Сеттеры:
	void setNumMessage(int);
	void setMessage(string&&);
	void setSendFrom(string&&);
	void setSendTo(string&&);

	//Геттеры:
	int getNumMessage() const;
	string* getMessage();
	string* getSendFrom();
	string* getSendTo();
	bool isItPrinted() const;
	 // Вывод сообщения
	void printMessage();
	// Читаем сообщение с консоли
	void readMessage(User* , User* );
};

