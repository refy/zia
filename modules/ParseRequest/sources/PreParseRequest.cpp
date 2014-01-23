#include	"AModule.hpp"
#include	"PreParseRequest.hpp"

PreParseRequest::PreParseRequest()
{}

PreParseRequest::~PreParseRequest()
{}

void	PreParseRequest::preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Pre Parse Request.\n";
}
