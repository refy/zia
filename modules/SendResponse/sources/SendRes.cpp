#include	"AModule.hpp"
#include	"SendRes.hpp"

SendRes::SendRes(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("SendRes"), _pre(new PreSendRes)
{}

SendRes::~SendRes()
{}

void	SendRes::preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  this->_pre->preSendRequest(r, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	SendRes::getPriority() const
{}

const apimeal::Version &		SendRes::getVersion() const
{
  return (this->_version);
}

const std::string &			SendRes::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new SendRes(log));
}
