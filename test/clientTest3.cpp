#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include "../srcs/Includes.hpp"
#include <vector>

#define PORT 8000
// #define PORT 6667

int main()
{
	sleep(4);
	int sockfd, numbytes;
	struct sockaddr_in servaddr;

	std::vector<std::string> msg;
	msg.reserve(60);
	// msg.push_back("USER juan juan localhost :juanRamon");
	// msg.push_back("NICK pepito");
	// msg.push_back("PASS asd");
	// msg.push_back("JOIN #usa");
	// msg.push_back("INVITE raul #usa");
	// msg.push_back("PRIVMSG #usa :hola!!!");
	// msg.push_back("PRIVMSG #usa :Como te llamas?");
	// msg.push_back("PRIVMSG #usa :encantado!!!");
	// msg.push_back("MODE #usa +o baby");
	// msg.push_back("KICK raul");
	// msg.push_back("KICK juanC");
	// msg.push_back("KICK #usa raul :no te quiero ver mas");
	// msg.push_back("LIST");
	// msg.push_back("LIST #usa,#ARG");
	// msg.push_back("TOPIC #ASPDJAPON");
	// msg.push_back("TOPIC #usa");
	// msg.push_back("TOPIC #usa :born to be wild");
	// msg.push_back("TOPIC #usa");
	// msg.push_back("MODE #usa -n ");
	// msg.push_back("MODE #usa +n ");
	// msg.push_back("MODE #usa +t ");
	// msg.push_back("TOPIC #usa ");
	// msg.push_back("MODE #usa +i");
	// msg.push_back("MODE #usa +l 1");
	// msg.push_back("MODE #usa +k asd");
	// msg.push_back("NAMES #usa,ARG");
	// msg.push_back("NOTICE #ASDSAD hola");
	// msg.push_back("NOTICE #usa :jsuis au toilet");
	// msg.push_back("PRIVMSG #usa :Quiero una hamburguesa");
	// msg.push_back("PRIVMSG raul :Che raul deja esos pankakes!");
	// msg.push_back("WHOIS raul");
	// msg.push_back("WHOWAS raul");
	// msg.push_back("PART #usa");
	// msg.push_back("JOIN");
	// msg.push_back("QUIT :ME FUI");
	msg.push_back("USER Pierre Lapointe localhost :Piedra lapunta");
	msg.push_back("NICK JamesBond");
	msg.push_back("PASS asd");
	msg.push_back("JOIN #japon");
	msg.push_back("INVITE");
	msg.push_back("PRIVMSG");
	msg.push_back("MODE");
	msg.push_back("KICK");
	msg.push_back("LIST");
	msg.push_back("TOPIC");
	msg.push_back("MODE");
	msg.push_back("MODE #japon +i");
	msg.push_back("MODE #japon +l");
	msg.push_back("MODE #japon +k");
	msg.push_back("MODE #japon +o");
	msg.push_back("MODE #japon +t");
	msg.push_back("MODE #japon +n");
	msg.push_back("NAMES");
	msg.push_back("NOTICE");
	msg.push_back("PRIVMSG");
	msg.push_back("WHOIS");
	msg.push_back("WHOWAS");
	msg.push_back("PART");
	msg.push_back("JOIN");
	msg.push_back("QUIT");
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
	servaddr.sin_family = AF_INET;      /* host byte order */
	servaddr.sin_port = htons(PORT);    /* short, network byte order */
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	bzero(&(servaddr.sin_zero), 8);     /* zero pour le reste de struct */

	if (connect(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
		perror("connect");
		exit(1);
	}
	std::vector<std::string>::iterator it = msg.begin();
	for ( ; it != msg.end(); ++it)
	{
		int i = 0;
		for ( ; i != 6; ++i)
		{
			if (i != 0)
			{
				it->erase(it->length() - 2);
				if (i % 2)
					it->append(" #usa,#arg");
				else
					it->append(" raul");
			}
			it->append(END_CHARACTERS);
			if ((numbytes = send(sockfd, it->c_str(), it->length(), 0)) < 0) {
				perror("send");
				exit(1);
			}
			usleep(100000);
		}
		sleep (1);
	}
	sleep (2);
	close(sockfd);
	return 0;
}
