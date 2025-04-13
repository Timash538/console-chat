#include "ConversationManager.h"

ConversationManager::ConversationManager()
{
}

ConversationManager::ConversationManager(Array<User>& allUsers, Array<Message>& privateMessagePool, Array<Message>& commonMessagePool)
{
}

void ConversationManager::cleanConsole()         // Очищаем консоль
{
    system("cls");
}

void ConversationManager::start()
{
    bool isRun = true;
    this->greeting();
    bool isItNextLoop = false;
    int uNum{ -1 };
    //Начальное меню
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
            this->userRegistration(allUsers);
            break;
        case '2':
            if (isItNextLoop)
            {
                this->cleanConsole();
                isItNextLoop = true;
            }
            else
            {
                std::cout << "\n\nНет зарегистрированных пользователей, начните с п.1.\n\n";
                break;
            }
            uNum = this->usersInput(allUsers);		//номер зарегистрировавшегося пользователя из массива Users
            if (uNum > -1)
            {
                User user = allUsers[uNum];			//получаем запись этого пользователя
                this->userMessChoise(user, allUsers, privateMessagePool, commonMessagePool);
            }
            break;
        case '3':
            std::cout << "\n\nРабота программы завершена.\n";
            isRun = false;
            break;
        }
    }
}

void ConversationManager::greeting()
{
    this->cleanConsole();
	std::cout << "Приветствую!!\n\n";
}

char ConversationManager::regOrComm()
{
    char sim;
    std::cout << "Выберите один из возможных режимов программы:\n1 - Регистрация нового пользователя.\n2 - Вход зарегистрированного пользователя.\n3 - Завершить работу программы.\nВведите номер планируемого действия: ";
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
    this->cleanConsole();
    std::cout << "\n\nРегистрация нового пользователя:\n\n";
    bool isSpellingBad = true;
    std::string log{""};
    std::string name{""};
    std::string pass{""};

    while (isSpellingBad)
    {
        std::cout << "Для выхода из режима регистрации, введите '!' и 'ENTER'.\n";
        std::cout << "Логин (латинские буквы, цифры и знак нижнего подчёркивания): ";
        getline(std::cin, log);
        if (log.length() == 0)
        {
            std::cout << "\n\nПустая строка не может быть логином! Вышли из режима Регистрации нового пользователя.\n\n";
            return false;
        }
        if (log.length() == 1 && log[0] == '!')         // выход на верхний уровень
        {
            this->cleanConsole();
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : log)                             // контроль правильности введенных символов
        {
            if (!((c <= 57 && c >= 48) ||                     // символ - цифра
                  (c <= 90 && c >= 65) ||                     // символ заглавная латинская буква
                  (c <= 122 && c >= 97)||                     // символ прописная латинская буква
                  (c == 95)))                                  // символ нижнее подчеркивание
            {
                std::cout << "К сожалению, в логине нашлись недопустимые символы. \nПопытайтесь ввести логин заново.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //Все символы правильные, проверяем на уникальность логина
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
                std::cout << "Такой логин уже зарегистрирован.\nВведите новый логин: ";
            }
        }
    }
    //std::cout << "Введен логин: " << log << std::endl;

    isSpellingBad = true;
    while (isSpellingBad)
    {
        std::cout << "Имя (русские буквы, цифры и знак нижнего подчёркивания): ";
        getline(std::cin, name);
        if (name.length() == 0)
        {
            std::cout << "\n\nПустая строка не может быть имененм пользователя. Вышли из режима регистрации пользователя.\n\n";
            return false;
        }
        if (name.length() == 1 && name[0] == '!')         // выход на верхний уровень
        {
            std::cout << "\n\nРегистрация нового пользователя была прервана.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : name)                             // контроль правильности введенных символов
        {
            if (!((c <= 57 && c >= 48) ||                     // символ - цифра
                (c <= -38 && c >= -64) ||                     // символ русская буква А-Ъ
                (c <= -6 && c >= -36)  ||                     // символ русская буква Ь-ъ
                (c <= -1 && c >= -4)   ||                     // символ русская буква ь-я
                c == -88 || c == -72   ||                     // символы Ё, ё
                (c == 95)))                                   // символ нижнее подчеркивание
            {
                /*      ***Отладка***
                for (auto& c1 : name)
                {
                    std::cout << c1 << "\t" << (int)c1 << std::endl;
                }
                */
                std::cout << "К сожалению, в имени нашлись недопустимые символы. \nПопробуйте ввести еще раз.\n\n";
                isSimbolBad = true;
                break;
            }
        }
        if (!isSimbolBad)                               //Все символы правильные, проверяем на уникальность логина
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
                std::cout << "Пользователь с таким имененм уже есть.\nВведите новое имя пользователя: ";
            }
        }
    }
    //std::cout << "Введено имя: " << name << std::endl;                                            //***Отладка****

    isSpellingBad = true;
    while (isSpellingBad)
    {
        pass = "";
        std::cout << "Пароль (латинские буквы, цифры и \nспециальные знаки, кроме пробела и восклицательного знака): ";
        char c;
        
        while ((c = _getch()) != '\r')
        {
            pass.push_back(c);
            _putch('*');
        }
        //std::cout << "\nСчитанный пароль: "<< pass << std::endl;                                 //***Отладка****
        
        if (pass.length() == 1 && pass[0] == '!')         // выход на верхний уровень
        {
            std::cout << "\n\nРегистрация нового пользователя была прервана.\n\n";
            return false;
        }
        bool isSimbolBad = false;
        for (auto& c : pass)                             // контроль правильности введенных символов
        {
            if (!(c <= 126 && c >= 34) or c=='!' or c == ' ')                  // Все печатные символы первой страницы ASCII кроме ! и пробела
            {
                std::cout << "\nБудьте внимательны! При наборе пароля допущена ошибка.\nПопытайтесь ввести пароль заново: ";
                isSimbolBad = true;
                //std::cin.ignore(32767, '\n'); // удаляем лишние значения
                break;
            }
             
        }
        if (!isSimbolBad)
            isSpellingBad = false;
    }
    //std::cout << "Введен пароль: " << pass << std::endl;                                          //***Отладка****
    //Заносим в массив нового пользователя
    User* ptrUser = new User(log, name, pass);
    allUsers.add(std::move(*ptrUser));
    delete ptrUser;
    std::cout << "\n\nНовый пользователь '" << name << "' успешно зарегистрирован.\n\n";
    return true;
}

