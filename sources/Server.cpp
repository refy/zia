#include	<signal.h>
#include	<errno.h>
#include	<sstream>
#include	<vector>
#include	"AModule.hpp"
#include	"Server.hpp"
#include	"ConnexionClient.hpp"
#include	"ConnexionAttente.hpp"
#include	"Thread.h"
#include	"pipeline.h"

Server::Server()
{}

Server::Server(apimeal::ILogger *log, ConfParser *p)
: _log(log)
{
    if (p)
    {
        this->_loader.LoadModules(p->getModulesPath(), this->_err, this->_log);
        this->_coWait = new ConnexionAttente(p->getPort());
    }
}

Server::~Server()
{}

void	Server::initServer(apimeal::ILogger *log, ConfParser *p)
{
    this->_log = log;
    if (p)
    {
        this->_loader.LoadModules(p->getModulesPath(), this->_err, this->_log);
        this->_coWait = new ConnexionAttente(p->getPort());
    }
}

bool	Server::checkError()
{
    if (this->_err.IsError)
    {
        this->_log->LogInfo(this->_err.Message);
        this->_err.Message.clear();
        this->_err.IsError = false;
        return true;
    }
    return false;
}

#include <iostream>

apimeal::IConnexion*	Server::accept_client()
{
    sockaddr_in	sin_tmp;
    SOCKET	s_tmp;
    socklen_t	sin_size;
    
    if (!this->_coWait->getSocket() < 0)
        return (0);
    sin_size = sizeof(sin_tmp);
    signal(SIGPIPE, SIG_IGN);
    if ((s_tmp = accept(this->_coWait->getSocket(), (sockaddr *)&sin_tmp, &sin_size)) < 0)
    {
        return (0);
    }
    apimeal::IConnexion *ptr = new ConnexionClient(sin_tmp, s_tmp);
    if (ptr == 0)
        return (0);
    return (ptr);
}

void *Server::pipelineEntry(void *param)
{
    apimeal::Error e;
    ModuleLoader *moduleLoader = new ModuleLoader(ConfParser::getInstance()->getModulesPath(), e, NULL);
    apimeal::IConnexion *client = (apimeal::IConnexion *)param;
    // postConnexion;
    pipeline pipe(client, moduleLoader);
    pipe.run();
//    delete client;
//    delete moduleLoader;
    return NULL;
}

void	Server::printConnexionInfo(apimeal::IConnexion *ptr, const std::string & msg)
{
    std::stringstream	s;
    std::string		ip = "IP: ";
    std::string		port = "Port: ";
    std::string		host = "Hostname: ";
    int			port_int = ptr->getPort();
    std::string		port_str;
    
    s << port_int;
    s >> port_str;
    ip += ptr->getIp();
    port += port_str;
    host += ptr->getHostname();
    this->_log->LogDebug(msg);
    this->_log->LogDebug(ip);
    this->_log->LogDebug(port);
    this->_log->LogDebug(host);
}

void	Server::listenServer()
{
    apimeal::IConnexion	*ptr;
    
    if (this->_coWait->getSocket() < 0)
        this->_log->LogError("Cannot create the waiting socket.");
    else
    {
        this->printConnexionInfo(this->_coWait, "Server socket informations: ");
        Thread		thread(this->pipelineEntry);
        while ((ptr = this->accept_client()) != 0)
        {
            this->printConnexionInfo(ptr, "Client socket informations: ");
            this->checkError();
            thread.run(ptr);
        }
    }
}
