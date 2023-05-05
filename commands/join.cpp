#include "../srcs/Includes.hpp"

//  made by: mpons
void	Client::join(Message *m)
{
	std::cout << FC(GREEN, ">\tjoin function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));

	std::stringstream ss(m->params[0]);
	std::string chan;
	while (std::getline(ss, chan, ','))
	{
		if (_joinedChannels.size() >= MAX_CHANNEL_PER_USER)
		{
				sendReply(405, chan, "", "", "");
				break;
		}
		if ((chan[0] != '#' && chan[0] != '+' && chan[0] != '!') || chan.length() > 50)
		{
			sendReply(403, chan, "", "", "");
			continue;
		}
		std::cout << FC(GREEN, "Canal =") << chan << std::endl;
		_server->createChannel(this, chan);
		Channel *ch = _server->getChannel(chan);
		if (!ch)
		{
			std::cerr << FC(RED, "Channel =") << chan << "was not created (not enough memory)" << std::endl;
			return ;
		}
		if (ch->hasMode('k'))
		{
			if (m->params.size() < 2 || !ch->isValidKey(m->params[1]))
				return (sendReply(475, chan, "", "", ""));
		}
		if (ch->hasMode('i') && !ch->isInvited(this))
			return (sendReply(473, chan, "", "", ""));
		if (ch->hasMode('l') && ch->getMembers().size() >= ch->getUserLimit())
			return (sendReply(471, chan, "", "", ""));
		if (ch->hasClient(this))
			return (sendReply(443, _nickname, chan, "", ""));
		_server->addClientToChannel(this, chan);
		std::string msg = formatMsgsUsers();
		msg.append("JOIN " + chan + END_CHARACTERS);
		sendMsgChannel(msg, ch);
		sendMsg(msg);
		std::string topic = ch->getTopic();
		if (!(topic.empty()))
			sendReply(332, chan, topic, "", "");
		sendReply(353, chan, ch->getMembersNicks(), "", "");
		sendReply(366, chan, "", "", "");
	}
}
// [ client : 9000 ] JOIN #buinbui 
//  [ server : 6667 ] :mikeymi!~raul@freenode-oov.edl.vrebei.IP JOIN :#buinbui 
//  [ server : 6667 ] :*.freenode.net 353 mikeymi = #buinbui :@jonyony mikeymi 
//  [ server : 6667 ] :*.freenode.net 366 mikeymi #buinbui :End of /NAMES list. 
// the other client gets
//  [ server : 6667 ] :mikeymi!~raul@freenode-oov.edl.vrebei.IP JOIN :#buinbui 

// join ,a ->join # + join a
//  3.2.1 Join message
//    Command: JOIN
//    Parameters: ( <channel> *( "," <channel> ) [ <key> *( "," <key> ) ] )
//                / "0"

//    The JOIN command is used by a user to request to start listening to
//    the specific channel.  Servers MUST be able to parse arguments in the
//    form of a list of target, but SHOULD NOT use lists when sending JOIN
//    messages to clients.

//    Once a user has joined a channel, he receives information about
//    all commands his server receives affecting the channel.
//	  This includes JOIN, MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.
//    This allows channel _members to keep track of the other channel
//    _members, as well as channel modes.

//    If a JOIN is successful, the user receives a JOIN message as
//    confirmation and is then sent the channel's topic (using RPL_TOPIC) and
//    the list of users who are on the channel (using RPL_NAMREPLY), which
//    MUST include the user joining.

//    Note that this message accepts a special argument ("0"), which is
//    a special request to leave all channels the user is currently a member
//    of.  The server will process this message as if the user had sent
//    a PART command (See Section 3.2.2) for each channel he is a member
//    of.

//    Numeric Replies:

// //473
// # define ERR_INVITEONLYCHAN(channel) (channel + " :Cannot join channel (+i)")

// //474
// # define ERR_BANNEDFROMCHAN(channel) (channel + " :Cannot join channel (+b)")

// //475
// # define ERR_BADCHANNELKEY(channel) (channel + " :Cannot join channel (+k)")

// // 471
// # define ERR_CHANNELISFULL(channel) (channel + " :Cannot join channel (+l)")

// //405
// # define ERR_TOOMANYCHANNELS(channel_name) (channel_name + " :You have joined too many channels")

// //407
// # define ERR_TOOMANYTARGETS(target, error_code, abort_message) (target + " :" + error code + "recipients. " + abort message)
// 476
// # define ERR_BADCHANMASK(channel) (channel + " :Bad Channel Mask")

// 403
// # define ERR_NOSUCHCHANNEL(channel_name) (channel_name + " :No such channel")


//437
// # define ERR_UNAVAILRESOURCE(nick_or_channel) (nick_or_channel + " :Nick/channel is temporarily unavailable")

//332
// # define RPL_TOPIC(channel, topic) (channel + " :" topic)

//353
// # define RPL_NAMREPLY(channel, nick) ("= " channel + " :@ " + nick)
// = #lol :@Guest36096 mikeWpit\r\n
//"( "=" / "*" / "@" ) <channel>
//:[ "@" / "+" ] <nick> *( " " [ "@" / "+" ] <nick> )

//- "@" is used for secret channels, "*" for private channels,
//  and "=" for others (public channels).

//366
// # define RPL_ENDOFNAMES(channel) (channel + " :End of NAMES list")

//          - To reply to a NAMES message, a reply pair consisting
//            of RPL_NAMREPLY and RPL_ENDOFNAMES is sent by the
//            server back to the client.  If there is no channel
//            found as in the query, then only RPL_ENDOFNAMES is
//            returned.  The exception to this is when a NAMES
//            message is sent with no parameters and all visible
//            channels and contents are sent back in a series of
//            RPL_NAMEREPLY messages with a RPL_ENDOFNAMES to mark
//            the end.
