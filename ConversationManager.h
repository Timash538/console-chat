#pragma once
#include <iostream>
#include <conio.h> // ���������� getch
#include <ios>		// for <streamsize>
#include <limits>	// for numeric_limits

#include "User.h"
#include "Array.h"
#include "PrivateMessage.h"
#include "CommonMessage.h"

class ConversationManager
{
public:
	void cleanConsole();
	void greeting();								//��������� ����������� ������������
	char regOrComm();								//���� ������ ����������� ������ ��������� ��� �������
	bool userRegistration(Array<User>&);			//������ ����������� ������ ������������
	int usersInput(Array<User>&);					//���� ������������������� ������������
	void userMessChoise(User&, Array<PrivateMessage>&, Array<CommonMessage>&);		//����� ����� ���������� ��������� ��������� � ������� ����� ���������
	
};

