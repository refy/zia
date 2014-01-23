#ifndef		__MODULELOADER_HPP__
#define		__MODULELOADER_HPP__

#include	<map>
#include	<vector>
#include	<string>
#include	"AModule.hpp"
#include	"eTypeModule.hpp"
#include	"ePriority.hpp"

class	ModuleLoader
{
private:
  std::map<apimeal::eTypeModule, apimeal::AModule*>	_modulesByType;
  std::map<apimeal::ePriority, apimeal::AModule*>	_modulesByPrio;
  std::map<std::string, apimeal::AModule*>	_modulesByName;

public:
  ModuleLoader();
  ModuleLoader(const std::vector<std::string> & modules, apimeal::Error & e);
  ~ModuleLoader();

public:
  void	LoadModule(const std::string & module, apimeal::Error & error);
  void	UnloadModule(const std::string & module, apimeal::Error & error);
  void	UnloadModule(const apimeal::eTypeModule & module, apimeal::Error & error);
  void	UnloadModule(const apimeal::ePriority & module, apimeal::Error & error);

public:
  const apimeal::AModule*	getModuleByName(const std::string & m, apimeal::Error & e);
  const apimeal::AModule*	getModuleByType(const apimeal::eTypeModule & m, apimeal::Error & e);
  const apimeal::AModule*	getModuleByPrio(const apimeal::ePriority & m, apimeal::Error & e);
};

#endif
