#include	<string>
#include	<iostream>
#include	"ConfParser.hpp"
#include	"Error.hpp"
#include	"Logger.hpp"
#include	"ModuleLoader.hpp"

bool	check_error(apimeal::Error & e, apimeal::ILogger *log)
{
  if (e.IsError)
    {
      log->LogError(e.Message);
      e.Message.clear();
      e.IsError = false;
      return true;
    }
  return false;
}

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

  check_error(err, log);

  ModuleLoader	modules(parser->getModulesPath(), err, log);

  check_error(err, log);

  apimeal::AModule	*con = modules.getModule("Connection", err);

  if (!*check_error(err, log))
    {
      con->preConnexion(NULL, err);
      check_error(err, log);
    }
  delete log;
  return (0);
}
