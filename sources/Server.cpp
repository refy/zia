#include	"AModule.hpp"
#include	"Server.hpp"

Server::Server(apimeal::ILogger *log, ConfParser *p, apimeal::Error & e)
  : _log(log)
{
  if (p)
    this->_loader.LoadModules(p->getModulesPath(), e, log);
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
  apimeal::AModule	*connexion = this->_loader.getModule("Connexion", this->_err);
  apimeal::AModule	*parse = this->_loader.getModule("ParseRequest", this->_err);
  apimeal::AModule	*content = this->_loader.getModule("GetContent", this->_err);
  apimeal::AModule	*genres = this->_loader.getModule("GenRes", this->_err);
  apimeal::AModule	*send = this->_loader.getModule("SendRes", this->_err);

  if (!this->checkError())
    {
      connexion->preConnexion(NULL, this->_err);
      connexion->postConnexion(NULL, this->_err);
      parse->preParseRequest(NULL, this->_err);
      parse->postParseRequest(NULL, this->_err);
      content->contentModule(NULL, this->_err);
      genres->CGIModule(NULL, this->_err);
      genres->postGenerateResponse(NULL, this->_err);
      send->preSendRequest(NULL, this->_err);
      this->checkError();
    }
}
