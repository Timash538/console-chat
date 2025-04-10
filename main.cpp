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
			{
				cm->cleanConsole();
			}
			isItNextLoop = true;
			cm->userRegistration(allUsers);
			break;
		case '2':
			if (isItNextLoop)
			{
				cm->cleanConsole();
				isItNextLoop = true;
			}
			else
			{
				std::cout << "\n\n��� ������������������ �������������, ������� � �.1.\n\n";
				break;
			}
			uNum = cm->usersInput(allUsers);		//����� ��������������������� ������������ �� ������� Users
			if (uNum > -1)
			{
				User user = allUsers[uNum];			//�������� ������ ����� ������������
				cm->userMessChoise(user, allUsers, privateMessagePool, commonMessagePool);
			}
			break;
		case '3':
			std::cout << "\n\n������ ��������� ���������.\n";
			isRun = false;
			break;
		}
	}
	return 0;
}