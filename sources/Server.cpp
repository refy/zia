#include	<sstream>
#include	<vector>

#include	"AModule.hpp"
#include	"Server.hpp"
#include	"ConnexionClient.hpp"
#include	"ConnexionAttente.hpp"

Server::Server(apimeal::ILogger *log, ConfParser *p, apimeal::Error & e)
  : _log(log)
{
  if (p)
    {
      this->_loader.LoadModules(p->getModulesPath(), e, log);
      this->_coWait = new ConnexionAttente(p->getPort());
    }
}

Server::~Server()
{}

bool	Server::checkError()
{
  if (this->_err.IsError)
    {
      this->_log->LogInfo(this->_err.Message);
      this->_err.Message.clear();
      this->_err.IsError = false;
      return true;
    }
  return false;
}

#include <iostream>

apimeal::IConnexion*	Server::accept_client()
{
  sockaddr_in	sin_tmp;
  SOCKET		s_tmp;
  socklen_t	sin_size;

  if (!this->_coWait->getSocket() < 0)
    return (0);
  sin_size = sizeof(sin_tmp);
  if ((s_tmp = accept(this->_coWait->getSocket(), (sockaddr *)&sin_tmp, &sin_size)) < 0)
    return (0);
  apimeal::IConnexion *ptr = new ConnexionClient(sin_tmp, s_tmp);
  if (ptr == 0)
    return (0);
  return (ptr);  
}

void	Server::run()
{
  apimeal::AModule	*bl = this->_loader.getModule("PreConnexion-Blacklist", this->_err);

  if (!this->checkError())
    {
      this->checkError();
      if (this->_coWait->getSocket() < 0)
	this->_log->LogError("Cannot create the waiting socket.");
      else
	{
	  int			p = this->_coWait->getPort();
	  std::stringstream	buffer;;
	  std::string		tmppo;

	  buffer << p;
	  buffer >> tmppo;

	  std::string	ip = "IP: " + this->_coWait->getIp();
	  std::string	port = "Port: " + tmppo;
	  std::string	host = "Hostname: " + this->_coWait->getHostname();

	  this->_log->LogDebug("Serveur Information: ");
	  this->_log->LogDebug(ip);
	  this->_log->LogDebug(port);
	  this->_log->LogDebug(host);

	  apimeal::IConnexion	*ptr;

	  while ((ptr = this->accept_client()) != 0)
	    {
	      int			p = ptr->getPort();
	      std::stringstream		buffer;;
	      std::string		tmppo;

	      buffer << p;
	      buffer >> tmppo;

	      std::string	ip = "IP: " + ptr->getIp();
	      std::string	port = "Port: " + tmppo;
	      std::string	host = "Hostname: " + ptr->getHostname();

	      this->_log->LogDebug("Connexion Information: ");
	      this->_log->LogDebug(ip);
	      this->_log->LogDebug(port);
	      this->_log->LogDebug(host);

	      bl->preConnexion(ptr, this->_err);
	      this->checkError();
	      delete ptr;
	    }
	}
    }
}
