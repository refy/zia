#include	"AModule.hpp"
#include	"mod_base.hpp"
#include	"eTypeModule.hpp"

mod_base::mod_base(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("mod_base")
{}

mod_base::~mod_base()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	mod_base::getPriority() const
{
  std::map<apimeal::eTypeModule, apimeal::ePriority>	ret;

  return (ret);
}

const apimeal::Version &		mod_base::getVersion() const
{
  return (this->_version);
}

const std::string &			mod_base::getName() const
{
  return (this->_name);
}

void mod_base::preConnexion (apimeal::IConnexion *, apimeal::Error &){}
void mod_base::postConnexion (apimeal::IConnexion *, apimeal::Error &){}
void mod_base::preParseRequest(apimeal::IHttpRequest *, apimeal::Error &){}
void mod_base::postParseRequest (apimeal::IHttpRequest *, apimeal::Error &){}
void mod_base::contentModule (apimeal::IHttpRequest *, apimeal::Error &){}
void mod_base::CGIModule (apimeal::IHttpResponse *, apimeal::Error &){}
void mod_base::postGenerateResponse (apimeal::IHttpResponse *, apimeal::Error &){}
void mod_base::preSendRequest (apimeal::IHttpResponse *, apimeal::IConnexion *, apimeal::Error &){}
void mod_base::release (){}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new mod_base(log));
}
