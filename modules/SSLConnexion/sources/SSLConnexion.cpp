#include	"AModule.hpp"
#include	"SSLConnexion.hpp"

SSLConnexion::SSLConnexion(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("SSLConnexion")
{}

SSLConnexion::~SSLConnexion()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	SSLConnexion::getPriority() const
{}

const apimeal::Version &		SSLConnexion::getVersion() const
{
  return (this->_version);
}

const std::string &			SSLConnexion::getName() const
{
  return (this->_name);
}

void	SSLConnexion::postConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "SSL Connexion.\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new SSLConnexion(log));
}
