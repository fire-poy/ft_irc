#include "../srcs/Includes.hpp"

// made by: mpons
// modified by: olmartin

void			Client::ping(Message *m)
{
	std::cout << FC(GREEN, ">\tping function executed ") <<"by client id: " << _id << "\t\t<" << std::endl;
	bool pongSend = false;
		if (m->params.empty())
		return (sendReply(409, "", "", "", ""));
	size_t nbParam = (m->params.size() > 1 ? 2 : 1);
	for (size_t i = 0; i < nbParam; ++i)
	{
		if (m->params[i].compare(_server->getName()) == 0)
		{
			if (!pongSend)
			{
				std::string to_send =  "PONG " + m->params[0] +  " :" + m->params[0] + END_CHARACTERS;
				sendMsg(to_send);
				pongSend = true;
			}
		}
		else
			sendReply(402, m->params[i], "", "", "");
	}
}

// 4.6.2 Ping message   			RFC 1459

//       Command: PING
//    Parameters: <server1> [<server2>]

//    The PING message is used to test the presence of an active client at
//    the other end of the connection.  A PING message is sent at regular
//    intervals if no other activity detected coming from a connection.  If
//    a connection fails to respond to a PING command within a set amount
//    of time, that connection is closed.

//    Any client which receives a PING message must respond to <server1>
//    (server which sent the PING message out) as quickly as possible with
//    an appropriate PONG message to indicate it is still there and alive.
//    Servers should not respond to PING commands but rely on PINGs from
//    the other end of the connection to indicate the connection is alive.
//    If the <server2> parameter is specified, the PING message gets
//    forwarded there.

//    Numeric Replies:

//            ERR_NOORIGIN                    ERR_NOSUCHSERVER

//    Examples:

//    PING tolsun.oulu.fi             ; server sending a PING message to
//                                    another server to indicate it is still
//                                    alive.

//    PING WiZ                        ; PING message being sent to nick WiZ

//*******************************************************************
// 3.7.2 Ping message				RFC 2812

//       Command: PING
//    Parameters: <server1> [ <server2> ]

//    The PING command is used to test the presence of an active client or
//    server at the other end of the connection.  Servers send a PING
//    message at regular intervals if no other activity detected coming
//    from a connection.  If a connection fails to respond to a PING
//    message within a set amount of time, that connection is closed.  A
//    PING message MAY be sent even if the connection is active.

//    When a PING message is received, the appropriate PONG message MUST be
//    sent as reply to <server1> (server which sent the PING message out)
//    as soon as possible.  If the <server2> parameter is specified, it
//    represents the target of the ping, and the message gets forwarded
//    there.

//    Numeric Replies:

//            ERR_NOORIGIN                  ERR_NOSUCHSERVER

//    Examples:

//    PING tolsun.oulu.fi             ; Command to send a PING message to
//                                    server

//    PING WiZ tolsun.oulu.fi         ; Command from WiZ to send a PING
//                                    message to server "tolsun.oulu.fi"

//    PING :irc.funet.fi              ; Ping message sent by server
//                                    "irc.funet.fi"
// ******************************************
	// NUMERIC REPLAY
// 409     ERR_NOORIGIN
//                         ":No origin specified"

//                 - PING or PONG message missing the originator parameter
//                   which is required since these commands must work
//                   without valid prefixes.
