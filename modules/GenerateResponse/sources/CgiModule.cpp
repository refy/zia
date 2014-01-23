#include	"AModule.hpp"
#include	"CgiModule.hpp"

CgiModule::CgiModule()
{}

CgiModule::~CgiModule()
{}

void	CgiModule::CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "CGI Module\n";
}
