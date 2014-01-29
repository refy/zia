#include	"AModule.hpp"
#include	"PostConnexion.hpp"

PostConnexion::PostConnexion(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PostConnexion-SSL")
{}

PostConnexion::~PostConnexion()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PostConnexion::getPriority() const
{
    return std::map<apimeal::eTypeModule, apimeal::ePriority>();
}

const apimeal::Version &		PostConnexion::getVersion() const
{
  return (this->_version);
}

const std::string &			PostConnexion::getName() const
{
  return (this->_name);
}

void	PostConnexion::postConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Connexion.\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PostConnexion(log));
}