int ConversationManager::usersInput(Array<User>& allUsers)
{
    std::string log{""};
    std::string pass{""};
    bool isLogGood = false;
    bool isPassGood = false;
    this->cleanConsole();
    std::cout << "\n\nВход пользователя.\n\n";
    std::cout << "\n\nВведите логин или символ '!' для возврата: ";
    getline(std::cin, log);
    if (log.length() == 1 && log == "!")
    {
        std::cout << "\n\nВерификация пользователя была прервана.\n\n";
        return -1;
    }
    //перебираем массив пользователей на совпадение логина
    int userNum{-1};
    for (int i = 0; i < allUsers.getCount(); ++i)
    {
        if (allUsers[i].getLogin() == log)
        {
            userNum = i;
            break;
        }
    }
    
    std::cout << "\n\nВведите пароль: ";
    
    char c;
    while ((c = _getch()) != '\r')
    {
        pass.push_back(c);
        _putch('*');
    }
    // сравниваем пароль с данными пользователя из массива
    if (pass != allUsers[userNum].getPassword())        //логин и пароль не совпали
    {
        std::cout << "\n\nОшибка при вводе логина или пароля.\n\n";
        userNum = -1;
    }
        
    return userNum;
}

void ConversationManager::userMessChoise(User& user, Array<User>& allUsers, Array<Message>& arrPM, Array<Message>& arrCM)
{
    bool isRun = true;
    //Имя пользователя
    std::string name = user.getNickname();
    while (isRun)
    {

        int countPM{ amountPrivateMessage(arrPM, name) };

        this->cleanConsole();
        std::cout << "\n\n" << user.getNickname() << ", возможные действия:\n";
        std::cout << "Выберите:\n1 - написать сообщение в общий чат.\n2 - написать сообщение в чат пользователя.\n";
        std::cout << "3 - просмотреть сообщения из общего чата (количество сообщений: " << arrCM.getCount() << ").\n";
        std::cout << "4 - просмотреть частные сообщения (количество сообщений: " << countPM << ").\n";
        std::cout << "5 - завершить работу с сообщениями.\n";
        std::cout << "\nРезультат выбора : ";

        // отслеживаем выбор пользователя
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

        if (sim == '1')  //написать сообщение в общий чат
        {
            inputCommonMessage(arrCM, name);
        }
        if (sim == '2')     //написать сообщение в чат пользоватля
        {
            inputPrivateMessage(allUsers, user, arrPM);
        }
        if (sim == '3')         //просмотр сообщений из общего чата 
        {
            outputCommonMessage(arrCM);
        }

        if (sim == '4')     //просмотр частнх сообщений
        {
            outputPrivateMesage(arrPM, user);
        }

        if (sim == '5')         //завершить работу с сообщениями
            isRun = false;
    }
}

