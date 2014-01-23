#include	"AModule.hpp"
#include	"Connection.hpp"

Connection::Connection(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("Connection"), _pre(new PreConnection), _post(new PostConnection)
{}

Connection::~Connection()
{}

void	Connection::postConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  this->_post->postConnexion(c, e);
}

void	Connection::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  this->_pre->preConnexion(c, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	Connection::getPriority() const
{}

const apimeal::Version &		Connection::getVersion() const
{
  return (this->_version);
}

const std::string &			Connection::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new Connection(log));
}
