#include	"AModule.hpp"
#include	"ContentModule.hpp"

ContentModule::ContentModule(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("ContentModule-Proxy")
{}

ContentModule::~ContentModule()
{}

void	ContentModule::contentModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message = "Content Module - Proxy\n";
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	ContentModule::getPriority() const
{
    return std::map<apimeal::eTypeModule, apimeal::ePriority>();
}

const apimeal::Version &		ContentModule::getVersion() const
{
  return (this->_version);
}

const std::string &			ContentModule::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new ContentModule(log));
}
