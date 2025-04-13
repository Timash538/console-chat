#pragma once
#include <string>

using namespace std;

class CommonMessage
{
private:
	unsigned int _numMessage;
	string _message;
	string _sendFrom;
public:
	//Конструкторы
	CommonMessage();
	CommonMessage(int, string&, string&);
	//Деструктор
	~CommonMessage();
	//Геттеры
	int getNumMessage() const;
	string getMessage() const;
	string getSendFrom() const;
	//Сеттеры
	void setNumMessage(int);
	void setMessage(string);
	void setSendFrom(string);

};

