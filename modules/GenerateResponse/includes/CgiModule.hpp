#ifndef		__CGIMODULE_HPP__
#define		__CGIMODULE_HPP__

#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	CgiModule
{
public:
  CgiModule();
  ~CgiModule();

public:
  void	CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
