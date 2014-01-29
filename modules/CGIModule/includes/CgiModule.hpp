#ifndef		__CGIMODULE_HPP__
#define		__CGIMODULE_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	CgiModule : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  CgiModule(apimeal::ILogger *log);
  ~CgiModule();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
