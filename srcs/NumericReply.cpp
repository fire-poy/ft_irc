#include "Includes.hpp"

std::string	Client::formatMsgsUsers()
{
	std::string		msg;

	msg.append(":");
	msg.append(_nickname);
	msg.append("!");
	// msg.append("~");
	msg.append(_username);
	msg.append("@");
	msg.append(getHostname());
	msg.append(" ");
	return (msg);
}

std::string	Client::formatMsgsReply(const int code)
{
	std::string	r;

	r.append(":");
	r.append(_server->getName());
	r.append(" ");
	if (code < 10)
		r.append("00");
	else if (code < 100)
		r.append("0");
	r.append(to_string(code));	//:hostname 025
	r.append(" ");
	if (getNickname() == "")
		r.append("*"); 			//:hostname 025 *
	else
		r.append(_nickname);	//:hostname 025 nick
	r.append(" ");
	return (r);
}

std::string	Client::numericReply(const int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4)
{
	switch(code)
	{
		case 1:
			return (RPL_WELCOME(arg1, arg2, arg3));
		case 2:
			return (RPL_YOURHOST(arg1, arg2));
		case 3:
			return (RPL_CREATED(arg1));
		case 4:
			return (RPL_MYINFO(arg1, arg2, arg3, arg4));
		// whois
		case 311:
			return (RPL_WHOISUSER(arg1, arg2, arg3, arg4));
		case 312:
			return (RPL_WHOISSERVER(arg1, arg2, arg3));
		case 313:
			return (RPL_WHOISOPERATOR(arg1, _server->isOper(this)));
		case 314:
			return (RPL_WHOWASUSER(arg1, arg2, arg3, arg4));
		case 317:
			return (RPL_WHOISIDLE(arg1, arg2)); // TO DO: CALL IDLE FUNCTION AS THE SECOND ARGUMENT
		case 318:
			return (RPL_ENDOFWHOIS(arg1));
		case 319:
			return (RPL_WHOISCHANNELS(arg1, arg2));
		case 401:
			return (ERR_NOSUCHNICK(arg1));
		case 406:
			return (ERR_WASNOSUCHNICK(arg1));
		// nick
		case 353:
			return (RPL_NAMREPLY(arg1, arg2));
		case 366:
			return (RPL_ENDOFNAMES(arg1));
		//whowas
		case 369:
			return (RPL_ENDOFWHOWAS(arg1));
		case 378:
			return (RPL_WHOISHOST(arg1, arg2, getIp()));
		// part
		case 403:
			return (ERR_NOSUCHCHANNEL(arg1));
		case 442:
			return (ERR_NOTONCHANNEL(arg1));
		case 431:
			return (ERR_NONICKNAMEGIVEN);
		case 432:
			return (ERR_ERRONEUSNICKNAME(arg1));
		case 433:
			return (ERR_NICKNAMEINUSE(arg1));
		case 461:
			return (ERR_NEEDMOREPARAMS(arg1));
		case 462:
			return (ERR_ALREADYREGISTERED);
		case 464:
			return (ERR_PASSWDMISMATCH);
		case 324:
			return (RPL_CHANNELMODEIS(arg1, arg2));
		//KICK
		case 476:
			return (ERR_BADCHANMASK(arg1));
		case 482:
			return (ERR_CHANOPRIVSNEEDED(arg1));
		case 441:
			return (ERR_USERNOTINCHANNEL(arg1, arg2));
		case 411:
			return (ERR_NORECIPIENT(arg1));
		case 412:
			return (ERR_NOTEXTTOSEND);
		case 404:
			return (ERR_CANNOTSENDTOCHAN(arg1));
		//PING PONG
		case 402:
			return (ERR_NOSUCHSERVER(arg1));
		case 409:
			return (ERR_NOORIGIN);
		//TOPIC
		case 331:
			return (RPL_NOTOPIC(arg1));
		case 332:
			return (RPL_TOPIC(arg1, arg2));
		//MODE
		case 472:
			return (ERR_UNKNOWNMODE(arg1));
		case 502:
			return (ERR_USERSDONTMATCH(arg1 ,arg2));
		case 696:
			return (ERR_NOKEY(arg1));
		//INVITE
		case 443:
			return (ERR_USERONCHANNEL(arg1, arg2));
		case 341:
			return (RPL_INVITING(arg1, arg2));
		case 473:
			return (ERR_INVITEONLYCHAN(arg1));
		// limitUser
		case 405:
			return (ERR_TOOMANYCHANNELS(arg1));
		case 471:
			return (ERR_CHANNELISFULL(arg1));
		case 697:
			return (ERR_NOLIMIT(arg1));
		case 698:
			return (ERR_NOOPER(arg1));
		case 475:
			return (ERR_BADCHANNELKEY(arg1));
		//LIST
		case 322:
			return (RPL_LIST(arg1, arg2, arg3, arg4));
		case 323:
			return (RPL_LISTEND);
		case 451:
			return (ERR_NOTREGISTERED(arg1, arg2));
		default:
			return ("BAD REPLY");
	}
	return ("");
}

void	Client::sendReply(const int code, std::string arg1, std::string arg2,\
										 std::string arg3, std::string arg4)
{
	std::string reply;

	reply = formatMsgsReply(code);
	reply += numericReply(code, arg1, arg2, arg3, arg4);
	reply += END_CHARACTERS;

	sendMsg(reply);
}

void	Client::sendMsg(std::string msg)
{
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
	if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
}

void	Client::sendMsgClient(std::string msg, Client *target)
{
	std::cout << FC(YELLOW, "Server Reply to be sent:\n") << msg << std::endl;
	if (send(target->getSocket(), msg.c_str(), msg.length(), 0) < 0)
			perror("SEND FAILED");
}

void	Client::sendMsgChannel(std::string msg, Channel *target)
{
	std::vector<Client *> members = target->getMembers();
	std::vector<Client *>::iterator it = members.begin();
	for ( ; it != members.end(); it++)
	{
		// std::cout << FC(GREEN, "members.client nick ->") << (*it)->getNickname() << std::endl;
		// std::cout << FC(RED, "sender nick ->") << _nickname << std::endl;
		if ((*it)->getNickname() != _nickname)
			sendMsgClient(msg, (*it));
	}
}

void	Client::sendMsgJoinedChannels(std::string msg)
{
	if (_joinedChannels.empty())
		return ;
	for (std::vector<Channel *>::iterator it = _joinedChannels.begin(); it != _joinedChannels.end(); it++)
		sendMsgChannel(msg, (*it));
}

void	Client::sendMsgSharedUsers(std::string msg)
{
	std::set<int> users;
	if (_joinedChannels.empty())
		return ;
	std::vector<Channel *>::iterator ch = _joinedChannels.begin();
	for ( ; ch != _joinedChannels.end(); ch++)
	{
		size_t old_size = users.size();
		std::vector<Client *> members = (*ch)->getMembers();
		std::vector<Client *>::iterator cl = members.begin();
		for ( ; cl != members.end(); cl++)
		{
			if ((*cl)->getId() != _id)
			{
				users.insert((*cl)->getId());
				if (users.size() > old_size)
				{
					sendMsgClient(msg, (*cl));
					++old_size;
				}
			}
		}
	}
}
