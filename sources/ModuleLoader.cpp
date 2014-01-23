#if defined	(_WIN32)
#include	<windows.h>
#else
#include	<dlfcn.h>
#endif

#include	"ModuleLoader.hpp"

ModuleLoader::ModuleLoader()
{}

ModuleLoader::ModuleLoader(const std::vector<std::string> & modules, apimeal::Error & e, apimeal::ILogger *log)
{
  for (std::vector<std::string>::const_iterator it = modules.begin();it != modules.end();++it)
    this->LoadModule((*it), e, log);
}

ModuleLoader::~ModuleLoader()
{
  for (std::map<std::string, apimeal::AModule*>::iterator it = this->_mod.begin();it != this->_mod.end();++it)
    this->UnloadModule((it->first));
}

void	ModuleLoader::LoadModule(const std::string & module, apimeal::Error & error, apimeal::ILogger *log)
{
  apimeal::AModule* (*mod)(apimeal::ILogger *);

#if defined	(_WIN32)
  HMODULE	library = LoadLibrary(module.c_str());

  if (library == NULL)
    {
      error.IsError = true;
      error.Message += "Cannot open library: " + module + "\n";
      return ;
    }

  mod = (apimeal::AModule* (*)(apimeal::ILogger *))GetProcAddress(library, "LoadModule");

  if (mod == NULL)
    {
      error.IsError = true;
      error.Message += "Cannot load symbole 'LoadModule' for the module named " + module + "\n";
      FreeLibrary(library);
      return ;
    }
  this->_handles[module] = library;
#else
  void	*handle = dlopen(module.c_str(), RTLD_LAZY);

  if (!handle)
    {
      error.IsError = true;
      error.Message += "Cannot open library: " + module + "\n";
      return ;
    }

  mod = (apimeal::AModule* (*)(apimeal::ILogger *)) dlsym(handle, "LoadModule");
  const char	*dlsym_error = dlerror();
  if (dlsym_error)
    {
      error.IsError = true;
      error.Message += "Cannot load symbole 'LoadModule' for the module named " + module + "\n";
      dlclose(handle);
      return ;
    }
  this->_handles[module] = handle;
#endif
  this->_mod[module] = mod(log);
}

void	ModuleLoader::UnloadModule(const std::string & module)
{

  if (this->_handles.find(module) != this->_handles.end())
    {
#if defined	(_WIN32)
      FreeLibrary(this->_handles[module]);
#else
      dlclose(this->_handles[module]);
    }
#endif
}

const apimeal::AModule*	ModuleLoader::getModule(const std::string & m, apimeal::Error & e)
{
  if (this->_mod.find(m) != this->_mod.end())
    return this->_mod[m];
  else
    {
      e.IsError = true;
      e.Message += "The module " + m + " doesn't exist.\n";
      return NULL;
    }
}
