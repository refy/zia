#ifndef		__CONNEXION_HPP__
#define		__CONNEXION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"PreConnexion.hpp"
#include	"PostConnexion.hpp"

class	Connexion : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;
  PreConnexion*	_pre;
  PostConnexion*	_post;

public:
  Connexion(apimeal::ILogger *log);
  ~Connexion();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preConnexion(apimeal::IConnexion *c, apimeal::Error & e);
  void	postConnexion(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
