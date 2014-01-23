#ifndef		__CONNECTION_HPP__
#define		__CONNECTION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"PreConnection.hpp"
#include	"PostConnection.hpp"

class	Connection : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  PreConnection*	_pre;
  PostConnection*	_post;

public:
  Connection(apimeal::ILogger *log);
  ~Connection();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preConnexion(apimeal::IConnexion *c, apimeal::Error & e);
  void	postConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
