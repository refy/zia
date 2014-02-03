#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

class	mod_phpcgi : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  mod_phpcgi(apimeal::ILogger *log);
  ~mod_phpcgi();

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
    std::string body;
    std::string cgiContent;
    std::string clientIp;
    int port;
    char **createEnv(apimeal::IHttpRequest* req) const;
    char **env;
    void error(apimeal::IHttpResponse *resp);
    bool PHPerror;
    int clientSock;
    bool isPhp;
};

#endif
