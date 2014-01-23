#include	"AModule.hpp"
#include	"PostGenRes.hpp"

PostGenRes::PostGenRes()
{}

PostGenRes::~PostGenRes()
{}

void	PostGenRes::postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Generate Response\n";
}
