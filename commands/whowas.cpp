#include "../srcs/Includes.hpp"

// made by: epresa-c

void			Client::whowas(Message *m){
	std::cout << FC(GREEN, ">\twhowas function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	int found = false;

	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));

	for (size_t i = _nicksHistory.size() - 1; i > 0 ; i--)
	{
		if (_nicksHistory[i].nick == m->params[0])
		{
			sendReply(314, _nicksHistory[i].nick, _nicksHistory[i].user, _nicksHistory[i].host, _nicksHistory[i].realname);
			sendReply(312, _nicksHistory[i].nick, _nicksHistory[i].server,  ctime(_nicksHistory[i].serverStartTime), "");
 			found = true;
			std::cout << "found = " << std::boolalpha << found << std::endl;
		}
	}
	if (found == false)
		sendReply(406, m->params[0], "", "", "");
	sendReply(369, m->params[0], "", "", "");
}
