#ifndef		__PREPARSEREQUEST_HPP__
#define		__PREPARSEREQUEST_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	PreParseRequest : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PreParseRequest(apimeal::ILogger *log);
  ~PreParseRequest();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
