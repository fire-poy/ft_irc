#include "../srcs/Includes.hpp"

// made by: mpons
// m->params[0] = channel or list of channels
// m->params[1] = part message
void			Client::part(Message *m){
	std::cout << FC(GREEN, ">\tpart function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));

	std::string part_msg = "";
	if (m->params.size() == 1)// PART_MSG not_defined
		part_msg = "hasta la vista Baby";
	else
		part_msg = m->params[1];

	std::stringstream ss(m->params[0]);
	std::string chan;
	while (std::getline(ss, chan, ','))
	{
		Channel *target = _server->getChannel((chan));
		if (target == NULL)
			sendReply(403, chan, "", "", "");
		else if (!target->hasClient(this))
			sendReply(442, target->getName(), "", "", "");
		else
		{
			std::string msg = formatMsgsUsers();
			msg.append("PART " + chan + " :" + part_msg + END_CHARACTERS);
			sendMsgChannel(msg, target);
			sendMsg(msg);
			_server->removeClientFromChannel(this, chan);
		}
	}
}

// [ client : 8000 ] b'PART #PATATA\r\n'
//  [ server : 6667 ] b':raul_!~raul@freenode-b8j.srb.vrebei.IP PART :#PATATA\r\n'
// [ client : 8000 ] b'PART #PATATA :me voy\r\n'
//  [ server : 6667 ] b':raul_!~raul@freenode-b8j.srb.vrebei.IP PART #PATATA :"me voy"\r\n'
// 3.2.2 Part message

//       Command: PART
//    Parameters: <channel> *( "," <channel> ) [ <Part Message> ]

//    The PART command causes the user sending the message to be removed
//    from the list of active _members for all given channels listed in the
//    parameter string.  If a "Part Message" is given, this will be sent
//    instead of the default message, the nickname.  This request is always
//    granted by the server.

//    Servers MUST be able to parse arguments in the form of a list of
//    target, but SHOULD NOT use lists when sending PART messages to
//    clients.

//    Numeric Replies:

// 442
// # define ERR_NOTONCHANNEL(channel) channel + " :You're not on that channel"

// 403
// # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel")

//            ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
//            ERR_NOTONCHANNEL

//    Examples:

//    PART #twilight_zone             ; Command to leave channel
//                                    "#twilight_zone"

//    PART #oz-ops,&group5            ; Command to leave both channels
//                                    "&group5" and "#oz-ops".

//    :WiZ!jto@tolsun.oulu.fi PART #playzone :I lost
//                                    ; User WiZ leaving channel
//                                    "#playzone" with the message "I
//                                    lost".

