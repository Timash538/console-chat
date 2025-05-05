#pragma once
#include <string>
#include <memory>
#include "User.h"

class Message
{
private:
	std::shared_ptr<User> _sender;
	std::string _msg;
public:
	// ������������:
	Message() = default;
	Message(User, std::string);
	Message(const Message& other);
	Message(Message&& other) noexcept;
	

	// ����������
	~Message() = default;

	// �������:
	void setMessage(std::string&);
	void setSender(User user);

	//�������:
	std::string getMessage();
	const User &getSendFrom();

};

