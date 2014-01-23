#include	"AModule.hpp"
#include	"PostConnection.hpp"

PostConnection::PostConnection(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PostConnection")
{}

PostConnection::~PostConnection()
{}

void	PostConnection::postConnection(apimeal::IConnexion *c, apimeal::Error & e)
{

}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PostConnection::getPriority() const
{
  
}

const apimeal::Version &		PostConnection::getVersion() const
{
  return (this->_version);
}

const std::string &			PostConnection::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PostConnection(log));
}
