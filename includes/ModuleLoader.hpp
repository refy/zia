#ifndef		__MODULELOADER_HPP__
#define		__MODULELOADER_HPP__

#if defined     (_WIN32)
#include        <windows.h>
#endif
#include	<map>
#include	<vector>
#include	<string>
#include	"AModule.hpp"
#include	"ILogger.hpp"

class	ModuleLoader
{
private:
  std::map<std::string, apimeal::AModule*>		_mod;
#if defined	(_WIN32)
  std::map<std::string, HMODULE>	_handles;
#else
  std::map<std::string, void*>		_handles;
#endif

public:
  ModuleLoader();
  ModuleLoader(const std::vector<std::string> & modules, apimeal::Error & e, apimeal::ILogger *log);
  ~ModuleLoader();

public:
  void	LoadModules(const std::vector<std::string> & m, apimeal::Error & e, apimeal::ILogger *log);
  void	LoadModule(const std::string & module, apimeal::Error & error, apimeal::ILogger *log);
  void	UnloadModule(const std::string & module);

public:
  apimeal::AModule*	getModule(const std::string & m, apimeal::Error & e);
};

#endif
