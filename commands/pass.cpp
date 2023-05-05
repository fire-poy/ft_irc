#include "../srcs/Includes.hpp"

// made by: mpons
// Numeric Replies: ERR_NEEDMOREPARAMS ERR_ALREADYREGISTRED
// Example: PASS secretpasswordhere
void	Client::welcome()
{
	sendReply(1, getNickname(), getUsername(), getHostname(), "");
	sendReply(2, _server->getName(), "1.0", "", "");
	sendReply(3, ctime(_server->getStartTime()), "", "", "");
	sendReply(4, _server->getName(), "1.0", "Channel modes +ntikl", "");
}

void	Client::pass(Message *m)
{
	std::cout << FC(GREEN, ">\tpass function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	std::string pass = "PASS";

	if (_register.passHasBeenExecuted)
		return (sendReply(462, "", "", "", ""));
	_hostname = _ip;
	_hostname += ".hosted-by-42lausanne.ch";
	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));
	else if (!m->params[0].compare(_server->getPassword()))
		addCommandToRegister(pass);
	else //wrong pass
	{
		_pass = PASS_WRONG;
		std::cout << BOLDCYAN << "Realpass = "<< _server->getPassword().c_str() << RESET << std::endl;
		return (sendReply(464, "", "", "", ""));
	}
}
