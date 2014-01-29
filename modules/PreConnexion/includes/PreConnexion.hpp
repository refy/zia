#ifndef		__PRECONNEXION_HPP__
#define		__PRECONNEXION_HPP__


#include	<iostream>
#include	<fstream>
#include	<ctime>
#include	<set>
#include	<mutex>

#include	"AModule.hpp"
#include	"ILogger.hpp"
#include	"IConnexion.hpp"
#include	"Error.hpp"

#define		PRECONNEXION_BLACKLIST_FILE	"blacklist.txt"
#define		PRECONNEXION_T_RELOAD_BLACKLIST	60

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
  
protected:
	void	load_blacklist();
  
	time_t			_t_last_blacklist;
	std::set<std::string>	_blacklist;
	std::mutex		_mutex;
};

#endif
