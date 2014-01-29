#ifndef		__POSTPARSEREQUEST_HPP__
#define		__POSTPARSEREQUEST_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IHttpRequest.hpp"
#include	"Error.hpp"

class	PostParseRequest : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PostParseRequest(apimeal::ILogger *log);
  ~PostParseRequest();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	postParseRequest(apimeal::IHttpRequest *c, apimeal::Error & e);
};

#endif
