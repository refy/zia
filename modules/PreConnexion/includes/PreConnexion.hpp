#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

class	PreConnexion : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PreConnexion(apimeal::ILogger *log);
  ~PreConnexion();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
