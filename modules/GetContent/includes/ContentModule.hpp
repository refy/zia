#ifndef		__CONTENTMODULE_HPP__
#define		__CONTENTMODULE_HPP__

#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	ContentModule
{
public:
  ContentModule();
  ~ContentModule();

public:
  void	contentModule(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
