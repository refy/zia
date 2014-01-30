#ifndef		__SERVER_HPP__
#define		__SERVER_HPP__

#include	"Error.hpp"
#include	"ILogger.hpp"
#include	"ModuleLoader.hpp"
#include	"ConfParser.hpp"
#include	"IConnexion.hpp"

class	Server
{
private:
    
  apimeal::ILogger*	_log;
  apimeal::Error	_err;
  ModuleLoader		_loader;
    apimeal::IConnexion *_coWait;
    ConfParser *_conf;
    
public:
  Server(apimeal::ILogger *log, ConfParser *p, apimeal::Error & e);
  ~Server();

private:
    
  bool	checkError();
  apimeal::IConnexion	*accept_client();

    static void *pipelineEntry(void *);
    
public:
    
    void initServer(){}
    void listenServer();
    void closeServer(){}

};

#endif
