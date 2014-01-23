#include	"AModule.hpp"
#include	"ContentModule.hpp"

ContentModule::ContentModule()
{}

ContentModule::~ContentModule()
{}

void	ContentModule::contentModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Content Module\n";
}
