#include "../srcs/Includes.hpp"

void	Client::channelModes(Message *m)
{
	Channel	*ch = _server->getChannel((m->params[0]));
	if (ch == NULL)
		return (sendReply(403, m->params[0], "", "", ""));

	std::string ch_name = ch->getName();
	if (!ch->hasClient(this))
		sendReply(442, ch_name, "", "", "");
	else if (m->params.size() == 1)	//return mode from channel
		return (sendReply(324, ch_name, ch->getModes(), "", ""));
	std::string set = m->params[1];
	if (set == "b")
		return ;
	else if (!ch->isOperator(this))
		return (sendReply(482, ch_name, "", "", ""));


	if (set.empty() || (set[0] != '+' && set[0] != '-') || set.size() < 2)
	{
		std::string err;
		err = set.at(0);
		return (sendReply(472, err, ch_name, "", ""));
	}

	size_t		arg_n = 2;
	std::string	error;
	std::string	seted;
	std::string	args;
	std::string::iterator it = set.begin() + 1;
	Client	*oper = NULL;

	for ( ; it != set.end() ; ++it)
	{
		switch (*it)
		{
			case 'n':
			case 't':
			case 'i':
				if (set[0] == '+')
					seted += ch->setMode(*it);
				if (set[0] == '-')
					seted += ch->unsetMode(*it);
			break;

			case 'l':
				if (set[0] == '-')
					seted += ch->unsetMode(*it);
				else if (set[0] == '+')
				{
					if (m->params.size() < arg_n + 1) // 0 #ch, 1 mode, 2arg1, arg2 arg3
					{
						sendReply(697, m->command, "", "", "");
						break;
					}
					if (isInt(m->params[arg_n]))
					{
						ch->setUserLimit(m->params[arg_n]);
						args += m->params[arg_n] + " ";
						ch->setMode(*it);
						seted += 'l';
						++arg_n;
					}
				}
			break;

			case 'k':
				if (m->params.size() < arg_n + 1)
				{
					sendReply(696 , ch->getName(), "", "", "");
					break;
				}
				if (set[0] == '-')
				{
					if (ch->isValidKey(m->params[arg_n]))
					{
						seted += ch->unsetMode(*it);
						args += m->params[arg_n] + " ";
					}
				}
				else if (set[0] == '+')
				{
					ch->setMode(*it);
					ch->setChannelKey(m->params[arg_n]);
					seted += 'k';
					args += m->params[arg_n] + " ";
				}
				++arg_n;
			break;

			case 'o':
				if (m->params.size() < arg_n + 1)
				{
					sendReply(698, m->command, "", "", "");
					break;
				}
				oper = _server->getClient((m->params[arg_n]));
				if (oper == NULL)
				{
					sendReply(401, m->params[arg_n], "", "", "");
					break;
				}
				if (!ch->hasClient(oper))
				{
					sendReply(441, m->params[arg_n], ch_name, "", "");
					break;
				}
				else if (set[0] == '+')
					ch->addOperator(oper);
				else if (set[0] == '-')
					ch->removeOperator(oper);
				seted += 'o';
				args += m->params[arg_n] + " ";
				++arg_n;
			break;

			default:
				error = *it;
				sendReply(472, error, "", "", "");
			break;
		}
	}
	removeZeros(seted);
	if (!seted.empty())
	{
		std::string msg = formatMsgsUsers();
		msg.append("MODE " + ch_name + " " + set[0] + seted + " :" + args + END_CHARACTERS);
		sendMsgChannel(msg, ch);
		sendMsg(msg);
	}
}

void	Client::userModes(Message *m)
{
	if (m->params[0] == _nickname)
	{
		std::string msg;
		if (!m->params[1].compare("+i"))
		{
			_hostname = "IP";
			_hostname += ".hosted-by-42lausanne.ch";
			msg = formatMsgsUsers();
			msg.append("MODE " + getNickname() + " " + m->params[1] + END_CHARACTERS);
		}
		else if(!m->params[1].compare("-i"))
		{
			_hostname = _ip;
			_hostname += ".hosted-by-42lausanne.ch";
			msg = formatMsgsUsers();
			msg.append("MODE " + getNickname() + " " + m->params[1] + END_CHARACTERS);
		}
		sendMsg(msg);
	}
	else if (m->params.size() == 1)
		return (sendReply(502, "view", "modes", "", "")); //Can't view modes for other users
	else if (m->params.size() == 2)
		return (sendReply(502, "change", "mode", "", "")); //Can't change mode for other users
}

