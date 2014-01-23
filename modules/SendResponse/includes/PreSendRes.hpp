#ifndef		__PRESENDRES_HPP__
#define		__PRESENDRES_HPP__

#include	"IHttpResponse.hpp"
#include	"Error.hpp"

class	PreSendRes
{
public:
  PreSendRes();
  ~PreSendRes();

public:
  void	preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
