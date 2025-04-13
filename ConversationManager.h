#pragma once
#include <iostream>
#include <conio.h> // подключаем getch
#include <ios>		// for <streamsize>
#include <limits>	// for numeric_limits

#include "User.h"
#include "Array.h"
#include "Message.h"
#include "getRightInt.cpp"

class ConversationManager
{
public:
	// онструкторы
	ConversationManager();
	ConversationManager(Array <User>&, Array <Message>&, Array <Message>&);
	
	void cleanConsole();
	void start();
	void greeting();																//Ќачальное приветствие пользовател€
	char regOrComm();																//ћеню выбора регистрации нового участника или общени€
	bool userRegistration(Array<User>&);											//ƒиалог регистрации нового пользовател€
	int usersInput(Array<User>&);													//¬ход зарегистрированного пользовател€
	void userMessChoise(User&, Array<User>&, Array<Message>&, Array<Message>&);		//выбор между прочтением пришедших сообщений и набором новых сообщений
	
	void outputPrivateMesage(Array<Message>&, User&);								//¬ывод на консоль сообщений из личного чата
	void outputCommonMessage(Array<Message>&);										//¬ывод на консоль сообщений из общего чата
	void inputPrivateMessage(Array<User>& , User& , Array<Message>& );				//«апись сообщени€ в личтный чат
	void inputCommonMessage(Array<Message>& , std::string& );						//«апись сообщени€ в общий чат
	int amountPrivateMessage(Array<Message>& , std::string& );						// оличество личных сообщений дл€ одного пользовател€

	Array <Message> privateMessagePool;
	Array <Message> commonMessagePool;
	Array <User> allUsers;
};

