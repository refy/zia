#ifndef		__SENDRES_HPP__
#define		__SENDRES_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"PreSendRes.hpp"

class	SendRes : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  PreSendRes*		_pre;

public:
  SendRes(apimeal::ILogger *log);
  ~SendRes();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preSendRequest(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
