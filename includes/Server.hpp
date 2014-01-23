#ifndef		__SERVER_HPP__
#define		__SERVER_HPP__

#include	"Error.hpp"
#include	"ILogger.hpp"
#include	"ModuleLoader.hpp"
#include	"ConfParser.hpp"

class	Server
{
private:
  apimeal::ILogger*	_log;
  apimeal::Error	_err;
  ModuleLoader		_loader;

public:
  Server(apimeal::ILogger *log, ConfParser *p, apimeal::Error & e);
  ~Server();

private:
  bool	checkError();

public:
  void	run();
};

#endif
