#include	"AModule.hpp"
#include	"Connexion.hpp"

Connexion::Connexion(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("Connexion"), _pre(new PreConnexion), _post(new PostConnexion)
{}

Connexion::~Connexion()
{}

void	Connexion::postConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  this->_post->postConnexion(c, e);
}

void	Connexion::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  this->_pre->preConnexion(c, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	Connexion::getPriority() const
{}

const apimeal::Version &		Connexion::getVersion() const
{
  return (this->_version);
}

const std::string &			Connexion::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new Connexion(log));
}
