#include "../srcs/Includes.hpp"

void			Client::notice(Message *m)
{
	std::cout << FC(GREEN, ">\tnotice function executed ") <<"by client id: " << _id << "\t<" << std::endl;
	if (m->params.empty())//no target
		return;
	else if (m->params.size() == 1)//no text
		return;
	
	Channel	*ch = _server->getChannel(m->params[0]);
	if (ch != NULL) //mandamos al canal
	{
		std::string	ch_name = ch->getName();
		if (ch->hasMode('n') && !ch->hasClient(this))//no estoy en el canal
			return;
		else
		{
			std::string msg = formatMsgsUsers();
			msg.append("NOTICE " + ch_name + " :" + m->params[1] + END_CHARACTERS);
			sendMsgChannel(msg, ch);
		}
	}
	else //no es un canal
	{
		Client	*target = _server->getClient(m->params[0]);
		if (target == NULL)//no esta ese nick
			return;
		else
		{
			std::string msg = formatMsgsUsers();
			msg.append("NOTICE " + m->params[0] + " :" + m->params[1] + END_CHARACTERS);
			sendMsgClient(msg, target);		
		}
	}
}

// 	3.3.2 Notice
//    Command: NOTICE
//    Parameters: <msgtarget> <text>

//    The NOTICE command is used similarly to PRIVMSG.  

// The difference
//    between NOTICE and PRIVMSG is that 
//	  automatic replies MUST NEVER be sent in response to a NOTICE message.
//	  This rule applies to servers too - they MUST NOT send any error reply back to the client on
//    receipt of a notice.  The object of this rule is to avoid loops
//    between clients automatically sending something in response to
//    something it received.

//    This command is available to services as well as users.

//    This is typically used by services, and automatons (clients with
//    either an AI or other interactive program controlling their actions).

//    See PRIVMSG for more details on replies and examples.

