#include <iostream>
#include <Windows.h>
#include <memory>
#include "PrivateMessage.h"
#include "CommonMessage.h"
#include "Array.h"
#include "User.h"
#include "ConversationManager.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Array <PrivateMessage> privateMessagePool;
	Array <CommonMessage> commonMessagePool;
	Array <User> allUsers;
	bool isRun = true;

	//���������� ����� ���������:
	unique_ptr<ConversationManager> cm{ make_unique<ConversationManager>() };		//������� ��������� ��������� ������ ������ � �������������
	cm->greeting();
	bool isItNextLoop = false;
	int uNum{-1};
	while (isRun)
	{
		char choice = cm->regOrComm();
		switch (choice)
		{
		case '1':
			if (isItNextLoop)
				cm->cleanConsole();
			cm->userRegistration(allUsers);
			isItNextLoop = true;
			break;
		case '2':
			uNum = cm->usersInput(allUsers);
			if (uNum > -1)
			{
				User user = allUsers[uNum];
				cm->userMessChoise(user, allUsers, privateMessagePool, commonMessagePool);
			}
			break;
		case '3':
			std::cout << "\n\n������ ��������� ���������.\n";
			isRun = false;
			break;
		}
	}


	
	// 1. ����� ������������ ���������� ������ ������������

	// 2. ����� ����� ������������, ��������� ����������� 
	// 
	// ������� ������� � ������� ����� ��������� � ������� ���������, ���� ����.
	// ����� �� �� �������� ��������� ����, ���� ��� - ���������� ���������������� ��� ������ ������������

	// ���� �� - ����� 1 ���� ��� - ����� 3
	//3. ���� ��������� � �������� - ����, ������� �� � ������ "����� ���������"
	//3.1 ����������, ������ �� �������� ��� ���������. ���� ��� - ����� �� ��������� ����������� ������������ ��� ������ ������������

	//4. ������ - ����� ������������

	//5. ��������� ������ ���������

	//6. ���� ����� ���������� - ��� ����� ��� ��������� 

	//7.
	/*
	User* ptrUserFrom = new User("logKol", "����","100");
	User* ptrUserTo = new User("logSas", "����", "101");

	
	PrivateMessage* ptrMes = new PrivateMessage;
	
	ptrMes->readMessage(ptrUserFrom, ptrUserTo);
	//������� ����� ��������� � ���������
	int lstCount = messagePool.getCount();
	ptrMes->setNumMessage(lstCount);
	//������� � ������ ���������
	messagePool.add(move( *ptrMes));
	delete ptrMes;

	// ������� ��������� �� ������� � ������� �� �������
	PrivateMessage mes = messagePool[0];
	mes.printMessage();

	cout << "������ ���!" << endl;
	
	delete ptrUserFrom;
	delete ptrUserTo;
	*/
	return 0;
}