#!/bin/bash

## ATENTION: Test requirements
#	For the test to work correctly, the following line in the pass.cpp file must be commented out
#		sendReply(3, ctime(_server->getStartTime()), "", "", "");

endline="\r\n"
LF="$'\n'"
# machine="c2r7s8"
machine="localhost"
ipServ=$( ping -c 1 $machine | grep "from" | awk '{print $4}' | sed 's/.$//')

# >>> TEST 1 <<<
# NICK, USER, PASS
input1="NICK Almodovar${endline}USER pedro pedro localhost :Pedro Almodovar${endline}PASS asd$endline"
expected_output1=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}")

# >>> TEST 2 <<<
# NICK, USER, PASS, JOIN #usa,
input2="${input1}JOIN #usa$endline"
expected_output2=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}")

# >>> TEST 3 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa,
input3="${input2}INVITE raul #usa$endline"
expected_output3=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}")

# >>> TEST 4 <<<
input4="${input3}PRIVMSG #usa :hola!!!$endline"
expected_output4=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}")

# >>> TEST 5 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!,
input5="${input4}PRIVMSG #usa :hola!!!$endline"
expected_output5=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}")

# >>> TEST 6 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby,
input6="${input5}MODE #usa +o baby$endline"
expected_output6=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}")

# >>> TEST 7 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul
input7="${input6}KICK raul$endline"
expected_output7=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}")

# >>> TEST 8 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas
input8="${input7}KICK #usa raul :no te quiero ver mas$endline"
expected_output8=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}")

# >>> TEST 9 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST,
input9="${input8}LIST$endline"
expected_output9=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}")

# >>> TEST 10 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG
input10="${input9}LIST #usa,#ARG$endline"
expected_output10=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}")

# >>> TEST 11 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON,
input11="${input10}TOPIC #ASPDJAPON$endline"
expected_output11=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}")

# >>> TEST 12 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON, TOPIC #usa,
input12="${input11}TOPIC #usa$endline"
expected_output12=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}\
:*.42irc.net 331 Almodovar #usa :No topic is set${endline}")

# >>> TEST 13 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON, TOPIC #usa, TOPIC #usa :born to be wild $endline,
input13="${input12}TOPIC #usa :born to be wild$endline"
expected_output13=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}\
:*.42irc.net 331 Almodovar #usa :No topic is set${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch TOPIC #usa :born to be wild${endline}")

# >>> TEST 14 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON, TOPIC #usa, TOPIC #usa :born to be wild $endline,
# TOPIC #usa,
input14="${input13}TOPIC #usa$endline"
expected_output14=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}\
:*.42irc.net 331 Almodovar #usa :No topic is set${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch TOPIC #usa :born to be wild${endline}\
:*.42irc.net 332 Almodovar #usa :born to be wild${endline}")

# >>> TEST 15 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON, TOPIC #usa, TOPIC #usa :born to be wild $endline,
# TOPIC #usa, MODE #usa -n, MODE #usa +n, MODE #usa +t
input15="${input14}MODE #usa -n${endline}MODE #usa +n${endline}MODE #usa +t$endline"
expected_output15=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}\
:*.42irc.net 331 Almodovar #usa :No topic is set${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch TOPIC #usa :born to be wild${endline}\
:*.42irc.net 332 Almodovar #usa :born to be wild${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa -n :${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa +n :${endline}")


