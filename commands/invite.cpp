#include "../srcs/Includes.hpp"

// m->params[0] nick
// m->params[1] channel
void	Client::invite(Message *m)
{
	std::cout << FC(GREEN, ">\tinvite function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.size() < 2)
		return (sendReply(461, m->command, "", "", ""));
 	Client *to_invite = _server->getClient((m->params[0]));
	if (to_invite == NULL)
		return (sendReply(401, m->params[0], "", "", ""));//no such nick
	Channel		*ch = _server->getChannel((m->params[1]));
	if (ch != NULL)//existe el canal 
	{
		std::string ch_name = ch->getName();
		
		if (!ch->hasClient(this))//no estoy en el canal
			return (sendReply(442, ch_name, "", "", ""));
		else if (ch->hasClient(to_invite))//ya existe el cliente en el canal
			return (sendReply(443, to_invite->getNickname(), ch_name, "", ""));
		else if (ch->hasMode('i') && !ch->isOperator(this))//no soy operador
			return (sendReply(482, ch_name, "", "", ""));
		ch->addInvited(to_invite);
	}
	std::string msg = formatMsgsUsers();
	msg.append("INVITE " + m->params[0] + " :" + m->params[1] + END_CHARACTERS);
	sendMsgClient(msg, to_invite);
	sendReply(341, m->params[0], m->params[1], "", "");
}
//  [ client : 9000 ] INVITE raul__ #glingla 
//  [ server : 6667 ] :jonyoli!~user@freenode-oov.edl.vrebei.IP INVITE raul__ :#glingla 
//  [ server : 6667 ] :*.freenode.net 341 jonyoli raul__ :#glingla
//:hostname 025 pepi invitado #canal

// 3.2.7 Invite message

//       Command: INVITE
//    Parameters: <nickname> <channel>

//    The INVITE command is used to invite a user to a channel.  The
//    parameter <nickname> is the nickname of the person to be invited to
//    the target channel <channel>.  There is no requirement that the
//    channel the target user is being invited to must exist or be a valid
//    channel.  However, if the channel exists, only members of the channel
//    are allowed to invite other users.  When the channel has invite-only
//    flag set, only channel operators may issue INVITE command.
//    Only the user inviting and the user being invited will receive
//    notification of the invitation.  Other channel members are not
//    notified.  (This is unlike the MODE changes, and is occasionally the
//    source of trouble for users.)

//    Numeric Replies:

// ERR_NEEDMOREPARAMS    461 (command)
// ERR_NOSUCHNICK(nick) (nick + " :No such nick") 401
// ERR_NOTONCHANNEL   (channel)    442
// // ERR443
// # define ERR_USERONCHANNEL (user, channel) (user + " " + channel + " :is already on channel")
// ERR_CHANOPRIVSNEEDED 482 (channel)
// RPL341
// # define RPL_INVITING (channel, nick) (nick + " is inviting you to " + channel)
// RPL_AWAY

//    Examples:
//    :Angel!wings@irc.org INVITE Wiz #Dust

//                                    ; Message to WiZ when he has been
//                                    invited by user Angel to channel
//                                    #Dust

//    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
//                                    #Twilight_zone					

