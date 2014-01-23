#ifndef		__PARSEREQUEST_HPP__
#define		__PARSEREQUEST_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"PreParseRequest.hpp"
#include	"PostParseRequest.hpp"

class	ParseRequest : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  PreParseRequest*	_pre;
  PostParseRequest*	_post;

public:
  ParseRequest(apimeal::ILogger *log);
  ~ParseRequest();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e);
  void	postParseRequest(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
