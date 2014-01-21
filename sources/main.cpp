#include	<string>
#include	<iostream>
#include	"ConfParser.hpp"
#include	"Error.hpp"
#include	"Logger.hpp"

int	main(int ac, char **av)
{
  bool			debug = false;
  std::string		conf;
  apimeal::Error	err;

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

  if (err.IsError && debug)
    log->LogError(err.Message);
}
