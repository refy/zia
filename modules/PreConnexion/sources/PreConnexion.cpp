#include	"AModule.hpp"
#include	"PreConnexion.hpp"

PreConnexion::PreConnexion(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PreConnexion-Blacklist")
{}

PreConnexion::~PreConnexion()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PreConnexion::getPriority() const
{}

const apimeal::Version &		PreConnexion::getVersion() const
{
  return (this->_version);
}

const std::string &			PreConnexion::getName() const
{
  return (this->_name);
}

void	PreConnexion::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Pre Connexion.\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PreConnexion(log));
}
