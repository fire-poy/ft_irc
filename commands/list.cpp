#include "../srcs/Includes.hpp"

// m->params[0] channel
// m->params[1] target (multiserver) not used
void			Client::list(Message *m)
{
	std::cout << FC(GREEN, ">\tlist function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	std::vector<Channel *> *chList = _server->getChannelList();
	if (m->params.empty())
	{
		std::vector<Channel *>::iterator it = chList->begin();
		for ( ; it != chList->end(); ++it)
			sendReply(322, (*it)->getName(), to_string((*it)->getMembers().size()), (*it)->getModes(), (*it)->getTopic());
		return (sendReply(323, "", "", "", ""));
	}
	if (!m->params[0].empty())
	{
		std::stringstream ss(m->params[0]);
		std::string chan;
		while (std::getline(ss, chan, ','))
		{
			Channel *ch = _server->getChannel(chan);
			if (ch != NULL)
				(sendReply(322, ch->getName(), to_string(ch->getMembers().size()), ch->getModes(), ch->getTopic()));
		}
		return (sendReply(323, "", "", "", ""));
	}
}

//  [ server : 6667 ] :*.freenode.net 321 raul_ Channel :Users Name
//:*.freenode.net 322 raul_ chanelname nb_user :[modes] topic
//:*.freenode.net 322 raul_ ##C 44 :[+nrt] C Programming Community | Paste (>3 lines): https://bpa.st/ or http://ix.io/ | Wiki: http://www.iso-9899.info/ | Books: http://www.iso-9899.info/wiki/Books | C2X Charter: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2086.htm | Standard: http://iso-9899.info/wiki/The_Standard | Off-topic: ##c-offtopic
//  [ server : 6667 ] :*.freenode.net 323 raul_ :End of channel list.

//  [ client : 9000 ] LIST #bitcoin*
//  [ server : 6667 ] :*.freenode.net 321 raul_ Channel :Users Name
//  [ server : 6667 ] :*.freenode.net 322 raul_ #bitcoin.cz 1 :[+nt]
//  [ server : 6667 ] :*.freenode.net 322 raul_ #bitcoin-otc-eu 1 :[+nt]

// 3.2.6 List message

//       Command: LIST
//    Parameters: [ <channel> *( "," <channel> ) [ <target> ] ]

//    The list command is used to list channels and their topics.  If the
//    <channel> parameter is used, only the status of that channel is
//    displayed.

//    If the <target> parameter is specified, the request is forwarded to
//    that server which will generate the reply.

//    Wildcards are allowed in the <target> parameter.

//    Numeric Replies:
//            ERR_TOOMANYMATCHES              ERR_NOSUCHSERVER
//            RPL_LIST                        RPL_LISTEND

//    Examples:

//    LIST                            ; Command to list all channels.

//    LIST #twilight_zone,#42         ; Command to list channels
//                                    #twilight_zone and #42
