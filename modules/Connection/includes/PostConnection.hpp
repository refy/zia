#ifndef		__POSTCONNECTION_HPP__
#define		__POSTCONNECTION_HPP__

#include	"IConnexion.hpp"
#include	"Error.hpp"

class	PostConnection
{
public:
  PostConnection();
  ~PostConnection();

public:
  void	postConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif