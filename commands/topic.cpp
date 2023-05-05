#include "../srcs/Includes.hpp"

void	Client::topic(Message *m)
{
	std::cout << FC(GREEN, ">\ttopic function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));
	
	Channel		*ch = _server->getChannel((m->params[0]));
	if (ch == NULL)//no existe canal
		return (sendReply(403, m->params[0], "", "", ""));

	std::string ch_name = ch->getName();
	if (!ch->hasClient(this))//no estoy en el canal
		return (sendReply(442, ch_name, "", "", ""));
	else if (ch->hasMode('t'))//solo oper cambia topic
	{
		if (!ch->isOperator(this))//no soy operador
			return (sendReply(482, ch_name, "", "", ""));
	}
	if (m->params.size() == 1)//get topic
	{
		std::string topic = ch->getTopic();
		if (topic.empty())
			return (sendReply(331, ch_name, "", "", ""));
		else
			return (sendReply(332, ch_name, topic, "", ""));
	}
	else if (m->params.size() == 2)//cambia topic
	{
		if (m->params[1].empty())
			ch->setTopic("");
		else
			ch->setTopic(m->params[1]);
		std::string msg = formatMsgsUsers();
		msg.append("TOPIC " + m->params[0] + " :" + m->params[1] + END_CHARACTERS);
		sendMsgChannel(msg, ch);
		sendMsg(msg);		
	}
}

// 3.2.4 Topic message

//       Command: TOPIC
//    Parameters: <channel> [ <topic> ]

//    The TOPIC command is used 
// 		to change or view the topic of a channel.
//    The topic for channel <channel> is returned if there is no <topic>
//    given.  If the <topic> parameter is present, the topic for that
//    channel will be changed, if this action is allowed for the user
//    requesting it. If the <topic> parameter is an empty string, the
//    topic for that channel will be removed.
// Si topic esta vacio da igual

//    Numeric Replies:
// ERR 461
// #define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")

// ERR 442    
// # define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel")
// - Returned by the server whenever a client tries to perform a
// channel affecting command for which the client isn't a member.

//ERR 482
// # define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator")			  

// // RPL331    
// # define RPL_NOTOPIC (channel) (channel + " :No topic is set")
// // RPL332
// # define RPL_TOPIC(channel, topic) (channel + " :" + topic)

// ERR477 no se usa
// # define ERR_NOCHANMODES(channel) (channel + " :Channel doesn't support modes")

// m->command	TOPIC
// m->params[0] channel
// m->params[1] topic
//  si presente se cambia el topic del channel
// si string vacia topic will be removed
// return (sendReply(477, ch_name, "", "", ""));//nose usa

//    Examples:

//    :WiZ!jto@tolsun.oulu.fi TOPIC #test :New topic ; User Wiz setting the
//                                    topic.

//    TOPIC #test :another topic      ; Command to set the topic on #test
//                                    to "another topic".

//    TOPIC #test :                   ; Command to clear the topic on
//                                    #test.

//    TOPIC #test                     ; Command to check the topic for
//                                    #test.
