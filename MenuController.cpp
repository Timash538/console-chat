#include "MenuController.h"
#include <iostream>

bool isStringNum(std::string);
void pressEnter(std::string);

MenuController::MenuController(std::unique_ptr<UserManager> uM,std::unique_ptr<ChatManager> cM) 
{
    _uM = std::move(uM);
    _cM = std::move(cM);
}

void MenuController::startMenu()
{
    
	char choice = '0';
	while (choice != 3)
	{
        system("cls");
		std::cout << "�������� ���� �� ��������� ������� ���������:\n1 - ����������� ������ ������������.\n2 - ���� ������������������� ������������.\n3 - ��������� ������ ���������.\n������� ����� ������������ ��������: ";

		std::cin >> choice;

		switch (choice)
		{
		case '1':
			userRegistration();
			break;
		case '2':
			login();
			break;
		case '3':
			return;
		default:
            pressEnter("������ �����.");
		}
	}
}

void MenuController::userRegistration()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
    std::cout << "\n\n����������� ������ ������������:\n\n";
    std::string log{ "" };
    std::string name{ "" };
    std::string pass{ "" };
    std::string currentString{ "" };

    std::cout << "��� ������ �� ������ �����������, ������� '!' � 'ENTER'.\n";
    std::cout << "����� (��������� �����, ����� � ���� ������� �������������): ";
    bool badInput = false;
    while (true)
    {
        badInput = false;
        getline(std::cin, currentString);
        if (currentString == "!")
        {
            return;
        }

        if (currentString.length() == 0)
        {
            std::cout << "\n\n������ ������ �� ����� ���� �������! ��������� ������� ��� ������� �� �����������.\n\n";
            continue;
        }
        for (auto& c : currentString)                             // �������� ������������ ��������� ��������
        {
            if (!((c <= 57 && c >= 48) ||                     // ������ - �����
                (c <= 90 && c >= 65) ||                     // ������ ��������� ��������� �����
                (c <= 122 && c >= 97) ||                     // ������ ��������� ��������� �����
                (c == 95)))                                  // ������ ������ �������������
            {
                std::cout << "\n\n� ���������, � ������ ������� ������������ �������. \n����������� ������ ����� ������.\n\n";
                badInput = true;
                break;
            }
        }                             //��� ������� ����������, ��������� �� ������������ ������
        if (_uM->findUserByLogin(move(currentString)))
        {
            std::cout << "������������ � ���� ������� ��� ���������������, ���������� ������ �����.\n\n";
            continue;
        }
        if (!badInput)
        {
            log = currentString;
            break;
        }
    }
    while (true)
    {
        badInput = false;
        std::cout << "��� (������� �����, ����� � ���� ������� �������������): ";

        getline(std::cin, currentString);
        if (currentString == "!")
        {
            return;
        }

        if (currentString.length() == 0)
        {
            std:: cout << "\n\n������ ������ �� ����� ���� ������! ��������� ������� ��� ������� �� �����������.\n\n";
            continue;
        }

        for (auto& c : currentString)                             // �������� ������������ ��������� ��������
        {
            if (!((c <= 57 && c >= 48) ||                     // ������ - �����
                (c <= -38 && c >= -64) ||                     // ������ ������� ����� �-�
                (c <= -6 && c >= -36) ||                     // ������ ������� ����� �-�
                (c <= -1 && c >= -4) ||                     // ������ ������� ����� �-�
                c == -88 || c == -72 ||                     // ������� �, �
                c == -5 || c == -37 ||                     // ������� �, �
                (c == 95)))                                   // ������ ������ �������������
            {
                std::cout << "� ���������, � ����� ������� ������������ �������. \n���������� ������ ��� ���.\n\n";
                badInput = true;
                break;
            }
        }
        if (_uM->findUserByNickname(move(currentString)))
        {
            std::cout << "������������ � ���� ������ ��� ���������������, ���������� ������ ���:)))))).\n";
            continue;
        }
        if (!badInput)
        {
            name = currentString;
            break;
        }
    }

    while (true)
    {
        badInput = false;
        std::cout << "������ (��������� �����, ����� � \n����������� �����, ����� ������� � ���������������� �����): ";

        getline(std::cin, currentString);
        if (currentString == "!")
        {
            return;
        }

        if (currentString.length() == 0)
        {
            std::cout << "\n\n������ ������ �� ����� ���� �������! ��������� ������� ��� ������� �� �����������.\n\n";
            continue;
        }

        for (auto& c : currentString)                             // �������� ������������ ��������� ��������
        {
            if (!(c <= 126 && c >= 34) or c == '!' or c == ' ')                  // ��� �������� ������� ������ �������� ASCII ����� ! � �������
            {
                std::cout << "\n������ �����������! ��� ������ ������ �������� ������.\n����������� ������ ������ ������: ";
                badInput = true;
                break;
            }

        }
        if (!badInput)
        {
            pass = currentString;
            break;
        }
    }

    _uM->addUser(User(log, name, pass));
    system("cls");
    std::cout << "����� ������������ '" << name << "' ������� ���������������.\n\n";
    _cM->addUserToChat(_uM->getCount() - 1, 0); // ������� ������������ � ����� ���.
}

