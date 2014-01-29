#include	"AModule.hpp"
#include	"CgiModule.hpp"

CgiModule::CgiModule(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("CGIModule")
{}

CgiModule::~CgiModule()
{}

void	CgiModule::CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "CGI Module\n";
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	CgiModule::getPriority() const
{
    return std::map<apimeal::eTypeModule, apimeal::ePriority>();
}

const apimeal::Version &		CgiModule::getVersion() const
{
  return (this->_version);
}

const std::string &			CgiModule::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new CgiModule(log));
}
