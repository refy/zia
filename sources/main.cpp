#include	<string>
#include	<iostream>
#include	"ConfParser.hpp"
#include	"Error.hpp"
#include	"Logger.hpp"
#include	"ModuleLoader.hpp"

int	main(int ac, char **av)
{
  bool			debug = false;
  std::string		conf;
  apimeal::Error	err;

  if (ac < 2)
    {
      std::cout << "Usage: ./zia configuration_file [OPTS]" << std::endl;
      std::cout << "	-d/--debug : debug mode, print all the log message" << std::endl;
    }
  for (int i = 1;i < ac;i++)
    {
      std::string	tmp(av[i]);

      if (tmp == "-d" || tmp == "--debug")
	debug = true;
      else
	conf.assign(av[i]);
    }

  ConfParser	*parser = new ConfParser(conf);

  parser->initialize(err);

  Logger	*log = new Logger(parser->getLoggerFormat(), debug,
				  parser->getLoggerFile());

  if (err.IsError)
    log->LogError(err.Message);

  ModuleLoader	modules(parser->getModulesPath(), err, log);

  if (err.IsError)
    log->LogError(err.Message);

  delete log;
  return (0);
}