void MenuController::login()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
    std::cout << "���� � �������\n";
    std::string log{ "" };
    std::string pass{ "" };
    std::string currentString{ "" };

    std::cout << "��� ������ �� ������ �����, ������� '!' � 'ENTER'.\n";
    while (true)
    {

        std::cout << "�����: ";
        getline(std::cin, currentString);
        if (currentString == "!") return;
        log = currentString;

        std::cout << "������: ";
        getline(std::cin, currentString);
        if (currentString == "!") return;
        pass = currentString;

        if (_uM->loginUser(move(log), move(pass)))
        {
            userMenu();
            return;
        }
    }
}

void MenuController::userMenu()
{
    
    while (true)
    {
        system("cls");
        _cM->showAllUserChats(_uM->getCurrentUserID(), *_uM);

        std::cout << "\n\n" << _uM->getCurrentUser().getNickname() << ", ��������� ��������:\n";
        std::cout << "������� ID ����, ����� ����� � ����.\n������� N, ����� ������� ����� ���.\n������� ! ����� �������������.\n";

        std::string currentString;
        getline(std::cin, currentString);
        if (currentString == "!")
        {
            return;
        }
        if (currentString == "N")
        {
            newChatMenu();
            continue;
        }

        if (!isStringNum(currentString)) continue;
        int idx = -1;
        _cM->findUserToChatLink(_uM->getCurrentUserID(), idx);
        unsigned int id = atoi(currentString.c_str());
        if (id >= _cM->getLinks()[idx]._chats.getCount())
        {
            pressEnter("��� ������ ID.");
            continue;
        }
        
        chatMenu(id);
    }
}

void MenuController::newChatMenu()
{
    while (true)
    {
        system("cls");
        std::cout << "�������� ��� ������ ����.\n1 - ��������� ���\n2 - ��������� ���.\n! - ��������� � ���� ������������.\n";
        char choice = '0';
        std::cin >> choice;
        if (choice != '1' && choice != '2')
        {
            std::cout << "�������� 1 ��� 2. ������� ENTER, ����� ����������.\n";
            continue;
        }

        unsigned int type = (unsigned int)choice - (int)'0';
        std::cout << "�������� ID ������������, � ������� ������ ������ ���.\n! - ��������� � ���� ������������.\nb - ��������� � ������ ���� ����.\n";
        _uM->showUsersExcludingCurrent();
        std::string strID;
        std::cin >> strID;
        if (strID == "!") return;
        if (strID == "b") continue;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (!isStringNum(strID)) continue;
        unsigned int id = atoi(strID.c_str());
        if (id == _uM->getCurrentUserID() || id >= _uM->getCount())
        {
            pressEnter("��� ������ ID.");
            continue;
        }
        _cM->addNewChat(ChatType(type), _uM->getCurrentUserID());
        _cM->addUserToLastChat(id);
       
        
        std::cout << "������ " << ((type == 1) ? "��������� " : "��������� ") << "��� � ������������� " << _uM->getUser(id).getNickname() << ".\n";
        pressEnter("");
        return;
    }
}