void ConversationManager::outputPrivateMesage(Array<Message>& arrPM, User& user)
{
    {
        this->cleanConsole();
        std::cout << "\nЧат. Все личные сообщения:\n\n";
        for (int i = 0; i < arrPM.getCount(); ++i)
        {
            if (*arrPM[i].getSendTo() == user.getNickname())
                std::cout << *arrPM[i].getSendFrom() << " написал: " << *arrPM[i].getMessage() << std::endl;
        }
        std::cout << "\n\nНажмите на любую клавишу, что бы выйти из режима прочтения чата личных сообщений: ";
        char sim;
        sim = _getch();
    }
}

void ConversationManager::outputCommonMessage(Array<Message>& arrCM)
{
    this->cleanConsole();
    std::cout << "\nОбщий чат. Все сообщения:\n\n";
    for (int i = 0; i < arrCM.getCount(); ++i)
    {
        std::cout << "'" << *arrCM[i].getSendFrom() << "'" << " написал: " << *arrCM[i].getMessage() << std::endl;
    }
    std::cout << "\n\nНажмите на любую клавишу, что бы выйти из режима прочтения общего чата: ";
    char sim;
    sim = _getch();
}

void ConversationManager::inputPrivateMessage(Array<User>& allUsers, User& user, Array<Message>& arrPM)
{
    this->cleanConsole();
    std::cout << "\n\nВыберите номер пользователя, что бы написать сообщение: \n";

    struct usersList    //временная структура для создания списка пользователей
    {
        int num{ 0 };
        std::string name{ "" };
        int numInAllUsers{ 0 };
    };
    Array <usersList> strList;
    int count{ 0 };
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
    int choise{ 0 };
    while (isNumNotOK)
    {
        choise = getIntValue();
        if (choise >= 0 && choise < strList.getCount())   //выбрано правильное число
            isNumNotOK = false;
    }

    std::cout << "\nНаберите текст сообщение для " << strList[choise].name << ": ";
    std::string privateMes{ "" };
    getline(std::cin, privateMes);
    int mesNum = arrPM.getCount();

    std::string name1 = user.getNickname();
    Message* ptrPrivateMes = new Message(mesNum, privateMes, name1, strList[choise].name);
    std::cout << "\n\nСообщение сохранено под номером: " << mesNum << " \n\n";
    arrPM.add(std::move(*ptrPrivateMes));
    delete ptrPrivateMes;
}

void ConversationManager::inputCommonMessage(Array<Message>& arrCM, std::string& name)
{
    this->cleanConsole();
    std::cout << "\n\nНаберите сообщение для всех: ";
    std::string mes{ "" };
    getline(std::cin, mes);
    int mesNum = arrCM.getCount();
    Message* ptrCommonMes = new Message(mesNum, mes, name);
    std::cout << "\n\nСообщение сохранено под номером: " << mesNum << " \n\n";
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

