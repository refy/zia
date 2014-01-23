#include	"AModule.hpp"
#include	"PreSendRes.hpp"

PreSendRes::PreSendRes()
{}

PreSendRes::~PreSendRes()
{}

void	PreSendRes::preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Pre Send Request\n";
}
