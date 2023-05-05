#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Includes.hpp"

class Client;

class Channel
{
	private:

		std::string	_name;
		std::string _topic;
		std::string _modes;
		std::string _key;
	    std::vector<Client*> _members;
		std::vector<Client*> _invited;
	    std::vector<Client*> _operators;
	    size_t _userLimit;

	public:

		Channel(Client &owner, std::string name);
		Channel(Channel &other);
		Channel &operator=(Channel &other);
		~Channel();

  		std::string				getName() const;
		std::string				getMembersNicks();
		std::vector<Client*>	getMembers() const;
		void	addClient(Client *client);
		void	removeClient(Client *client);
		bool	hasClient(Client *client) const;
		bool	isEmpty() const;
		bool	isOperator(Client *client) const;
		void	addOperator(Client* client);
		void	removeOperator(Client* client);
		void	setUserLimit(std::string set);
		size_t	getUserLimit() const;
		void	setChannelKey(std::string key);
		bool	isValidKey(std::string key) const;

		std::string	getTopic() const;
		void		setTopic(std::string topic);
		
		bool		hasMode(char mode) const;
		std::string	getModes() const;
		char		setMode(char mode);
		char		unsetMode(char mode);

		bool		isInvited(Client *client) const;
		void		addInvited(Client* client);
};

std::ostream		&operator<<(std::ostream & o, Channel const & rhs );

#endif

