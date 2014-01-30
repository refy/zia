#include	"ConnexionAttente.hpp"

ConnexionAttente::ConnexionAttente(int port, int nbs_attente)
{
	this->_sin.sin_addr.s_addr  = htonl(INADDR_ANY);
	this->_sin.sin_family       = AF_INET;
	this->_sin.sin_port         = htons(port);

	if ((this->_sock = socket(AF_INET, SOCK_STREAM, 0)) >= 0)
	{
		int yes = 1;
		if (setsockopt(this->_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
		{
			close(this->_sock);
			this->_sock = -1;
		}
		if (bind(this->_sock, (sockaddr *)&this->_sin, sizeof(this->_sin)) < 0)
		{
			close(this->_sock);
			this->_sock = -1;
		}
    		else if (listen(this->_sock, nbs_attente) < 0)
		{
			close(this->_sock);
			this->_sock = -1;
		}
		else
		{
			// IP du serveur
			this->_ip = std::string(inet_ntoa(this->_sin.sin_addr));
			
			// Port du serveur
			this->_port = port;
			
			// Hostname du serveur
			struct hostent *hp;
			struct in_addr ip;
			if (!inet_aton(this->_ip.c_str(), &ip))
				if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) != 0)
					this->_hostname = std::string(hp->h_name);
		}
	}
}

ConnexionAttente::~ConnexionAttente()
{
	if (this->_sock >= 0)
		close(this->_sock);
	this->_sock = -1;
}

std::string const &ConnexionAttente::getHostname() const
{
	return (this->_hostname);
}

std::string const &ConnexionAttente::getIp() const
{
	return (this->_ip);
}

int ConnexionAttente::getPort() const
{
	return (this->_port);
}

std::string const &ConnexionAttente::getRequest() const
{
	return (this->_request);
}

void ConnexionAttente::setRequest(std::string const &request)
{
	this->_request = request;
}

void ConnexionAttente::setSocket(SOCKET s)
{
	this->_sock = s;
}

SOCKET ConnexionAttente::getSocket()
{
	return (this->_sock);
}
