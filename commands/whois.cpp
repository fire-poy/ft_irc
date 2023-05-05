#include "../srcs/Includes.hpp"

// made by: epresa-c

void			Client::whois(Message *m){
	std::cout << FC(GREEN, ">\twhois function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	Client *ptr;

	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));

	std::vector<std::string> subsplited = subSplitString(m->params[0], ',');

	for (size_t i = 0; i < subsplited.size(); i++)
	{
		if ((ptr = _server->getClient(subsplited[i])) != NULL)
		{
			sendReply(311, ptr->getNickname(), ptr->getUsername(), ptr->getHostname(), ptr->getRealname());
			if (ptr->getNickname() == _nickname)
				sendReply(378, ptr->getUsername(), ptr->getHostname(), "", "");
			sendReply(312, subsplited[i], _server->getName(), ctime(_server->getStartTime()), "");
			sendReply(317, subsplited[i], to_string(ptr->getIdle()), "", ""); // last connection
			if (ptr->_joinedChannels.size() != 0)
			{
				std::string channelsList;
				for (size_t i = 0; i < ptr->_joinedChannels.size(); i++)
				{
					channelsList += ptr->_joinedChannels.at(i)->getName();
					channelsList += " ";
				}
				sendReply(319, subsplited[i], channelsList, "", "");
			}
		}
		else
			sendReply(401, subsplited[i], "", "", "");
		sendReply(318, subsplited[i], "", "", "");
	}
}
