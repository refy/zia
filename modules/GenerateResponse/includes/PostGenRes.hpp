#ifndef		__POSTGENRES_HPP__
#define		__POSTGENRES_HPP__

#include	"IHttpResponse.hpp"
#include	"Error.hpp"

class	PostGenRes
{
public:
  PostGenRes();
  ~PostGenRes();

public:
  void	postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
