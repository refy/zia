#include	"AModule.hpp"
#include	"PreConnection.hpp"

PreConnection::PreConnection()
{}

PreConnection::~PreConnection()
{}

void	PreConnection::preConnexion(apimeal::IConnexion *c, apimeal::Error & e)
{
  e.IsError = true;
  e.Message = "KIKOO JE SUIS DANS UN MODULE LOL";
}
