#ifndef		__GENRES_HPP__
#define		__GENRES_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"CgiModule.hpp"
#include	"PostGenRes.hpp"

class	GenRes : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  CgiModule*		_cgi;
  PostGenRes*		_post;

public:
  GenRes(apimeal::ILogger *log);
  ~GenRes();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	CGIModule(apimeal::IHttpRequest *r, apimeal::Error & e);
  void	postGenerateResponse(apimeal::IHttpResponse *r, apimeal::Error & e);
};

#endif
