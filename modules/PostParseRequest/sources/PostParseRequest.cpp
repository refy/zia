#include	"AModule.hpp"
#include	"PostParseRequest.hpp"

PostParseRequest::PostParseRequest(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PostParseRequest-URLRewriting")
{}

PostParseRequest::~PostParseRequest()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PostParseRequest::getPriority() const
{}

const apimeal::Version &		PostParseRequest::getVersion() const
{
  return (this->_version);
}

const std::string &			PostParseRequest::getName() const
{
  return (this->_name);
}

void	PostParseRequest::postParseRequest(apimeal::IHttpRequest *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Parse Request.\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PostParseRequest(log));
}
