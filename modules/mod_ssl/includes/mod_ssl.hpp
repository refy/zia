#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

class	mod_ssl : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  mod_ssl(apimeal::ILogger *log);
  ~mod_ssl();

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
    int recv(std::string &buf);
    int send(const std::string &string);
    
protected:
    SSL_CTX*                    ctx;
    SSL*                        ssl;
    int                         listenSocket;
    bool                        _closed;
    std::string                 _address;
    int                         _port;
    bool                        sslEnabled;
};

#endif
