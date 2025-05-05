#pragma once
#include "User.h"
#include "DataManager.h"
#include "Array.h"
#include <memory>
#include <string>


class UserManager //класс дл€ управлени€ пользовател€ми
{
public:
	UserManager(std::unique_ptr<DataManager<User>>&& manager); 
	UserManager(UserManager&& other) noexcept; 
	UserManager(const UserManager& other); 
	UserManager& operator=(UserManager&& other) noexcept; 
	UserManager& operator=(const UserManager& other); 
	UserManager() = default;
	~UserManager() = default;
	bool addUser(User&& user); // ƒобавл€ет пользовател€, возвращает true если удалось
	const User& getUser(int id) const; // ѕолучить пользовател€ по ID
	int getCurrentUserID() const; // ¬озвращает ID текущего пользовател€ (который залогинилс€)
	const User& getCurrentUser() const; // ¬озвращает текущего пользовател€ (который залогинилс€)
	bool exists(std::string&&, std::string&&); // ¬озвращает true если логин или никнейм совпадают с хот€ бы одним пользователем
	bool findUserByNickname(std::string&& nickname, int& index); // Ќайти пользовател€ по нику и достать его ID (index)
	bool findUserByNickname(std::string&& nickname); // “о же самое но провер€ет существует ли пользователь с таким ником
	bool findUserByLogin(std::string&& login, int& index); // Ќайти пользовател€ по логину и достать его ID (index)
	bool findUserByLogin(std::string&& login); // “о же самое но провер€ет существует ли пользователь с таким логином
	bool loginUser(std::string&& login, std::string&& password); // ≈сли логин и пароль сход€тс€ - найденный по логину пользователь заноситс€ в currentUser
	void logout(); // ≈сли логин и пароль сход€тс€ - найденный по логину пользователь заноситс€ в currentUser
	void showUsers(); // ѕоказывает всех пользователей
	void showUsersExcludingCurrent(); // ѕоказывает всех пользователей исключа€ залогиненного
	void showUsersExcluding(Array<int>&& ids); // ѕоказывает всех пользователей исключа€ залогиненного
	int getCount() const; // ¬озвращает кол-во пользователей
private:
	std::unique_ptr<DataManager<User>> _users;
	int _currentUserID;
};