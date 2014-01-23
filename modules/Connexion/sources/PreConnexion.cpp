#include	"AModule.hpp"
#include	"PreConnexion.hpp"

PreConnexion::PreConnexion()
{}

PreConnexion::~PreConnexion()
{}

void	PreConnexion::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message += "Pre Connexion.\n";
}
