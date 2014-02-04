#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

class	mod_error : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  mod_error(apimeal::ILogger *log);
  ~mod_error();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;
  void preConnexion (apimeal::IConnexion *, apimeal::Error &);
  void postConnexion (apimeal::IConnexion *, apimeal::Error &);
  void preParseRequest(apimeal::IHttpRequest *, apimeal::Error &);
  void postParseRequest (apimeal::IHttpRequest *, apimeal::Error &);
  void contentModule (apimeal::IHttpRequest *, apimeal::Error &);
  void CGIModule (apimeal::IHttpRequest *, apimeal::Error &);
  void postGenerateResponse (apimeal::IHttpResponse *, apimeal::Error &);
  void preSendRequest (apimeal::IHttpResponse *, apimeal::Error &);
  void release ();

protected:

};

#endif
