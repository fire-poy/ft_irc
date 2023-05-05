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

#define PORT 8000
// #define PORT 6667
#define N_LINES 35

int main()
{
	sleep(10);
	int sockfd, numbytes;
	struct sockaddr_in servaddr;
	// char buff[TEST_MESSAGE_LENGTH] = TEST_MESSAGE;
	std::string testCmd[N_LINES] = {
		"USER juan juan localhost :juanRamon\r\n" ,\
		"NICK pepito\r\n" ,\
		"PASS asd\r\n" ,\
		"JOIN #usa\r\n" ,\
		"INVITE raul #usa\r\n" ,\
		"PRIVMSG #usa :hola!!!\r\n" ,\
		"PRIVMSG #usa :Como te llamas?\r\n" ,\
		"PRIVMSG #usa :encantado!!!\r\n" ,\
		"MODE #usa +o baby\r\n" ,\
		"KICK raul\r\n" ,\
		"KICK juanC\r\n" ,\
		"KICK #usa raul :no te quiero ver mas\r\n" ,\
		"LIST\r\n" ,\
		"LIST #usa,#ARG\r\n" ,\
		"TOPIC #ASPDJAPON\r\n" ,\
		"TOPIC #usa\r\n" ,\
		"TOPIC #usa :born to be wild\r\n" ,\
		"TOPIC #usa\r\n" ,\
		"MODE #usa -n \r\n" ,\
		"MODE #usa +n \r\n" ,\
		"MODE #usa +t \r\n" ,\
		"TOPIC #usa" ,\
		"MODE #usa +i\r\n" ,\
		"MODE #usa +l 1\r\n" ,\
		"MODE #usa +k asd\r\n" ,\
		"NAMES #usa,ARG\r\n" ,\
		"NOTICE #ASDSAD hola\r\n" ,\
		"NOTICE #usa :jsuis au toilet\r\n" ,\
		"PRIVMSG #usa :Quiero una hamburguesa\r\n" ,\
		"PRIVMSG raul :Che raul deja esos pankakes!\r\n" ,\
		"WHOIS raul\r\n" ,\
		"WHOWAS raul\r\n" ,\
		"PART #usa\r\n" ,\
		"JOIN\r\n" ,\
		"QUIT :ME FUI\r\n"
		};

	int i = 0;

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

	while (i != N_LINES)
	{
		// if (send(getSocket(), msg.c_str(), msg.length(), 0) < 0)
		if ((numbytes = send(sockfd, testCmd[i % N_LINES].c_str(), testCmd[i % N_LINES].length(), 0)) < 0) {
			perror("send");
			exit(1);
		}

		std::cout << "string length = " << (int)(testCmd[i % N_LINES].length()) << std::endl;
		if (numbytes != (int)(testCmd[i % N_LINES].length()))
			std::cout << "numbytes sended = " << numbytes << "the test message has been partially sent" << std::endl;
		else
			std::cout << "the message has been completely sent" << std::endl;
		// sleep (2);
		sleep (1);
		i++;
	}
	sleep (2);
	close(sockfd);

	return 0;
}
