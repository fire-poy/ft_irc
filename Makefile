# CXX = c++
CXX = clang++
# CXX = g++-12

NAME = ircserv

SRCS =	./srcs/main.cpp\
		./srcs/Server.cpp\
		./srcs/Channel.cpp\
		./srcs/Client.cpp\
		./srcs/parsing.cpp\
		./srcs/NumericReply.cpp\
		./srcs/Utils.cpp\
		./commands/join.cpp\
		./commands/kick.cpp\
		./commands/list.cpp\
		./commands/names.cpp\
		./commands/mode.cpp\
		./commands/nick.cpp\
		./commands/notice.cpp\
		./commands/part.cpp\
		./commands/pass.cpp\
		./commands/ping.cpp\
		./commands/pong.cpp\
		./commands/privmsg.cpp\
		./commands/quit.cpp\
		./commands/user.cpp\
		./commands/whois.cpp\
		./commands/whowas.cpp\
		./commands/topic.cpp\
		./commands/invite.cpp\

SRCS_T =./test/clientTest1.cpp\
		./test/clientTest2.cpp\

CFLAGS = -Werror -Wextra -Wall -std=c++98 -pedantic
CFLAGS += -Wfatal-errors 
# CFLAGS += -g
# CFLAGS += -fsanitize=address

OBJ = $(SRCS:.cpp=.o)
OBJ_T = $(SRCS_T:.cpp=.o)

TEST_CLIENT_1 = test1
TEST_CLIENT_2 = test2
TEST_CLIENT_3 = test3

.cpp.o:
	$(CXX) $(CFLAGS) -c $^ -o $@


$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(NAME)

$(TEST_CLIENT_1): $(OBJ_T)
	$(CXX) $(CFLAGS) ./test/clientTest1.cpp -o $(TEST_CLIENT_1)

$(TEST_CLIENT_2): $(OBJ_T)
	$(CXX) $(CFLAGS) ./test/clientTest2.cpp -o $(TEST_CLIENT_2)

$(TEST_CLIENT_3): $(OBJ_T)
	$(CXX) $(CFLAGS) ./test/clientTest3.cpp -o $(TEST_CLIENT_3)

all: $(NAME) $(TEST_CLIENT_1) $(TEST_CLIENT_2) $(TEST_CLIENT_3)

debug:
	lldb ./ircserv 6667 asd

run: all
	./ircserv 6667 asd

test: all
	./test1 &
	sleep 0.5
	./test2 &
	sleep 0.5
	./test3 &
	./ircserv 6667 asd


rclean: 
	/bin/rm -f $(TEST_CLIENT_3)

t: rclean $(TEST_CLIENT_3)
	./test3 &
	./ircserv 6667 asd

val: all
	valgrind ./ircserv 6667 asd

leak: all
	valgrind --leak-check=full --show-leak-kinds=all ./ircserv 6667 asd

tleak: all
	./test1 &
	sleep 0.5
	./test2 &
	sleep 0.5
	./test3 &
	valgrind --leak-check=full --show-leak-kinds=all ./ircserv 6667 asd

proxy: all
	python3 ./proxy/proxy.py

proxyfree: all
	python3 ./proxyfree/proxy.py


clean:
	/bin/rm -f $(OBJ)
	/bin/rm -f $(OBJ_T)

fclean: clean
	/bin/rm -f $(NAME)
	/bin/rm -f $(TEST_CLIENT_1)
	/bin/rm -f $(TEST_CLIENT_2)
	/bin/rm -f $(TEST_CLIENT_3)

re: fclean all test

.PHONY: all clean fclean re
