#ifndef		__PRECONNECTION_HPP__
#define		__PRECONNECTION_HPP__

#include	"IConnexion.hpp"
#include	"Error.hpp"

class	PreConnection
{
public:
  PreConnection();
  ~PreConnection();

public:
  void	preConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
