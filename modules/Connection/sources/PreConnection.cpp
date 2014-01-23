#include	"AModule.hpp"
#include	"PreConnection.hpp"

PreConnection::PreConnection(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PreConnection")
{}

PreConnection::~PreConnection()
{}

void	PreConnection::preConnection(apimeal::IConnexion *c, apimeal::Error & e)
{

}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PreConnection::getPriority() const
{
  
}

const apimeal::Version &		PreConnection::getVersion() const
{
  return (this->_version);
}

const std::string &			PreConnection::getName() const
{
  return (this->_name);
}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PreConnection(log));
}
