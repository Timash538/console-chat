#include "ChatManager.h"



ChatManager::ChatManager(ChatManager&& other) noexcept
{
	_chats = std::move(other._chats);
	_links = std::move(other._links);
}

ChatManager::ChatManager(const ChatManager& other)
{
	_chats = other._chats;
	_links = other._links;
}

ChatManager& ChatManager::operator=(ChatManager&& other) noexcept
{
	_chats = std::move(other._chats);
	_links = std::move(other._links);
	return *this;
}

ChatManager& ChatManager::operator=(const ChatManager& other)
{
	_chats = other._chats;
	_links = other._links;
	return *this;
}

void ChatManager::addNewChat(ChatType &&type, unsigned int userID)
{
	_chats.add(Chat(type));
	addUserToLastChat(userID);
}

void ChatManager::addNewChat(ChatType&& type)
{
	_chats.add(Chat(type));
}

void ChatManager::addUserToChat(int userID, int chatID)
{
	_chats.get(chatID)._users.add(std::move(userID));
	int idx = -1;
	if (findUserToChatLink(userID, idx))
	{
		_links.get(idx)._chats.add(std::move(chatID));
		_links.get(idx)._userPtrToLastMsg.add(0);
		return;
	}
	_links.add(UserToChatLink(userID, chatID));
	_links.get(_links.getCount() - 1)._userPtrToLastMsg.add(0);
}

void ChatManager::addUserToLastChat(int userID)
{
	unsigned int lastChatID = _chats.getCount() - 1;
	_chats.get(lastChatID)._users.add(std::move(userID));
	int idx = -1;
	if (findUserToChatLink(userID, idx))
	{
		_links.get(idx)._chats.add(lastChatID);
		_links.get(idx)._userPtrToLastMsg.add(0);
		return;
	}
	_links.add(UserToChatLink(userID, _chats.getCount()-1));
	_links.get(_links.getCount()-1)._userPtrToLastMsg.add(0);
}

bool ChatManager::findUserToChatLink(int userID, int& idx)
{
	for (int i = 0; i < _links.getCount(); i++)
	{
		if (_links.get(i)._userID == userID)
		{
			idx = i;
			return true;
		}
	}
	return false;
}

void ChatManager::updateUserPtrToLastMsg(int userID, int chatID)
{
	int idx = -1;
	findUserToChatLink(userID, idx);
	_links.get(idx)._userPtrToLastMsg.get(chatID) = _chats.get(_links.get(idx)._chats.get(chatID))._messages.getCount();
}

void ChatManager::showAllUserChats(int userID, const UserManager& uM)
{
	int idx = -1;
	findUserToChatLink(userID, idx);

	if (_links.get(idx)._chats.isEmpty())
	{
		std::cout << "Нет чатов, попробуйте создать новый." << std::endl;
		return;
	}
	std::cout << "Все доступные вам чаты: " << std::endl;
	
	for (int i = 0; i < _links.get(idx)._chats.getCount(); i++)
	{
		unsigned int id = _links.get(idx)._chats[i];
		Array<int>* users = &_chats.get(id)._users;
		if (_chats.get(id)._type == FORALL)
		{
			std::cout << "\tID: " << i << " Общий чат. " << std::endl;
			continue;
		}
		else if (_chats.get(id)._type == GROUP)
		{
			std::cout << "\tID: " << i << " участники чата: ";
			for (int j = 0; j < users->getCount(); j++)
			{
				std::cout << uM.getUser(users->get(j)).getNickname() << ((j == users->getCount() - 1) ? ". " : ", ");
			}
		}
		else
		{
			std::cout << "\tID: " << i << " личный чат с " << ((users->get(0) == userID) ? uM.getUser(users->get(1)).getNickname() : uM.getUser(users->get(0)).getNickname()) << ". ";
		}
		if (countUnreadMsgs(userID, i) > 0)
		{
			int chatID = _links.get(idx)._chats[i];
			std::cout << "(Непрочитанных сообщений: " << countUnreadMsgs(userID, i) << ")";
			std::cout << "\n";
		}
		else std::cout << "\n";
	}
}

int ChatManager::countUnreadMsgs(int userID, int id)
{
	int idx = -1;
	findUserToChatLink(userID, idx);
	return (_chats.get(_links.get(idx)._chats.get(id))._messages.getCount()) - _links.get(idx)._userPtrToLastMsg.get(id);
}

const Array<ChatManager::Chat>& ChatManager::getChats()
{
	return _chats;
}

ChatManager::Chat& ChatManager::getChat(unsigned int chatID)
{
	return _chats.get(chatID);
}

const Array<ChatManager::UserToChatLink>& ChatManager::getLinks()
{
	return _links;
}

void ChatManager::showMessages(unsigned int chatID)
{
	Array<Message>* messages = &_chats.get(chatID)._messages;
	for (unsigned int i = 0; i < messages->getCount(); i++)
	{
		std::cout << messages->get(i).getSendFrom().getNickname() << ": " << messages->get(i).getMessage() << "\n";
	}
}

void ChatManager::showAllLinks(const UserManager& uM)
{
	std::cout << "\n All links:\n";
	for (int i = 0; i < _links.getCount(); i++)
	{
		std::cout << "ID: " << i << "\n";
		std::cout << "User: " << uM.getUser(_links[i]._userID).getNickname() << "\n";
		std::cout << "Chats: \n";
		for (int j = 0; j < _links[i]._chats.getCount(); j++)
		{
			std::cout << "\tID of chat: " << _links[i]._chats[j] << " Users: "; 
			for (int k = 0; k < _chats[_links[i]._chats[j]]._users.getCount(); k++)
				std::cout << uM.getUser(_chats[_links[i]._chats[j]]._users[k]).getNickname() << " ";
			std::cout << "\n";
			std::cout << "\tMessages count: " << _chats[_links[i]._chats[j]]._messages.getCount() << "\n";
			std::cout << "\tLast read message: " << _links[i]._userPtrToLastMsg[j] << "\n";
		}
	}
}

Array<int> ChatManager::getUsersIDFromChat(int chatID)
{
	return Array<int>(_chats.get(chatID)._users);
}

ChatManager::UserToChatLink::UserToChatLink(int userID, int chatID)
{
	_userID = userID;
	_chats.add(std::move(chatID));
	_userPtrToLastMsg.add(0);
}

ChatManager::Chat::Chat(ChatType type)
{
	_type = type;
}

ChatManager::Chat::Chat(const Chat& other)
{
	_type = other._type;
	_messages = other._messages;
	_users = other._users;
}

ChatManager::Chat::Chat(Chat&& other) noexcept
{
	_type = std::move(other._type);
	_messages = std::move(other._messages);
	_users = std::move(other._users);
}
