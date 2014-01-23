#ifndef		__POSTCONNEXION_HPP__
#define		__POSTCONNEXION_HPP__

#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	PostParseRequest
{
public:
  PostParseRequest();
  ~PostParseRequest();

public:
  void	postParseRequest(apimeal::IHttpRequest *c, apimeal::Error & e);
};

#endif
