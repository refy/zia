#if defined	(_WIN32)
#include	<windows.h>
#else
#include	<dlfcn.h>
#endif

#include	"ModuleLoader.hpp"

ModuleLoader::ModuleLoader()
{}

ModuleLoader::ModuleLoader(const std::vector<std::string> & modules, apimeal::Error & e)
{
  for (std::vector<std::string>::const_iterator it = modules.begin();it != modules.end();++it)
    this->LoadModule((*it), e);
}

ModuleLoader::~ModuleLoader()
{}

void	ModuleLoader::LoadModule(const std::string & module, apimeal::Error & error)
{
#if defined	(_WIN32)
#else
  void	*handle = dlopen(module.c_str(), RTLD_LAZY);

  if (!handle)
    {
      error.IsError = true;
      error.Message += "Cannot open library: " + module + "\n";
      return ;
    }
#endif  
}

void	ModuleLoader::UnloadModule(const std::string & module, apimeal::Error & error)
{}

void	ModuleLoader::UnloadModule(const apimeal::eTypeModule & module, apimeal::Error & error)
{}

void	ModuleLoader::UnloadModule(const apimeal::ePriority & module, apimeal::Error & error)
{}

const apimeal::AModule*	ModuleLoader::getModuleByName(const std::string & m, apimeal::Error & e)
{}

const apimeal::AModule*	ModuleLoader::getModuleByType(const apimeal::eTypeModule & m, apimeal::Error & e)
{}

const apimeal::AModule*	ModuleLoader::getModuleByPrio(const apimeal::ePriority & m, apimeal::Error & e)
{}
