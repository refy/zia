#if defined	(_WIN32)
#include	<windows.h>
#else
#include	<dlfcn.h>
#endif

#include	<iostream>
#include	"AModule.hpp"
#include	"Logger.hpp"

apimeal::AModule *Load(Logger *log, char **argv)
{

  void* handle = dlopen(argv[1], RTLD_LAZY);

  if (!handle)
    {
      std::cerr << "Cannot open library: " << dlerror() << std::endl;
      return NULL;
    }

  apimeal::AModule* (*create)(apimeal::ILogger *);

  create = (apimeal::AModule* (*)(apimeal::ILogger *))dlsym(handle, "LoadModule");

  const char *dlsym_error = dlerror();

  if (dlsym_error)
    {
      std::cerr << "Cannot load symbol 'LoadModule': " << dlsym_error << std::endl;
      dlclose(handle);
      return NULL;
    }
  return create(log);
}

int	main(int ac, char **av)
{
  if (ac != 2)
    {
      std::cerr << "No librarie !" << std::endl;
      return (-1);
    }

  Logger		*log = new Logger();
  apimeal::AModule	*mod = Load(log, av);

  if (mod == NULL)
    return (-1);

  std::cout << mod->getVersion().Minor << std::endl;

  mod->release();

  return (0);
}
