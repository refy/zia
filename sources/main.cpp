#include	<string>
#include	<iostream>
#include	"ConfParser.hpp"
#include	"Error.hpp"
#include	"Logger.hpp"
#include	"Server.hpp"

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
  std::string		conf = "config.xml";
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

  Server	server(log, parser, err);

  check_error(err, log);
  delete parser;

  server.run();

  delete log;
  return (0);
}
