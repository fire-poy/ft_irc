# include "Channel.hpp"

//	  i - invite-only channel flag;
//    t - topic settable by channel operator only flag;
//    n - no messages to channel from clients on the outside;
Channel::Channel(Client &owner, std::string name) :
_name(name), _modes("+nt")
{
	_operators.push_back(&owner); 
}

Channel::Channel(Channel &other){ *this = other;}

Channel &Channel::operator=(Channel &other){
	(void) other;
	return (*this);
}

Channel::~Channel(){}

std::string	Channel::getName() const
{
	return _name;
}

//Clients
std::vector<Client*> Channel::getMembers() const {
	return _members;
}

std::string	Channel::getMembersNicks()
{ 
	std::string all_nicks;
	for (std::vector<Client *>::iterator it = _members.begin(); it != _members.end(); ++it)
	{
		if (isOperator(*it))
			all_nicks += "@";
		all_nicks += (*it)->getNickname() + " ";
	}
	return all_nicks;
}

void Channel::addClient(Client* client) {
	_members.push_back(client);
}

void Channel::removeClient(Client* client) {
	for (std::vector<Client*>::iterator it = _members.begin(); it != _members.end(); ++it) {
		if ((*it)->getNickname() == client->getNickname()) {
			_members.erase(it);
			if (isOperator(client))
				removeOperator(client);
			return;
		}
	}
}

bool	Channel::hasClient(Client* client) const {
	std::string client_nick = client->getNickname();
	std::vector<Client*>::const_iterator it = _members.begin();
	for ( ; it != _members.end(); ++it) {
		if ((*it)->getNickname() == client_nick) {
			return true;
		}
	}
	return false;
}

bool	Channel::isEmpty() const{
	if (_members.empty())
		return true;
	return false;
}

bool	Channel::isOperator(Client *client) const
{
	for (std::vector<Client*>::const_iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		std::cout << *(*it) << std::endl; 
		if ((*it)->getId() == client->getId() &&\
		(*it)->getUsername() == client->getUsername() &&\
		(*it)->getHostname() == client->getHostname())
			return true;
	}
	return false;
}

void	Channel::addOperator(Client* client)
{
	_operators.push_back(client);
}

void	Channel::removeOperator(Client* client) {
	for (std::vector<Client*>::iterator it = _operators.begin(); it != _operators.end(); ++it) {
		if ((*it)->getNickname() == client->getNickname()) {
			_operators.erase(it);
			return;
		}
	}
}

//TOPIC
void	Channel::setTopic(std::string topic) {
	this->_topic = topic;
}
std::string	Channel::getTopic() const {
	return _topic;
}

std::string	Channel::getModes() const
{
	return _modes;
}

char	Channel::setMode(char mode)
{
	if (hasMode(mode))
		return 0;
	else
		_modes.push_back(mode);
	return mode;
}

char	Channel::unsetMode(char mode)
{
	if (hasMode(mode))
	{
	    _modes.erase(_modes.find(mode), 1);
		return mode;
	}
	else
		return 0; 
}

bool	Channel::hasMode(char mode) const
{
	if (_modes.find(mode) == std::string::npos)//no encontramos el char
		return (false);
	return (true);
}

void	Channel::setUserLimit(std::string set)
{
	_userLimit = toSizeType(set);
}

size_t	Channel::getUserLimit() const
{
	return _userLimit;
}

void	Channel::setChannelKey(std::string key)
{
	_key = key;
}

bool	Channel::isValidKey(std::string key) const
{ 
	std::cout << "try key == " << key << std::endl; 
	std::cout << "Good key == "<< _key << std::endl; 
	if (_key.compare(key) == 0)
		return true;
	return false;
}

bool	Channel::isInvited(Client *client) const
{
	for (std::vector<Client*>::const_iterator it = _invited.begin(); it != _invited.end(); ++it)
	{
		std::cout << *(*it) << std::endl; 
		if ((*it)->getId() == client->getId() &&\
		(*it)->getUsername() == client->getUsername() &&\
		(*it)->getHostname() == client->getHostname())
			return true;
	}
	return false;
}

void Channel::addInvited(Client* client) {
	_invited.push_back(client);
}

std::ostream	&operator<<(std::ostream & o, Channel const & rhs )
{
	o << FC(GREEN, "******\tChannel info\t******") << std::endl;
	o << "Name: " << rhs.getName() << std::endl;
	o << "Modes: " << rhs.getModes() << std::endl;
	if (!rhs.getTopic().empty())
		o << "Topic: " << rhs.getTopic() << std::endl;
	return o;
}
