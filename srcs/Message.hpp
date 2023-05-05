#ifndef MESSAGE_HPP
# define MESSAGE_HPP

class Client;
class Server;

typedef struct s_message {
    std::string prefix;
    std::string command;
    std::vector<std::string> params;
}	Message;

Message		parseMessage(std::string input);
void		print_message(const Message& msg);
void		printAscii(const std::string& str);

#endif
