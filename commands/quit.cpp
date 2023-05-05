#include "../srcs/Includes.hpp"

// made by: epresa-c
// modified by :mpons
void	Client::leaveAll()
{
	std::vector<Channel *>::iterator it = _joinedChannels.begin();
	while (it != _joinedChannels.end())
		_server->removeClientFromChannel(this, (*it)->getName());
}

void			Client::quit(Message *m)
{
	std::cout << FC(GREEN ,">\tquit function executed ") << "by client id: " << _id << "\t\t<" << std::endl;
	std::string part_msg = "";

	if (m->params.empty())
		part_msg = "hasta la vista Baby";
	else
		part_msg = m->params[0];
	std::string msg = formatMsgsUsers();
	msg.append("QUIT :Quit: " + part_msg + END_CHARACTERS);
	sendMsg(msg);
	sendMsgSharedUsers(msg); 
	leaveAll();
	_quiting = true;
}

// ERGO CHAT
// [ client : 9000 ] NICK pepi 
//  [ server : 6667 ] :raul_!~u@2v9h9hjx6pxc6.oragono NICK pepi 
//  [ server : 6667 ] :raul_!~u@2v9h9hjx6pxc6.oragono NICK pepi 
//  [ client : 9000 ] PING testnet.ergo.chat 
//  [ server : 6667 ] :testnet.ergo.chat PONG testnet.ergo.chat testnet.ergo.chat 
//  [ client : 9000 ] QUIT :me fui 
//  [ server : 6667 ] :pepi!~u@2v9h9hjx6pxc6.oragono QUIT :Quit: me fui 
//  [ server : 6667 ] :pepi!~u@2v9h9hjx6pxc6.oragono QUIT :Quit: me fui 
//  [ server : 6667 ] ERROR :Quit: me fui 
//  [ client : 9000 ] QUIT :me fui 
//  [ server : 6667 ] :pepi!raul@127.0.0.1.hosted-by-42lausanne.ch QUIT :Quit: leaving
//  [ server : 6667 ] ERROR :Closing link: (raul@127.0.0.1.hosted-by-42lausanne.ch) [Quit: me fui] 
//  [ server : 6667 ] :pepinsa!~raul@freenode-7kj.edl.vrebei.IP QUIT :Quit: me fui 
//  [ server : 6667 ] ERROR :Closing link: (~raul@xcpe-62-167-164-111.cgn.res.adslplus.ch) [Quit: me fui] 

// 3.1.7 Quit

//       Command: QUIT
//    Parameters: [ <Quit Message> ]

//    A client session is terminated with a quit message.  The server
//    acknowledges this by sending an ERROR message to the client.

//    Numeric Replies:

//            None.

//    Example:

//    QUIT :Gone to have lunch        ; Preferred message format.

//    :syrk!kalt@millennium.stealth.net QUIT :Gone to have lunch ; User
//                                    syrk has quit IRC to have lunch.
// std::cout << FC(GREEN, "Iterador chName =") << (*it)->getName() << std::endl;
// std::cout << FC(GREEN, "Antes de hacer ++") << std::endl;
// PrintVectorPointer(_joinedChannels);
// std::cout << FC(GREEN, "Channel QUIT =") << ch_name << std::endl;
