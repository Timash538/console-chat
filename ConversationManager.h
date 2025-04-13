#pragma once
#include <iostream>
#include <conio.h> // ���������� getch
#include <ios>		// for <streamsize>
#include <limits>	// for numeric_limits
#include <memory>	// ��� ����� ����������

#include "User.h"
#include "Array.h"
#include "Message.h"
#include "getRightInt.cpp"
#include "UserManager.h"

class ConversationManager
{
public:
	//������������
	ConversationManager();
	ConversationManager(Array <Message>&, Array <Message>&);
	
	void cleanConsole();
	void start();
	void greeting();																//��������� ����������� ������������
	char regOrComm();																//���� ������ ����������� ������ ��������� ��� �������
	bool userRegistration();											//������ ����������� ������ ������������
	int usersInput();													//���� ������������������� ������������
	void userMessChoise(User&, Array<Message>&, Array<Message>&);		//����� ����� ���������� ��������� ��������� � ������� ����� ���������
	
	void outputPrivateMesage(Array<Message>&, User&);								//����� �� ������� ��������� �� ������� ����
	void outputCommonMessage(Array<Message>&);										//����� �� ������� ��������� �� ������ ����
	void inputPrivateMessage(User& , Array<Message>& );				//������ ��������� � ������� ���
	void inputCommonMessage(Array<Message>& , std::string& );						//������ ��������� � ����� ���
	int amountPrivateMessage(Array<Message>& , std::string& );						//���������� ������ ��������� ��� ������ ������������

	Array <Message> privateMessagePool;
	Array <Message> commonMessagePool;
	UserManager allUsers;
};