void MenuController::chatMenu(unsigned int id)
{
    int chatID = getRealChatID(id);
    while (true)
    {
        system("cls");
        _cM->updateUserPtrToLastMsg(_uM->getCurrentUserID(), id);

        std::cout << "������ ";
        switch (_cM->getChat(chatID)._type)
        {
        case 0:
            std::cout << "����� ";
            break;
        case 1:
            std::cout << "��������� ";
            break;
        case 2:
            std::cout << "������ ";
            break;
        default:
            break;
        }
        std::cout << "���.\n";
        std::cout << "��������� ����: ";

        for (int i = 0; i < _cM->getChat(chatID)._users.getCount(); i++)
        {
            std::cout << _uM->getUser(_cM->getChat(chatID)._users.get(i)).getNickname() << ((i == _cM->getChat(chatID)._users.getCount() - 1) ? ".\n\n" : ", ");
        }
        if (_cM->getChat(chatID)._messages.isEmpty())
        {
            std::cout << "��� ���������, ���������� ���-������ ��������.\n\n";
        }
        _cM->showMessages(chatID);
        std::cout << "\n";

        std::cout << "������� ���������. \n��� ������ �� ����, ������� '!' � 'ENTER'.\n";
        if (_cM->getChat(chatID)._type == GROUP) std::cout << "����� �������� ������ ������������ ������� /add\n\n";
        std::string message;
        std::getline(std::cin, message, '\n');
        if (message == "!") return;
        else if (message == "/add" && _cM->getChat(chatID)._type == GROUP)
        {
            addUserToChatMenu(chatID);
            continue;
        }
        else
        {
            _cM->getChat(chatID)._messages.add(Message(_uM->getCurrentUser(), message));
            _cM->updateUserPtrToLastMsg(_uM->getCurrentUserID(), id);
        }
    }
}

void MenuController::addUserToChatMenu(unsigned int chatID)
{
    while (true)
    {
        std::cout << "�������� ID ������������, � ������� ������ ������ ���.\n! - ��������� � ���� ������������.\n";
        Array<int> usersIDInChat = _cM->getUsersIDFromChat(chatID);
        _uM->showUsersExcluding(std::move(usersIDInChat));
        std::string strID;
        getline(std::cin, strID);
        if (strID == "!") return;
        if (!isStringNum(strID)) continue;
        unsigned int id = atoi(strID.c_str());
        bool f = false;
        for (int i = 0; i < usersIDInChat.getCount(); i++)
        {
            if (id == usersIDInChat[i])
            {
                f = true;
            }
            if (f) break;
        }
        if (id >= _uM->getCount() || f)
        {
            pressEnter("��� ������ ID.");
            continue;
        }
        else
        _cM->addUserToChat(id, chatID);
        continue;
    }
}

int MenuController::getRealChatID(unsigned int id) //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!���������� link� � chats � ChatManager!!!!!!!
{
    int idx = -1;
    _cM->findUserToChatLink(_uM->getCurrentUserID(), idx);
    return _cM->getLinks()[idx]._chats[id];
}

UserManager& MenuController::getUM()
{
    return *_uM;
}

ChatManager& MenuController::getCM()
{
    return *_cM;
}

void pressEnter(std::string str)
{
    std::cout << str << " ������� ENTER, ����� ����������.";
    getline(std::cin, str);
}

bool isStringNum(std::string str)
{
    for (auto& c : str)
    {
        if (!(c <= 57 && c >= 48))
        {
            pressEnter("������ � �����.");
            return false;
        }
    }
    return true;
}

