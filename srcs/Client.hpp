#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Includes.hpp"

class Server;
class Channel;

typedef struct s_nicksBackup {
	std::string	nick;
	std::string	server;
	std::string	serverInfo;
	std::string	user;
	std::string	host;
	std::string	realname;
	const time_t	*serverStartTime;
}	nicksBackup;

typedef struct s_isFullyRegistered {
	bool passHasBeenExecuted;
	bool nickHasBeenExecuted;
	bool userHasBeenExecuted;
}	isFullyRegistered;

class Client
{
	public:

		Client(Server *server);
		Client(Client &other);
		Client &operator=(Client &other);
		~Client();

		// SETTERS
		void				setId(int id);
		void				setNickname(std::string nickname);
		void				setUsername(std::string username);
		void				setHostname(std::string hostname);
		void				setLastCommunication(std::time_t lastCommunication);
		void				setSocket(int socket);
		void				setAddress(struct sockaddr_in address);
		void				setBuf(std::string buf);
		void				setIp(std::string ip);
		void				setIsPingSent( bool isPingSentStatus);

		// GETTERS
		int					getMaxId() const ;
		int					getId() const;
		std::string			getNickname() const;
		std::string			getUsername() const;
		std::string			getHostname() const;
		std::string			getRealname() const;
		int					getSocket() const;
		struct sockaddr_in	getAddress() const;
		std::string			getIp() const;
		double				getIdle() const;
		int					getPass() const;
		bool				isQuiting();
		bool				getIsPingSent() const;

		// PARSING
		std::string			getBuf() const;
		void				execCmd(Message *m);
		void				process_buffer(const std::string& message);

		// REPLY
		std::string			numericReply(const int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);
		std::string			formatMsgsReply(const int code);
		void				sendReply(const int code, std::string arg1, std::string arg2, std::string arg3, std::string arg4);

		//MSG
		std::string			formatMsgsUsers();
		void				sendMsg(std::string msg);
		void				sendMsgClient(std::string msg, Client *target);
		void				sendMsgChannel(std::string msg, Channel *target);
		void				sendMsgJoinedChannels(std::string msg);
		void				sendMsgSharedUsers(std::string msg) ;


		// JOINED CHANNELS
		void				addJoinedChannel(Channel *ch);
		void				removeJoinedChannel(Channel *ch);

		// CMDS
		void				nick(Message *m);
		void				user(Message *m);
		void				pass(Message *m);
		void				join(Message *m);
		void				quit(Message *m);
		void				list(Message *m);
		void				names(Message *m);
		void				part(Message *m);
		void				privmsg(Message *m);
		void				ping(Message *m);
		void				kick(Message *m);
		void				notice(Message *m);
		void				mode(Message *m);
		void				pong(Message *m);
		void				whois(Message *m);
		void				whowas(Message *m);
		void				topic(Message *m);
		void				invite(Message *m);

		// CMDS TOOLS
		void				addToNicksHistory();
		void				welcome();
		void				leaveAll();
		void				channelModes(Message *m);
		void				userModes(Message *m);
		void				addCommandToRegister(std::string &command);

		// TOOLS
		std::vector<std::string>	subSplitString(const std::string& str, char c);

	private:

		int								_id;
		std::string 					_nickname;
		std::string 					_username;
		std::string 					_hostname;
		std::string						_ip;
		std::string 					_realname;
		bool							_isRegistered;
		time_t							_lastCommunication;
		int 							_socket;
		struct sockaddr_in				_address;
		std::string						_buf;
		static int						_maxId;
		Server							*_server;
		static std::vector<nicksBackup>	_nicksHistory;
		bool							_alreadyWelcomed;
		bool							_quiting;
		std::vector<Channel *>			_joinedChannels;
		int								_pass;
		isFullyRegistered				_register;
		bool							_isPingSent;
};

std::ostream	&operator<<( std::ostream & o, Client const & rhs );

#endif
