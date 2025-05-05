#include "User.h"

User::User(User&& other) noexcept
	: _nickname(std::move(other._nickname)),
	_login(std::move(other._login)),
	_password(std::move(other._password)) {
}

User& User::operator=(User&& other) noexcept {
	_nickname = std::move(other._nickname);
	_login = std::move(other._login);
	_password = std::move(other._password);
	return *this;
}

std::string User::getNickname()	const
{
	return _nickname;
}

std::string User::getLogin() const
{
	return _login;
}

std::string User::getPassword() const
{
	return _password;
}

void User::setNickname(std::string&& nickname)
{
	_nickname = nickname;
}

void User::setLogin(std::string&& login)
{
	_login = login;
}

void User::setPassword(std::string&& password)
{
	_password = password;
}

bool User::checkPassword(std::string&& password) const
{
	return (_password == password) ? true : false;
}

bool User::operator==(const User& b)
{
	if (_login == b._login && _nickname == b._nickname && _password == b._password) return true;
	return false;
}