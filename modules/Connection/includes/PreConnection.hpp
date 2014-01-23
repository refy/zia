#ifndef		__PRECONNECTION_HPP__
#define		__PRECONNECTION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"

class	PreConnection : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PreConnection(apimeal::ILogger *log);
  ~PreConnection();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	preConnection(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
