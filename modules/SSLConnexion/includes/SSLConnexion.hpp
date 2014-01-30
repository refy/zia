#ifndef		__POSTCONNEXION_HPP__
#define		__POSTCONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

class	SSLConnexion : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  SSLConnexion(apimeal::ILogger *log);
  ~SSLConnexion();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	postConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif