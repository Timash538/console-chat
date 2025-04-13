#include "ConversationManager.h"
#include "DataManager.h"

ConversationManager::ConversationManager()
{
}

ConversationManager::ConversationManager(Array<Message>& privateMessagePool, Array<Message>& commonMessagePool)
{
    allUsers = UserManager(std::move(std::make_unique<Array<User>>(10)));
}

void ConversationManager::cleanConsole()         // ������� �������
{
    system("cls");
}

void ConversationManager::start()
{
    bool isRun = true;
    this->greeting();
    bool isItNextLoop = false;
    int uNum{ -1 };
    //��������� ����
    while (isRun)
    {
        char choice = this->regOrComm();
        switch (choice)
        {
        case '1':
            if (isItNextLoop)
            {
                this->cleanConsole();
            }
            isItNextLoop = true;
            this->userRegistration();
            break;
        case '2':
            if (isItNextLoop)
            {
                this->cleanConsole();
                isItNextLoop = true;
            }
            else
            {
                std::cout << "\n\n��� ������������������ �������������, ������� � �.1.\n\n";
                break;
            }
            uNum = this->usersInput();		//����� ��������������������� ������������ �� ������� Users
            if (uNum > -1)
            {
                User user = allUsers.getUser(uNum);			//�������� ������ ����� ������������
                this->userMessChoise(user, privateMessagePool, commonMessagePool);
            }
            break;
        case '3':
            std::cout << "\n\n������ ��������� ���������.\n";
            isRun = false;
            break;
        }
    }
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

bool ConversationManager::userRegistration()
{
    this->cleanConsole();
    std::cout << "\n\n����������� ������ ������������:\n\n";
    bool isSpellingBad = true;
    std::string log{""};
    std::string name{""};
    std::string pass{""};

    while (isSpellingBad)
    {
        std::cout << "��� ������ �� ������ �����������, ������� '!' � 'ENTER'.\n";
        std::cout << "����� (��������� �����, ����� � ���� ������� �������������): ";
        getline(std::cin, log);
        if (log.length() == 0)
        {
            std::cout << "\n\n������ ������ �� ����� ���� �������! ����� �� ������ ����������� ������ ������������.\n\n";
            return false;
        }
        if (log.length() == 1 && log[0] == '!')         // ����� �� ������� �������
        {
            this->cleanConsole();
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
                if (allUsers.findUserByLogin(std::move(log))) 
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
                if (allUsers.findUserByNickname(std::move(name)))
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
    allUsers.addUser(std::move(User(log, name, pass)));
    std::cout << "\n\n����� ������������ '" << name << "' ������� ���������������.\n\n";
    return true;
}

int ConversationManager::usersInput()
{
    std::string log{""};
    std::string pass{""};
    bool isLogGood = false;
    bool isPassGood = false;
    this->cleanConsole();
    std::cout << "\n\n���� ������������.\n\n";
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
        if (allUsers.getUser(i).getLogin() == log)
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
    if (pass != allUsers.getUser(userNum).getPassword())        //����� � ������ �� �������
    {
        std::cout << "\n\n������ ��� ����� ������ ��� ������.\n\n";
        userNum = -1;
    }
        
    return userNum;
}

void ConversationManager::userMessChoise(User& user, Array<Message>& arrPM, Array<Message>& arrCM)
{
    bool isRun = true;
    //��� ������������
    std::string name = user.getNickname();
    while (isRun)
    {

        int countPM{ amountPrivateMessage(arrPM, name) };

        this->cleanConsole();
        std::cout << "\n\n" << user.getNickname() << ", ��������� ��������:\n";
        std::cout << "��������:\n1 - �������� ��������� � ����� ���.\n2 - �������� ��������� � ��� ������������.\n";
        std::cout << "3 - ����������� ��������� �� ������ ���� (���������� ���������: " << arrCM.getCount() << ").\n";
        std::cout << "4 - ����������� ������� ��������� (���������� ���������: " << countPM << ").\n";
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
            inputCommonMessage(arrCM, name);
        }
        if (sim == '2')     //�������� ��������� � ��� �����������
        {
            inputPrivateMessage(user, arrPM);
        }
        if (sim == '3')         //�������� ��������� �� ������ ���� 
        {
            outputCommonMessage(arrCM);
        }

        if (sim == '4')     //�������� ������ ���������
        {
            outputPrivateMesage(arrPM, user);
        }

        if (sim == '5')         //��������� ������ � �����������
            isRun = false;
    }
}

void ConversationManager::outputPrivateMesage(Array<Message>& arrPM, User& user)
{
    {
        this->cleanConsole();
        std::cout << "\n���. ��� ������ ���������:\n\n";
        for (int i = 0; i < arrPM.getCount(); ++i)
        {
            if (*arrPM[i].getSendTo() == user.getNickname())
                std::cout << *arrPM[i].getSendFrom() << " �������: " << *arrPM[i].getMessage() << std::endl;
        }
        std::cout << "\n\n������� �� ����� �������, ��� �� ����� �� ������ ��������� ���� ������ ���������: ";
        char sim;
        sim = _getch();
    }
}

void ConversationManager::outputCommonMessage(Array<Message>& arrCM)
{
    this->cleanConsole();
    std::cout << "\n����� ���. ��� ���������:\n\n";
    for (int i = 0; i < arrCM.getCount(); ++i)
    {
        std::cout << "'" << *arrCM[i].getSendFrom() << "'" << " �������: " << *arrCM[i].getMessage() << std::endl;
    }
    std::cout << "\n\n������� �� ����� �������, ��� �� ����� �� ������ ��������� ������ ����: ";
    char sim;
    sim = _getch();
}

void ConversationManager::inputPrivateMessage(User& user, Array<Message>& arrPM)
{
    this->cleanConsole();
    std::cout << "\n\n�������� ����� ������������, ��� �� �������� ���������: \n";
    int count = 0;
    for (int i = 0; i < allUsers.getCount(); ++i)
    {
        if (!(allUsers.getUser(i) == user))
        {
            std::cout << count << ". " << allUsers.getUser(i).getNickname() << std::endl;
            count++;
        }
    }
    int choise{ 0 };
    while (true)
    {
        choise = getIntValue();
        if (choise >= 0 && choise < count)   //������� ���������� �����
            break;
    }

    int index;
    allUsers.findUser(std::move(user), index);
    if (choise >= index) choise++;
    std::cout << "\n�������� ����� ��������� ��� " << allUsers.getUser(choise).getNickname() << ": ";
    std::string privateMes{ "" };
    getline(std::cin, privateMes);
    int mesNum = arrPM.getCount();

    Message* ptrPrivateMes = new Message(mesNum, privateMes, user.getNickname(), allUsers.getUser(choise).getNickname());
    std::cout << "\n\n��������� ��������� ��� �������: " << mesNum << " \n\n";
    arrPM.add(std::move(*ptrPrivateMes));
    delete ptrPrivateMes;
}

void ConversationManager::inputCommonMessage(Array<Message>& arrCM, std::string& name)
{
    this->cleanConsole();
    std::cout << "\n\n�������� ��������� ��� ����: ";
    std::string mes{ "" };
    getline(std::cin, mes);
    int mesNum = arrCM.getCount();
    Message* ptrCommonMes = new Message(mesNum, mes, name);
    std::cout << "\n\n��������� ��������� ��� �������: " << mesNum << " \n\n";
    arrCM.add(std::move(*ptrCommonMes));
    delete ptrCommonMes;
}

int ConversationManager::amountPrivateMessage(Array<Message>& arrPM, std::string& name)
{
    int countPM{ 0 };
    for (int i = 0; i < arrPM.getCount(); ++i)
    {
        if (*arrPM[i].getSendTo() == name)
        {
            countPM += 1;
        }
    }
    return countPM;
}

