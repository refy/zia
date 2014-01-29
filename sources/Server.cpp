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

void	Server::run()
{
  apimeal::AModule	*bl = this->_loader.getModule("PreConnexion-Blacklist", this->_err);
  apimeal::AModule	*co_ssl = this->_loader.getModule("PostConnexion-SSL", this->_err);

  if (!this->checkError())
    {
      bl->preConnexion(NULL, this->_err);
      // co_ssl->postConnexion(NULL, this->_err);
      this->checkError();
    }

  // if (this->_coWait->isOK() == false)
  //   this->_log->LogError("Cannot create the waiting socket.");
  else
    {
      std::string	ip = "IP: " + this->_coWait->getIp();
      std::string	port = "Port: " + this->_coWait->getPort();
      std::string	host = "Hostname: " + this->_coWait->getHostname();

      this->_log->LogDebug("Serveur Information");
      this->_log->LogDebug(ip);
      this->_log->LogDebug(port);
      this->_log->LogDebug(host);
    }
}
