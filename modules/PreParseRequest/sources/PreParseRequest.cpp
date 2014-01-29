#include	"AModule.hpp"
#include	"PreParseRequest.hpp"

PreParseRequest::PreParseRequest(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PreParseRequest-Decode")
{}

PreParseRequest::~PreParseRequest()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PreParseRequest::getPriority() const
{}

const apimeal::Version &		PreParseRequest::getVersion() const
{
  return (this->_version);
}

const std::string &			PreParseRequest::getName() const
{
  return (this->_name);
}

void	PreParseRequest::preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Pre Parse Request.\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PreParseRequest(log));
}
