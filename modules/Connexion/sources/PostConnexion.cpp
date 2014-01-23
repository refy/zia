#include	"AModule.hpp"
#include	"PostConnexion.hpp"

PostConnexion::PostConnexion()
{}

PostConnexion::~PostConnexion()
{}

void	PostConnexion::postConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Post Connexion.\n";
}
