#include	"AModule.hpp"
#include	"GetContent.hpp"

GetContent::GetContent(apimeal::ILogger *log)
  : AModule(log), _version(0, 1), _name("GetContent"), _post(new ContentModule)
{}

GetContent::~GetContent()
{}

void	GetContent::contentModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  this->_post->contentModule(r, e);
}

std::map<apimeal::eTypeModule, apimeal::ePriority>	GetContent::getPriority() const
{}

const apimeal::Version &		GetContent::getVersion() const
{
  return (this->_version);
}

const std::string &			GetContent::getName() const
{
  return (this->_name);
}

extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
  return (new GetContent(log));
}
