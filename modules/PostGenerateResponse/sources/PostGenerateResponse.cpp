#include	"AModule.hpp"
#include	"PostGenerateResponse.hpp"

PostGenerateResponse::PostGenerateResponse(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("PostGenerateResponse-Encode")
{}

PostGenerateResponse::~PostGenerateResponse()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	PostGenerateResponse::getPriority() const
{}

const apimeal::Version &		PostGenerateResponse::getVersion() const
{
  return (this->_version);
}

const std::string &			PostGenerateResponse::getName() const
{
  return (this->_name);
}

void	PostGenerateResponse::postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Generate Response Encode\n";
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new PostGenerateResponse(log));
}
