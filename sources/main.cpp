#include	<string>
#include	<iostream>
#include	"ConfParser.hpp"
#include	"Error.hpp"
#include	"Logger.hpp"
#include	"Server.hpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

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
    std::string			conf = "config.xml";
    apimeal::Error		err;
    Logger			*log;
    
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
    
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    
    ConfParser	*parser = ConfParser::getInstance();
    parser->setFile(conf);

    parser->initialize(err);

    log = Logger::getInstance(parser->getLoggerFormat(), debug,
                              parser->getLoggerFile());
    
    check_error(err, log);
    
    Server	server(log, parser);
    
    check_error(err, log);
    server.listenServer();
    
    log->kill();
    return (0);
}
