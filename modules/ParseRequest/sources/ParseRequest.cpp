#include	"AModule.hpp"
#include	"ParseRequest.hpp"

ParseRequest::ParseRequest(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("ParseRequest"), _pre(new PreParseRequest), _post(new PostParseRequest)
{}

ParseRequest::~ParseRequest()
{}

void	ParseRequest::postParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  this->_post->postParseRequest(r, e);
}

void	ParseRequest::preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  this->_pre->preParseRequest(r, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	ParseRequest::getPriority() const
{}

const apimeal::Version &		ParseRequest::getVersion() const
{
  return (this->_version);
}

const std::string &			ParseRequest::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new ParseRequest(log));
}
