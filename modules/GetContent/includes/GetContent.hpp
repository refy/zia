#ifndef		__GETCONTENT_HPP__
#define		__GETCONTENT_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"ContentModule.hpp"

class	GetContent : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  ContentModule*	_post;

public:
  GetContent(apimeal::ILogger *log);
  ~GetContent();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	contentModule(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
