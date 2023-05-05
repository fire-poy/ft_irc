#include "../srcs/Includes.hpp"

// made by: epresa-c

void			Client::user(Message *m)
{
	std::cout << FC(GREEN, ">\tuser function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	std::string user = "USER";

	if (_register.userHasBeenExecuted)
		return (sendReply(462, "", "", "", ""));
	if (m->params.size() < 4)
		return (sendReply(461, m->command, "", "", ""));

	_username = m->params[0];

	(void) m->params[1]; // hostname provided by client. Unused, we replace them by:
	_hostname = _ip;
	_hostname += ".hosted-by-42lausanne.ch";

	(void) m->params[2]; // servername provided by client. Unused.

	_realname = m->params[3];
	addCommandToRegister(user);
}