// m->params[0] == channel ou nick
// m->params[1] == mode to set
// m->params[2..] == parameter to mode 'k', 'o' or 'l' mode to set
void	Client::mode(Message *m)
{
	std::cout << FC(GREEN, ">\tmode function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	if (m->params.empty())
		return (sendReply(461, m->command, "", "", ""));
	if (m->params[0].at(0) == '#')
		channelModes(m);
	else
		userModes(m);
}

// k + o - viene siempre con arg
// [ client : 9000 ] MODE #glingla -kl pass -> pass es enviado por irssi
//  [ server : 6667 ] :pepi!~raul@freenode-nop.edl.vrebei.IP MODE #glingla -kl :pass
//  [ client : 9000 ] MODE #glingla +klo pass 42 cuchi
//  [ server : 6667 ] :pepi!~raul@freenode-nop.edl.vrebei.IP MODE #glingla +klo pass 42 :cuchi
//  [ server : 6667 ] :pepi!~raul@freenode-nop.edl.vrebei.IP MODE #glingla +klo pass 42 :cuchi

//  [ client : 9000 ] MODE #glingla +kol pass chapurri 40
//  [ server : 6667 ] :*.freenode.net 401 cuchi chapurri :No such nick
//  [ server : 6667 ] :cuchi!~raul@freenode-nop.edl.vrebei.IP MODE #glingla +kl pass :40
//  [ server : 6667 ] :cuchi!~raul@freenode-nop.edl.vrebei.IP MODE #glingla +kl pass :40

// [ server : 6667 ] :*.freenode.net 472 pepi q :is not a recognised channel mode.
// +l
//  [ client : 9000 ] MODE #glingla +l 1
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +l :1
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +l :1
//  [ client : 9000 ] PART #glingla
//  [ server : 6667 ] :raul_!~raul@freenode-ioq.edl.vrebei.IP PART :#glingla
//  [ server : 6667 ] :raul_!~raul@freenode-ioq.edl.vrebei.IP PART :#glingla
//  [ client : 9000 ] JOIN #glingla
//  [ server : 6667 ] :*.freenode.net 471 raul_ #glingla :Cannot join channel (channel is full)

// le agrega el @ al nick cuando es operador
// /mode o nick no funciona hay que poner +
// un operador puede quitarle priv a los otros y viceversa
//  [ client : 9000 ] MODE #glingla +o pepi
//  [ server : 6667 ] :raul_!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +o :pepi
//  [ server : 6667 ] :raul_!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +o :pepi

// +k pass
//  [ client : 9000 ] MODE k papi
//  [ server : 6667 ] :*.freenode.net 501 pepi p :is not a recognised user mode.
//  [ server : 6667 ] :*.freenode.net 501 pepi a :is not a recognised user mode.
//  [ server : 6667 ] :*.freenode.net 501 pepi p :is not a recognised user mode.
//  [ server : 6667 ] :*.freenode.net 502 pepi :Can't change mode for other users
//  [ client : 9000 ] MODE #glingla +k papi
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +k :papi

//  [ client : 9000 ] JOIN #glingla
//  [ server : 6667 ] :*.freenode.net 475 raul_ #glingla :Cannot join channel (incorrect channel key)
//  [ client : 9000 ] JOIN #glingla papi
//  [ server : 6667 ] :*.freenode.net 471 raul_ #glingla :Cannot join channel (channel is full)

// [ client : 9000 ] MODE #glingla +k
//  [ server : 6667 ] :*.freenode.net 696 pepi #glingla k * :You must specify a parameter for the key mode. Syntax: <key>.
//  [ client : 9000 ] MODE #glingla +kl pass
//  [ server : 6667 ] :*.freenode.net 696 pepi #glingla l * :You must specify a parameter for the limit mode. Syntax: <limit>.
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +k :pass
//  [ client : 9000 ] PING *.freenode.net
//  [ server : 6667 ] :*.freenode.net PONG *.freenode.net :*.freenode.net
//  [ client : 9000 ] MODE #glingla +kl pass 4
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +l :4
//  [ client : 9000 ] PING *.freenode.net
//  [ server : 6667 ] :*.freenode.net PONG *.freenode.net :*.freenode.net
//  [ client : 9000 ] MODE #glingla -kl pass
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla -kl :pass
//  [ client : 9000 ] MODE #glingla +kl pass 4
//  [ server : 6667 ] :pepi!~raul@freenode-ioq.edl.vrebei.IP MODE #glingla +kl pass :4

//  [ client : 9000 ] MODE #anime b
//  [ server : 6667 ] :ChanServ!services@services.freenode.net NOTICE raul_ :[#anime] Welcome to freenode #anime IRC! Be aware conversations can be slow at times, so if you don't get a response immediately, please do stick around ☺
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!*@freenode/user/antifascist elon.hub :1676764361
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!~technet@* elon.hub :1676764361
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!~simon@* elon.hub :1676764361
//  [ server : 6667 ] :*.freenode.net 367 raul_ #anime *!*@freenode-frpvje.rlp1.7tn1.4hb93e.IP elon.hub :1676764361
//  [ server : 6667 ] :*.freenode.net 368 raul_ #anime :End of channel ban list

// [ client : 8000 ] MODE raul +i
// [ server : 6667 ] MODE raul +i

//  [ client : 8000 ] MODE #usa
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :+nt

//hay que bannear a algien me imagino para que pase a modo +b
//  [ client : 8000 ] MODE #usa +b
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :+b

//  [ client : 8000 ] MODE #usa -i
//  [ server : 6667 ] :*.42irc.net 324 raul #usa :-i

//  [ client : 9000 ] MODE #pitusa -sizpqwe
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :-si
//  [ server : 6667 ] :*.freenode.net 472 pepi q :is not a recognised channel mode.
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :-si

//  [ client : 9000 ] MODE #pitusa +si
//a todo los del canal
//  [ server : 6667 ] :pepi!~raul@freenode-s3k.srb.vrebei.IP MODE #pitusa :+si

// // MODE +i (invite_only channel)
// // MODE +t (Change the channel topic in a mode +t channel)
//  n - no messages to channel from clients on the outside;
	// }
//  c-> MODE raul
//  s-> :*.freenode.net 502 raul_ :Can't view modes for other users
//  c-> MODE raul -i
//  s-> :*.freenode.net 502 glingla :Can't change mode for other users


// ERR472   ERR_UNKNOWNMODE(char, channel) (char + " :is unknown mode char to me for " + channel)
// RPL325
// # define RPL_UNIQOPIS(channel, nickname) (channel + " " + nickname)
// RPL346
// # define RPL_INVITELIST(channel, invitemask) (channel + " " + invitemask)
// RPL347
// # define RPL_ENDOFINVITELIST(channel) (channel + " :End of channel invite list")

//  [ client : 8000 ] MODE Rony +i
//  [ server : 6667 ] :Rony!raul@127.0.0.1 MODE Rony +i

// 3.2.3 Channel mode message

//       Command: MODE
//    Parameters: <channel> *( ( "-" / "+" ) *<modes> *<modeparams> )

//    The MODE command is provided so that users may query and change the
//    characteristics of a channel.  For more details on available modes
//    and their uses, see "Internet Relay Chat: Channel Management" [IRC-
//    CHAN].  Note that there is a maximum limit of three (3) changes per
//    command for modes that take a parameter.

//    Numeric Replies:

// ERR 461
// #define ERR_NEEDMOREPARAMS(command) (command + " :Not enough parameters")
//    477    ERR_NOCHANMODES              "<channel> :Channel doesn't support modes" no se usa mepa

//ERR 482
// # define ERR_CHANOPRIVSNEEDED(channel) (channel + " :You're not channel operator")

// ERR 441
// # define ERR_USERNOTINCHANNEL(nick, channel) (nick + " " + channel + " :They aren't on that channel")

// 324
// # define RPL_CHANNELMODEIS(channel, mode) (channel + " :" + mode)
// :*server_name 324 nick #CHANNEL :+nt
// :DESKTOP-MQD5OHQ 324 Rony #people [+n]  ccomis


// // ERR467
// # define ERR_KEYSET(channel) (channel + " :Channel key already set")

// // ERR472
// # define ERR_UNKNOWNMODE(char, channel) (char + " :is unknown mode char to me for " + channel)

// // RPL325
// # define RPL_UNIQOPIS(channel, nickname) (channel + " " + nickname)

// // RPL346
// # define RPL_INVITELIST(channel, invitemask) (channel + " " + invitemask)

// // RPL347
// # define RPL_ENDOFINVITELIST(channel) (channel + " :End of channel invite list")

//    The following examples are given to help understanding the syntax of
//    the MODE command, but refer to modes defined in "Internet Relay Chat:
//    Channel Management" [IRC-CHAN].
