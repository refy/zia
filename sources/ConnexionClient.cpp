#include	"ConnexionClient.hpp"


ConnexionClient::ConnexionClient(const sockaddr_in &sin, SOCKET s)
{
	this->_sock = s;

	// IP du client
	this->_ip = std::string(inet_ntoa(sin.sin_addr));
			
	// Port du client
	this->_port = sin.sin_port;
			
	// Hostname du serveur
	struct hostent *hp;
	struct in_addr ip;
	if (!inet_aton(this->_ip.c_str(), &ip))
		if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) != 0)
			this->_hostname = std::string(hp->h_name);
}

ConnexionClient::~ConnexionClient()
{
	if (this->_sock >= 0)
		close(this->_sock);
	this->_sock = -1;
}

bool ConnexionClient::isOK() const
{
	if (this->_sock < 0)
		return (false);
	return (true);
}

std::string const &ConnexionClient::getHostname() const
{
	return (this->_hostname);
}

std::string const &ConnexionClient::getIp() const
{
	return (this->_ip);
}

int ConnexionClient::getPort() const
{
	return (this->_port);
}

std::string const &ConnexionClient::getRequest() const
{
	return (this->_request);
}

void ConnexionClient::setRequest(std::string const &r)
{
	this->_request = r;
}

void ConnexionClient::setSocket(SOCKET s)
{
	this->_sock = s;
}

SOCKET ConnexionClient::getSocket()
{
	return (this->_sock);
}



