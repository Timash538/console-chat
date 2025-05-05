#include "UserManager.h"
#include <iostream>

UserManager::UserManager(std::unique_ptr<DataManager<User>>&& manager) : _users(std::move(manager)), _currentUserID(-1) {}

UserManager::UserManager(UserManager&& other) noexcept
{
	_users = std::move(other._users);
	_currentUserID = std::move(other._currentUserID);
}

UserManager::UserManager(const UserManager& other)
{
	_users = other._users->clone();
	_currentUserID = other._currentUserID;
}

UserManager& UserManager::operator=(UserManager&& other) noexcept
{
	_users = std::move(other._users);
	_currentUserID = std::move(other._currentUserID);
	return *this;
}

UserManager& UserManager::operator=(const UserManager& other) 
{
	_users = other._users->clone();
	_currentUserID = other._currentUserID;
	return *this;
}

bool UserManager::addUser(User&& user)
{
	if (!exists(move(user.getNickname()), move(user.getLogin())))
	{
		_users->add(std::move(user));
		std::cout << "Пользователь " << user.getNickname() << " успешно зарегистрирован!" << std::endl;
		return true;
	}
	std::cout << "Пользователь с таким ником или логином уже зарегистрирован!" << std::endl;
	return false;
}

const User& UserManager::getUser(int id) const
{
	return _users->get(id);
}

int UserManager::getCurrentUserID() const
{
	return _currentUserID;
}

const User& UserManager::getCurrentUser() const
{
	return getUser(_currentUserID);
}

bool UserManager::exists(std::string&& nickname, std::string&& login)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname || _users->get(i).getLogin() == login)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByNickname(std::string&& nickname, int& index)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname)
		{
			index = i;
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByNickname(std::string&& nickname)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getNickname() == nickname)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByLogin(std::string&& login, int& index)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getLogin() == login)
		{
			index = i;
			return true;
		}
	}
	return false;
}

bool UserManager::findUserByLogin(std::string&& login)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (_users->get(i).getLogin() == login)
		{
			return true;
		}
	}
	return false;
}

bool UserManager::loginUser(std::string&& login, std::string&& password)
{
	int index = -1;

	if (findUserByLogin(move(login), index))
		if (_users->get(index).checkPassword(std::move(password)))
		{
			std::cout << "Успешный вход в чат! Добро пожаловать, " << _users->get(index).getNickname() << "!" << std::endl;
			_currentUserID = index;
			return true;
		}

	std::cout << "Неверный логин или пароль!" << std::endl;
	return false;

}

void UserManager::logout()
{
	_currentUserID = -1;
}

void UserManager::showUsers()
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		std::cout << "ID: " << i << " " << " Никнейм: " << _users->get(i).getNickname() << std::endl;
	}
}

void UserManager::showUsersExcludingCurrent()
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		if (i != _currentUserID)
		std::cout << "ID: " << i << " " << " Никнейм: " << _users->get(i).getNickname() << std::endl;
	}
}

void UserManager::showUsersExcluding(Array<int>&& ids)
{
	for (int i = 0; i < _users->getCount(); i++)
	{
		bool f = false;
		for (int j = 0; j < ids.getCount(); j++)
			if (i == ids[j])
			{
				f = true;
				break;
			}
		if (!f) std::cout << "ID: " << i << " " << " Никнейм: " << _users->get(i).getNickname() << std::endl;
	}
}

int UserManager::getCount() const
{
	return _users->getCount();
}
