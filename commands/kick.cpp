#include "../srcs/Includes.hpp"

void			Client::kick(Message *m)
{
	std::cout << FC(GREEN, ">\tkick function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.size() < 2)
		return (sendReply(461, m->command, "", "", ""));
	Channel		*ch = _server->getChannel((m->params[0]));
	if (ch == NULL)//no existe canal
		return (sendReply(403, m->params[0], "", "", ""));
	
	std::string ch_name = ch->getName();
	Client		*to_kick = _server->getClient((m->params[1]));
	
	if (to_kick == NULL)
		return (sendReply(401, m->params[1], "", "", ""));
	if (!ch->hasClient(this))//no estoy en el canal
		return (sendReply(442, ch_name, "", "", ""));
	else if (!ch->hasClient(to_kick))//no existe el cliente en el canal
		return (sendReply(441, m->params[1], ch_name, "", ""));
	else if (!ch->isOperator(this))//no soy operador
		return (sendReply(482, ch_name, "", "", ""));
	else
	{
		std::string part_msg;
		if (m->params.size() == 2)// PART_MSG not_defined
			part_msg = "has been kicked";
		else
			part_msg = m->params[2];
		std::string msg = formatMsgsUsers();
		msg.append("KICK " + ch_name + " " + m->params[1] + " :" + part_msg + END_CHARACTERS);
		sendMsgChannel(msg, ch);// a todos los clientes del canal
		sendMsg(msg);
		_server->removeClientFromChannel(to_kick, ch_name);
	}
}
// 3.2.8 Kick command

//       Command: KICK
//    Parameters: <channel> *( "," <channel> ) <user> *( "," <user> )
//                [<comment>]

//    The KICK command can be used to request the forced removal of a user
//    from a channel.  It causes the <user> to PART from the <channel> by
//    force.  For the message to be syntactically correct, there MUST be
//    either one channel parameter and multiple user parameter, or as many
//    channel parameters as there are user parameters.  If a "comment" is
//    given, this will be sent instead of the default message, the nickname
//    of the user issuing the KICK.

//    The server MUST NOT send KICK messages with multiple channels or
//    users to clients.  This is necessarily to maintain backward
//    compatibility with old client software.

//    Numeric Replies:
// #define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
// # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel") // ERR 403
/*
# define ERR_BADCHANMASK(channel) (channel+ " :Bad Channel Mask")// ERR 476
# define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator")//ERR 482
// - Any command requiring 'chanop' privileges (such as MODE messages) 
// MUST return this error if the client making the attempt is not a 
// chanop on the specified channel.
# define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel")// ERR 441    
// - Returned by the server to indicate that the target
// user of the command is not on the given channel.
# define ERR_NOTONCHANNEL(channel) (channel + " :You're not on that channel")// ERR 442    
// - Returned by the server whenever a client tries to perform a
// channel affecting command for which the client isn't a member.
*/
//    Examples:
//    KICK &Melbourne Matthew         ; Command to kick Matthew from
//                                    &Melbourne

//    KICK #Finnish John :Speaking English
//                                    ; Command to kick John from #Finnish
//                                    using "Speaking English" as the
//                                    reason (comment).

//    :WiZ!jto@tolsun.oulu.fi KICK #Finnish John
//                                    ; KICK message on channel #Finnish
//                                    from WiZ to remove John from channel
// me hechan
// [ server : 6667 ] :raul_!~raul@freenode-s3k.srb.vrebei.IP KICK #glingla pupi

// hecho raul_ sin msg
//  [ client : 9000 ] KICK #buinbui raul_ : 
//  [ server : 6667 ] :pupi!~raul@freenode-s3k.srb.vrebei.IP KICK #buinbui raul_ : 

// hecho raul_ con msg
// [ client : 9000 ] 	KICK #buinbui raul_ :eres un zopenco 
// [ server : 6667 ] 	:pupi!~raul@freenode-s3k.srb.vrebei.IP KICK #buinbui raul_ :eres un zopenco 
