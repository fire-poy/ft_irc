#include "../srcs/Includes.hpp"

	// m->params[0] target
	// m->params[1] text
void			Client::privmsg(Message *m)
{
	std::cout << FC(GREEN, ">\tprivmsg function executed ") <<"by client id: " << _id << "\t<" << std::endl;
	if (m->params.empty())//no target
		return (sendReply(411, m->command, "", "", ""));
	else if (m->params.size() == 1)//no text
		return (sendReply(412, "", "", "", ""));
	
	Channel	*ch = _server->getChannel(m->params[0]);
	if (ch != NULL) //mandamos al canal
	{
		std::string	ch_name = ch->getName();
		if (ch->hasMode('n') && !ch->hasClient(this))//no estoy en el canal
			sendReply(404, ch_name, "", "", "");
		else {
		std::string msg = formatMsgsUsers();
		msg.append("PRIVMSG " + ch_name + " :" + m->params[1] + END_CHARACTERS);
		sendMsgChannel(msg, ch);
		}
	}
	else //no es un canal
	{
		Client	*target = _server->getClient(m->params[0]);
		if (target == NULL)//no esta ese nick
			return (sendReply(401, m->params[0], "", "", ""));
		else
		{
			std::string msg = formatMsgsUsers();
			msg.append("PRIVMSG " + m->params[0] + " :" + m->params[1] + END_CHARACTERS);
			sendMsgClient(msg, target);		
		}
	}
}

// 3.3.1 Private messages

//       Command: PRIVMSG
//    Parameters: <msgtarget> <text to be sent>

//    PRIVMSG is used to send private messages between users, as well as to
//    send messages to channels.  <msgtarget> is usually the nickname of
//    the recipient of the message, or a channel name.

//    The <msgtarget> parameter may also be a host mask (#<mask>) or server
//    mask ($<mask>).  In both cases the server will only send the PRIVMSG
//    to those who have a server or host matching the mask.  The mask MUST
//    have at least 1 (one) "." in it and no wildcards following the last
//    ".".  This requirement exists to prevent people sending messages to
//    "#*" or "$*", which would broadcast to all users.  Wildcards are the
//    '*' and '?'  characters.  This extension to the PRIVMSG command is
//    only available to operators.

//    Numeric Replies:
// // ERR411    
// # define ERR_NORECIPIENT(command) (":No recipient given (" + command + ")")
// // ERR412    
// # define ERR_NOTEXTTOSEND ":No text to send"
// // ERR404    
// # define ERR_CANNOTSENDTOCHAN(channel_name) (channel_name + " :Cannot send to channel")

// RPL 401 # define ERR_NOSUCHNICK(nick) (nick + " :No such nick")

// // ERR413    
// # define ERR_NOTOPLEVEL(mask) (mask + " :No toplevel domain specified")
// // ERR414    
// # define ERR_WILDTOPLEVEL "<mask> :Wildcard in toplevel domain"
// // ERR407    
// # define ERR_TOOMANYTARGETS "<target> :<error code> recipients. <abort message>"
// - Returned to a client which is attempting to send a
// PRIVMSG/NOTICE using the user@host destination format
// and for a user@host which has several occurrences.

// - Returned to a client which trying to send a
// PRIVMSG/NOTICE to too many recipients.

// - Returned to a client which is attempting to JOIN a safe
// channel using the shortname when there are more than one
// such channel.
//RPL301    
// # define RPL_AWAY "<nick> :<away message>"

//    Examples:
//    :Angel!wings@irc.org PRIVMSG Wiz :Are you receiving this message ?
//                                    ; Message from Angel to Wiz.

//    PRIVMSG Angel :yes I'm receiving it !
//                                    ; Command to send a message to Angel.
