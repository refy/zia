#ifndef		__GETCONTENT_HPP__
#define		__GETCONTENT_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"

class	ContentModule : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  ContentModule(apimeal::ILogger *log);
  ~ContentModule();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	contentModule(apimeal::IHttpRequest *r, apimeal::Error & e);
};

#endif
