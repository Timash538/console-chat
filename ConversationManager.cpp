#include "ConversationManager.h"

void ConversationManager::cleanConsole()         // ������� �������
{
    system("cls");
}

void ConversationManager::greeting()
{
    this->cleanConsole();
	std::cout << "�����������!!\n\n";
}

char ConversationManager::regOrComm()
{
    char sim;
    std::cout << "�������� ���� �� ��������� ������� ���������:\n1 - ����������� ������ ������������.\n2 - ���� ������������������� ������������.\n3 - ��������� ������ ���������.\n������� ����� ������������ ��������: ";
    while (true)
    {
        sim = _getch();
        
        if (sim == '1' or sim == '2' or sim == '3')
        {
            std::cout << sim << std::endl << std::endl;
            return sim;
        }
    }
}

bool ConversationManager::userRegistration(Array<User>& allUsers)
{
    std::cout << "\n\n����������� ������ ������������:\n\n";
    bool isSpellingBad = true;
    std::string log{""};
    std::string name{""};
    std::string pass{""};

    while (isSpellingBad)
    {
        std::cout << "��� ������ �� ������ �����������, ������� '!'.\n";
        std::cout << "����� (��������� �����, ����� � ���� ������� �������������): ";
        getline(std::cin, log);
        if (log.length() == 0)
        {
            std::cout << "\n\n������ ������ �� ����� ���� �������! ����� �� ������ ����������� ������ ������������.\n\n";
            return false;
        }
        if (log.length() == 1 && log[0] == '!')         // ����� �� ������� �������
        {
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : log)                             // �������� ������������ ��������� ��������
        {
            if (!((c <= 57 && c >= 48) ||                     // ������ - �����
                  (c <= 90 && c >= 65) ||                     // ������ ��������� ��������� �����
                  (c <= 122 && c >= 97)||                     // ������ ��������� ��������� �����
                  (c == 95)))                                  // ������ ������ �������������
            {
                std::cout << "� ���������, � ������ ������� ������������ �������. \n����������� ������ ����� ������.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //��� ������� ����������, ��������� �� ������������ ������
        {
            bool isLogUnique = true;
            for (int i = 0; i < allUsers.getCount(); ++i)
            {
                if (allUsers[i].getLogin() == log) 
                {
                    isLogUnique = false;
                    break;
                }
            }
            if (isLogUnique)
                isSpellingBad = false;
            else
            {
                std::cout << "����� ����� ��� ���������������.\n������� ����� �����: ";
            }
        }
    }
    //std::cout << "������ �����: " << log << std::endl;

    isSpellingBad = true;
    while (isSpellingBad)
    {
        std::cout << "��� (������� �����, ����� � ���� ������� �������������): ";
        getline(std::cin, name);
        if (name.length() == 0)
        {
            std::cout << "\n\n������ ������ �� ����� ���� ������� ������������. ����� �� ������ ����������� ������������.\n\n";
            return false;
        }
        if (name.length() == 1 && name[0] == '!')         // ����� �� ������� �������
        {
            std::cout << "\n\n����������� ������ ������������ ���� ��������.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : name)                             // �������� ������������ ��������� ��������
        {
            if (!((c <= 57 && c >= 48) ||                     // ������ - �����
                (c <= -38 && c >= -64) ||                     // ������ ������� ����� �-�
                (c <= -6 && c >= -36)  ||                     // ������ ������� ����� �-�
                (c <= -1 && c >= -4)   ||                     // ������ ������� ����� �-�
                c == -88 || c == -72   ||                     // ������� �, �
                (c == 95)))                                   // ������ ������ �������������
            {
                /*      ***�������***
                for (auto& c1 : name)
                {
                    std::cout << c1 << "\t" << (int)c1 << std::endl;
                }
                */
                std::cout << "� ���������, � ����� ������� ������������ �������. \n���������� ������ ��� ���.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //��� ������� ����������, ��������� �� ������������ ������
        {
            bool isLogUnique = true;
            for (int i = 0; i < allUsers.getCount(); ++i)
            {
                if (allUsers[i].getNickname() == name)
                {
                    isLogUnique = false;
                    break;
                }
            }
            if (isLogUnique)
                isSpellingBad = false;
            else
            {
                std::cout << "������������ � ����� ������� ��� ����.\n������� ����� ��� ������������: ";
            }
        }
    }
    //std::cout << "������� ���: " << name << std::endl;                                            //***�������****

    isSpellingBad = true;
    while (isSpellingBad)
    {
        pass = "";
        std::cout << "������ (��������� �����, ����� � \n����������� �����, ����� ������� � ���������������� �����): ";
        char c;
        
        while ((c = _getch()) != '\r')
        {
            pass.push_back(c);
            _putch('*');
        }
        //std::cout << "\n��������� ������: "<< pass << std::endl;                                 //***�������****
        
        if (pass.length() == 1 && pass[0] == '!')         // ����� �� ������� �������
        {
            std::cout << "\n\n����������� ������ ������������ ���� ��������.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : pass)                             // �������� ������������ ��������� ��������
        {
            if (!(c <= 126 && c >= 34) or c=='!' or c == ' ')                  // ��� �������� ������� ������ �������� ASCII ����� ! � �������
            {
                std::cout << "\n������ �����������! ��� ������ ������ �������� ������.\n����������� ������ ������ ������: ";
                isSimbolBad = true;
                //std::cin.ignore(32767, '\n'); // ������� ������ ��������
                break;
            }
             
        }
        if (!isSimbolBad)
            isSpellingBad = false;
    }
    //std::cout << "������ ������: " << pass << std::endl;                                          //***�������****
    //������� � ������ ������ ������������
    User* ptrUser = new User(log, name, pass);
    allUsers.add(std::move(*ptrUser));
    delete ptrUser;
    std::cout << "\n\n����� ������������ '" << name << "' ������� ���������������.\n\n";
    return true;
}

int ConversationManager::usersInput(Array<User>& allUsers)
{
    std::string log{""};
    std::string pass{""};
    bool isLogGood = false;
    bool isPassGood = false;
    this->cleanConsole();
    std::cout << "\n\n������� ����� ��� ������ '!' ��� ��������: ";
    getline(std::cin, log);
    if (log.length() == 1 && log == "!")
    {
        std::cout << "\n\n����������� ������������ ���� ��������.\n\n";
        return -1;
    }
    //���������� ������ ������������� �� ���������� ������
    int userNum{-1};
    for (int i = 0; i < allUsers.getCount(); ++i)
    {
        if (allUsers[i].getLogin() == log)
        {
            userNum = i;
            break;
        }
    }
    
    std::cout << "\n\n������� ������: ";
    
    char c;
    while ((c = _getch()) != '\r')
    {
        pass.push_back(c);
        _putch('*');
    }
    // ���������� ������ � ������� ������������ �� �������
    if (pass != allUsers[userNum].getPassword())        //����� � ������ �� �������
    {
        std::cout << "\n\n������ ��� ����� ������ ��� ������.\n\n";
        userNum = -1;
    }
        
    return userNum;
}

void ConversationManager::userMessChoise(User& user, Array<User>& allUsers, Array<PrivateMessage>& arrPM, Array<CommonMessage>& arrCM)
{
    this->cleanConsole();
    std::cout << "\n\n" << user.getNickname() << ", ������!\n\n";
    std::cout << "��������:\n1 - �������� ��������� � ����� ���.\n2 - �������� ��������� � ��� ������������.\n";
    std::cout << "3 - ����������� ��������� �� ������ ���� (���������� ���������: " << arrCM.getCount() << ").\n";

    //��������� ������� ������� ���������
    std::string name = user.getNickname();
    int countPM{0};
    Array <int> numbersFromPM;
    
    for (int i = 0; i < arrPM.getCount(); ++i)
    {
        if (*arrPM[i].getSendTo() == name)
        {
            numbersFromPM.add(std::move(i));
        }
    }

    std::cout << "4 - ����������� ������� ��������� (���������� ���������: " << numbersFromPM.getCount() << ").\n";
    std::cout << "5 - ��������� ������ � �����������.\n";
    std::cout << "\n��������� ������ : ";
    // ����������� ����� ������������
    char sim;
    bool isSimOK = false;
    while (!isSimOK)
    {
        sim = _getch();

        if (sim == '1' || sim == '2' || sim == '3' || sim == '4' || sim == '5')
        {
            std::cout << sim << std::endl << std::endl;
            isSimOK = true;
        }
    }
    
    if (sim == '1')  //�������� ��������� � ����� ���
    {
        this->cleanConsole();
        std::cout << "\n\n�������� ��������� ��� ����: ";
        std::string mes{ "" };
        getline(std::cin, mes);
        int mesNum = arrCM.getCount();
        CommonMessage* ptrCommonMes = new CommonMessage(mesNum, mes, name);
        std::cout << "\n\n��������� ��������� ��� �������: " << mesNum << " \n\n";
        arrCM.add(std::move(*ptrCommonMes));
        delete ptrCommonMes;
    }
    if (sim == '2')     //�������� ��������� � ��� �����������
    {
        this->cleanConsole();
        std::cout << "\n\n�������� ����� ������������, ��� �� �������� ���������: \n";
        
        struct usersList    //��������� ��������� ��� �������� ������ �������������
        {
            int num;
            std::string name;
            int numInAllUsers;
        };
        Array <usersList> strList;
        int count{0};
        for (int i = 0; i < allUsers.getCount(); ++i) 
        {
            if (user.getNickname() != allUsers[i].getNickname())
            {
                usersList* ptrUL = new usersList;
                ptrUL->name = allUsers[i].getNickname();
                ptrUL->num = count;
                ptrUL->numInAllUsers = i;
                strList.add(std::move(*ptrUL));
                delete ptrUL;
                count += 1;
            }
        }
        for (int i = 0; i < strList.getCount(); ++i)
        {
            std::cout << strList[i].num << ". " << strList[i].name << std::endl;
        }
        bool isNumNotOK = true;
        int choise = getIntValue();
        
        //������ ���
        std::string mes{ "" };
        getline(std::cin, mes);
        int mesNum = arrCM.getCount();
        CommonMessage* ptrCommonMes = new CommonMessage(mesNum, mes, name);
        std::cout << "\n\n��������� ��������� ��� �������: " << mesNum << " \n\n";
        arrCM.add(std::move(*ptrCommonMes));
        delete ptrCommonMes;
        // ����������� �������
    }
       
}

