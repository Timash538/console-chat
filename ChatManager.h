#pragma once
#include "Array.h"
#include "Message.h"
#include "UserManager.h"

enum ChatType {FORALL, GROUP, PRIVATE};


class ChatManager
{
	struct Chat;
	struct UserToChatLink;

public:
	ChatManager() = default;
	ChatManager(ChatManager&& other) noexcept;
	ChatManager(const ChatManager& other);
	ChatManager& operator=(ChatManager&& other) noexcept;
	ChatManager& operator=(const ChatManager& other);
	void addNewChat(ChatType&& type, unsigned int userID);
	void addNewChat(ChatType&& type);
	void addUserToChat(int userID, int chatID);
	void addUserToLastChat(int userID);
	bool findUserToChatLink(int userID, int& index);
	void updateUserPtrToLastMsg(int userID, int chatID);
	void showAllUserChats(int userID, const UserManager& uM);
	int countUnreadMsgs(int userID, int chatID);
	const Array<Chat>& getChats();
	Chat& getChat(unsigned int chatID);
	const Array<UserToChatLink>& getLinks();
	void showMessages(unsigned int chatID);
	void showAllLinks(const UserManager& uM);
	Array<int> getUsersIDFromChat(int chatID);

private:

	struct Chat
	{
		ChatType _type;
		Array<Message> _messages;
		Array<int> _users;

		Chat(ChatType type);
		Chat(const Chat& chat);
		Chat(Chat&& chat) noexcept;
		Chat() = default;
	};

	struct UserToChatLink
	{
		int _userID;
		Array<int> _chats;
		Array<int> _userPtrToLastMsg;

		UserToChatLink(int userID, int chatID);
		UserToChatLink() = default;
	};

	Array<Chat> _chats;
	Array<UserToChatLink> _links;
};