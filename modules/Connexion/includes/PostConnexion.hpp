#ifndef		__POSTCONNEXION_HPP__
#define		__POSTCONNEXION_HPP__

#include	"IConnexion.hpp"
#include	"Error.hpp"

class	PostConnexion
{
public:
  PostConnexion();
  ~PostConnexion();

public:
  void	postConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
