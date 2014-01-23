#ifndef		__POSTCONNECTION_HPP__
#define		__POSTCONNECTION_HPP__

#include	"AModule.hpp"
#include	"ILogger.hpp"

class	PostConnection : public apimeal::AModule
{
private:
  apimeal::Version	_version;
  std::string		_name;

public:
  PostConnection(apimeal::ILogger *log);
  ~PostConnection();

public:
  std::map<apimeal::eTypeModule, apimeal::ePriority>	getPriority() const;
  const apimeal::Version &				getVersion() const;
  const std::string &					getName() const;

public:
  void	postConnection(apimeal::IConnexion *c, apimeal::Error & e);
};

#endif
