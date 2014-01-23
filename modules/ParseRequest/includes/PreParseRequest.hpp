#ifndef		__PREPARSEREQUEST_HPP__
#define		__PREPARSEREQUEST_HPP__

#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	PreParseRequest
{
public:
  PreParseRequest();
  ~PreParseRequest();

public:
  void	preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
