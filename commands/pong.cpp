#include "../srcs/Includes.hpp"

void			Client::pong(Message *m){
	if (m->params.size() < 1)
		return (sendReply(461, m->command, "", "", ""));
	std::cout << FC(GREEN, ">\tpong function executed ") <<"by client id: " << _id << "\t\t<" << std::endl << std::endl;
}

// 4.6.3 Pong message				RFC 1459

//       Command: PONG
//    Parameters: <daemon> [<daemon2>]

//    PONG message is a reply to ping message.  If parameter <daemon2> is
//    given this message must be forwarded to given daemon.  The <daemon>
//    parameter is the name of the daemon who has responded to PING message
//    and generated this message.

//    Numeric Replies:

//            ERR_NOORIGIN                    ERR_NOSUCHSERVER

//    Examples:

//    PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to tolsun.oulu.fi


//*******************************************************************
// 3.7.3 Pong message					RFC 2812

//       Command: PONG
//    Parameters: <server> [ <server2> ]

//    PONG message is a reply to ping message.  If parameter <server2> is
//    given, this message MUST be forwarded to given target.  The <server>
//    parameter is the name of the entity who has responded to PING message
//    and generated this message.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Example:

//    PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
//                                    tolsun.oulu.fi
