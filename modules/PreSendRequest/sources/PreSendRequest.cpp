#include	"AModule.hpp"
#include	"PreSendRequest.hpp"

PreSendRequest::PreSendRequest(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PreSendRequest-SSL")
{}

PreSendRequest::~PreSendRequest()
{}

void	PreSendRequest::preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message = "Pre Send Request - SSL\n";
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PreSendRequest::getPriority() const
{}

const apimeal::Version &		PreSendRequest::getVersion() const
{
  return (this->_version);
}

const std::string &			PreSendRequest::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PreSendRequest(log));
}
