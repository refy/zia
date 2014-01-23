#include	"AModule.hpp"
#include	"GenRes.hpp"

GenRes::GenRes(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("GenRes"), _cgi(new CgiModule), _post(new PostGenRes)
{}

GenRes::~GenRes()
{}

#include <iostream>

void	GenRes::postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  this->_post->postGenerateResponse(r, e);
}

void	GenRes::CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  this->_cgi->CGIModule(r, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	GenRes::getPriority() const
{}

const apimeal::Version &		GenRes::getVersion() const
{
  return (this->_version);
}

const std::string &			GenRes::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new GenRes(log));
}
