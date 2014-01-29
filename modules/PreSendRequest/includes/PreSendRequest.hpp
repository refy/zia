#ifndef		__PRESENDREQUEST_HPP__
#define		__PRESENDREQUEST_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"

class	PreSendRequest : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PreSendRequest(apimeal::ILogger *log);
  ~PreSendRequest();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
