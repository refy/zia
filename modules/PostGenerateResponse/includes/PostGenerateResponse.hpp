#ifndef		__POSTGENERATERESPONSE_HPP__
#define		__POSTGENERATERESPONSE_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IHttpResponse.hpp"
#include	"Error.hpp"

class	PostGenerateResponse : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PostGenerateResponse(apimeal::ILogger *log);
  ~PostGenerateResponse();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
