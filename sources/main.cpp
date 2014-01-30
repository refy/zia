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

int	run_server(bool debug, const std::string & conf)
{
  Server		server;
  apimeal::Error	err;
  ConfParser*		parser = new ConfParser(err, conf);
  Logger*		log = new Logger(parser->getLoggerFormat(), debug,
					 parser->getLoggerFile());

  check_error(err, log);
  server.initServer(log, parser);
  delete parser;
  std::cout << "PLOP" << std::endl;
  server.listenServer();
  server.closeServer();
  delete log;
}

int	main(int ac, char **av)
{
  bool			debug = false;
  std::string		conf = "config.xml";

  for (int i = 1;i < ac;i++)
    {
      std::string	tmp(av[i]);

      if (tmp == "-d" || tmp == "--debug")
	debug = true;
      else if (tmp == "-h" || tmp == "--help")
	{
	  std::cout << "Usage: ./zia [configuration_file] [OPTS]" << std::endl;
	  std::cout << "	-d/--debug : debug mode, print all the log message" << std::endl;
	  return (0);
	}
      else
	conf.assign(av[i]);
    }

  run_server(debug, conf);
  return (0);
}
