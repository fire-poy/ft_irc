#include "../srcs/Includes.hpp"
#include <cstring>

# define NICKNAME_VALID_CHAR "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_[]{}\\`|"

bool	validNickName(std::string nickname)
{
	if (nickname.length() > 9)
		return false;
	for (size_t i = 0; i < nickname.length(); i++)
	{
		if (!std::strchr(NICKNAME_VALID_CHAR, nickname[i]))
			return false;
	}
	return true;
}

void	Client::nick(Message *m)
{
	std::cout << FC(GREEN, ">\tnick function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	std::string nick = "NICK";
	if (m->params.empty())
		sendReply(431, _nickname, "", "", "");
	else if (!validNickName(m->params[0]))
		sendReply(432, _nickname, "", "", "");
	else if (_server->isNickUsed(m->params[0]))
		sendReply(433, m->params[0], "", "", "");
	else // "the nick is OK"
	{
		std::string msg;
		if ( _register.nickHasBeenExecuted )
		{
			msg = formatMsgsUsers();
			setNickname(m->params[0]);
		}
		else
		{
			setNickname(m->params[0]);
			msg = formatMsgsUsers();
		}
		msg.append("NICK " + _nickname + END_CHARACTERS);
		sendMsgSharedUsers(msg);
		sendMsg(msg);
		addToNicksHistory();
		addCommandToRegister(nick);
	}
}

void	Client::addToNicksHistory( void ){
	nicksBackup newNick;

	newNick.nick = this->_nickname;
	newNick.server = this->_server->getName();
	newNick.serverInfo = this->_server->getServInfo();
	newNick.user = this->_username;
	newNick.host = this->_hostname;
	newNick.realname = this->_realname;
	newNick.serverStartTime = this->_server->getStartTime();
	_nicksHistory.push_back(newNick);
}

// 3.1.2 Nick message
//       Command: NICK  Parameters: <nickname>

//    NICK command is used to give user a nickname or change the existing one.

//    Numeric Replies:
//            ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
//            ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
//            ERR_UNAVAILRESOURCE             ERR_RESTRICTED

//    Examples:
//    NICK Wiz                ; Introducing new nick "Wiz" if session is
//                            still unregistered, or user changing his
//                            nickname to "Wiz"

//    :WiZ!jto@tolsun.oulu.fi NICK Kilroy
//                            ; Server telling that WiZ changed his
//                            nickname to Kilroy.

//HACER (en principio no usado)??
// #define ERR_NICKCOLLISION(nick,user, host) nick + " :Nickname collision KILL from "+ user + "@" + host//436
//          - Returned by a server to a client when it detects a
//            nickname collision (registered of a NICK that
//            already exists by another server).

// #define ERR_UNAVAILRESOURCE(resource) resource + "<nick/channel> :Nick/channel is temporarily unavailable" //437
//          - Returned by a server to a user trying to join a channel
//            currently blocked by the channel delay mechanism.

//          - Returned by a server to a user trying to change nickname
//            when the desired nickname is blocked by the nick delay
//            mechanism.

// #define ERR_RESTRICTED ":Your connection is restricted!" //484
// //          - Sent by the server to a user upon connection to indicate
// //            the restricted nature of the connection (user mode "+r").
