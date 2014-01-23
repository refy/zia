#include	"AModule.hpp"
#include	"PostParseRequest.hpp"

PostParseRequest::PostParseRequest()
{}

PostParseRequest::~PostParseRequest()
{}

void	PostParseRequest::postParseRequest(apimeal::IHttpRequest *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Parse Request.\n";
}
