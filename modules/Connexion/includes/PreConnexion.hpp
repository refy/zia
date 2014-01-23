#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__

#include	"IConnexion.hpp"
#include	"Error.hpp"

class	PreConnexion
{
public:
  PreConnexion();
  ~PreConnexion();

public:
  void	preConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
