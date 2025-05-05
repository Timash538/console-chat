#pragma once
#include "User.h"
#include "DataManager.h"
#include "Array.h"
#include <memory>
#include <string>


class UserManager //����� ��� ���������� ��������������
{
public:
	UserManager(std::unique_ptr<DataManager<User>>&& manager); 
	UserManager(UserManager&& other) noexcept; 
	UserManager(const UserManager& other); 
	UserManager& operator=(UserManager&& other) noexcept; 
	UserManager& operator=(const UserManager& other); 
	UserManager() = default;
	~UserManager() = default;
	bool addUser(User&& user); // ��������� ������������, ���������� true ���� �������
	const User& getUser(int id) const; // �������� ������������ �� ID
	int getCurrentUserID() const; // ���������� ID �������� ������������ (������� �����������)
	const User& getCurrentUser() const; // ���������� �������� ������������ (������� �����������)
	bool exists(std::string&&, std::string&&); // ���������� true ���� ����� ��� ������� ��������� � ���� �� ����� �������������
	bool findUserByNickname(std::string&& nickname, int& index); // ����� ������������ �� ���� � ������� ��� ID (index)
	bool findUserByNickname(std::string&& nickname); // �� �� ����� �� ��������� ���������� �� ������������ � ����� �����
	bool findUserByLogin(std::string&& login, int& index); // ����� ������������ �� ������ � ������� ��� ID (index)
	bool findUserByLogin(std::string&& login); // �� �� ����� �� ��������� ���������� �� ������������ � ����� �������
	bool loginUser(std::string&& login, std::string&& password); // ���� ����� � ������ �������� - ��������� �� ������ ������������ ��������� � currentUser
	void logout(); // ���� ����� � ������ �������� - ��������� �� ������ ������������ ��������� � currentUser
	void showUsers(); // ���������� ���� �������������
	void showUsersExcludingCurrent(); // ���������� ���� ������������� �������� �������������
	void showUsersExcluding(Array<int>&& ids); // ���������� ���� ������������� �������� �������������
	int getCount() const; // ���������� ���-�� �������������
private:
	std::unique_ptr<DataManager<User>> _users;
	int _currentUserID;
};