# >>> TEST 99 <<<
# NICK, USER, PASS, JOIN #usa, INVITE raul #usa, PRIVMSG #usa :hola!!!, MODE #usa +o baby, KICK raul,
# KICK #usa raul :no te quiero ver mas, LIST, LIST #usa,#ARG, TOPIC #ASPDJAPON, TOPIC #usa, TOPIC #usa :born to be wild $endline,
# TOPIC #usa, MODE #usa -n, MODE #usa +n, MODE #usa +t, MODE #usa +i $endline, MODE #usa +l 1 $endline, MODE #usa +k asd $endline,
# NAMES #usa,ARG $endline, NOTICE #ASDSAD hola, NOTICE #usa :jsuis au toilet, PRIVMSG #usa :Quiero una hamburguesa $endline,
# PRIVMSG raul :Che raul deja esos pankakes!, WHOIS raul, WHOWAS raul, PART #usa, JOIN, QUIT :ME FUI
input99="${input15}MODE #usa +i${endline}MODE #usa +l 1${endline}MODE #usa +k asd ${endline}NAMES #usa,ARG ${endline}\
NOTICE #ASDSAD hola${endline}NOTICE #usa :jsuis au toilet${endline}PRIVMSG #usa :Quiero una hamburguesa${endline}\
PRIVMSG raul :Che raul deja esos pankakes!${endline}WHOIS raul${endline}WHOWAS raul${endline}PART #usa${endline}\
JOIN${endline}QUIT :ME FUI${endline}"
expected_output99=$(echo -e ":Almodovar!@ NICK Almodovar${endline}\
:*.42irc.net 001 Almodovar :Welcome to the Internet Relay Network Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch${endline}\
:*.42irc.net 002 Almodovar :Your host is *.42irc.net, running version 1.0${endline}\
:*.42irc.net 004 Almodovar :*.42irc.net 1.0 Channel modes +ntikl ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch JOIN #usa${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar #usa :End of NAMES list${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 401 Almodovar baby :No such nick${endline}\
:*.42irc.net 461 Almodovar KICK :Not enough parameters${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 322 Almodovar #usa 1 :[+nt] ${endline}\
:*.42irc.net 323 Almodovar :End of LIST${endline}\
:*.42irc.net 403 Almodovar #ASPDJAPON :No such channel${endline}\
:*.42irc.net 331 Almodovar #usa :No topic is set${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch TOPIC #usa :born to be wild${endline}\
:*.42irc.net 332 Almodovar #usa :born to be wild${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa -n :${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa +n :${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa +i :${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa +l :1 ${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch MODE #usa +k :asd ${endline}\
:*.42irc.net 353 Almodovar = #usa :@Almodovar ${endline}\
:*.42irc.net 366 Almodovar  :End of NAMES list${endline}\
:*.42irc.net 411 Almodovar :No recipient given (PRIVMSG)${endline}\
:*.42irc.net 401 Almodovar raul :No such nick${endline}\
:*.42irc.net 318 Almodovar raul :End of /WHOIS list.${endline}\
:*.42irc.net 406 Almodovar raul :There was no such nickname${endline}\
:*.42irc.net 369 Almodovar raul :End of WHOWAS${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch PART #usa :hasta la vista Baby${endline}\
:*.42irc.net 461 Almodovar JOIN :Not enough parameters${endline}\
:Almodovar!pedro@${ipServ}.hosted-by-42lausanne.ch QUIT :Quit: ME FUI${endline}")

inputs=("$input1" "$input2" "$input3" "$input4" "$input5"
		"$input6" "$input7" "$input8" "$input9" "$input10"
		"$input11" "$input12" "$input13" "$input14" "$input15"
		"$input99")

expected_outputs=("$expected_output1" "$expected_output2" "$expected_output3"
				"$expected_output4" "$expected_output5" "$expected_output6" "$expected_output7"
				"$expected_output8" "$expected_output9" "$expected_output10" "$expected_output11"
				"$expected_output12" "$expected_output13" "$expected_output14" "$expected_output15"
				"$expected_output99")

for i in "${!inputs[@]}"
do
    input="${inputs[$i]}"
    expected_output="${expected_outputs[$i]}"

	echo -ne "\033[1;37mSTART TEST $((i+1))\033[0m\n"

    output=$(echo -ne "$input" | nc -c ${ipServ} 6667)

	#####		UNCOMMENT TO ADD NEW TESTS		#####
	printf "\n"
	printf "    EXPECTED output: %s" "${expected_output}" | cat -e
	printf "\n"
	printf "\n"
	printf "    REAL output: %s" "${output}" | cat -e
	printf "\n"

    if [[ "$output" == "$expected_output" ]]; then
        # echo -ne "${input}"
		echo -e "\033[1;32mTEST $((i+1)): OK\033[0m\n"
    else
        # echo -ne "${input}"
        echo -e "\033[1;31mKO\033[0m"
		printf "\n"

    fi
done

	# "JOIN #usa $endline" ,\
	# "INVITE raul #usa $endline" ,\
	# "PRIVMSG #usa :hola!!! $endline" ,\
	# "MODE #usa +o baby $endline" ,\
	# "KICK raul $endline" ,\
	# "KICK #usa raul :no te quiero ver mas $endline" ,\
	# "LIST $endline" ,\
	# "LIST #usa,#ARG $endline" ,\
	# "TOPIC #ASPDJAPON $endline" ,\
	# "TOPIC #usa $endline" ,\
	# "TOPIC #usa :born to be wild $endline" ,\
	# "TOPIC #usa $endline" ,\
	# "MODE #usa -n  $endline" ,\
	# "MODE #usa +n  $endline" ,\
	# "MODE #usa +t  $endline" ,\
	# "TOPIC #usa" ,\
	# "MODE #usa +i $endline" ,\
	# "MODE #usa +l 1 $endline" ,\
	# "MODE #usa +k asd $endline" ,\
	# "NAMES #usa,ARG $endline" ,\
	# "NOTICE #ASDSAD hola $endline" ,\
	# "NOTICE #usa :jsuis au toilet $endline" ,\
	# "PRIVMSG #usa :Quiero una hamburguesa $endline" ,\
	# "PRIVMSG raul :Che raul deja esos pankakes! $endline" ,\
	# "WHOIS raul $endline" ,\
	# "WHOWAS raul $endline" ,\
	# "PART #usa $endline" ,\
	# "JOIN $endline" ,\
	# "QUIT :ME FUI $endline"
