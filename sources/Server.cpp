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
        std::vector<int> ports = p->getPorts();
        std::vector<int>::iterator ite;
        
        ite = ports.begin();
        while (ite != ports.end()) {
            std::cout << *ite << std::endl;
            apimeal::IConnexion *tmp = new ConnexionAttente(*ite);
            if (tmp->getSocket() >= 0)
                this->_coWait.push_back(tmp);
            ++ite;
        }
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
        std::vector<int> ports = p->getPorts();
        std::vector<int>::iterator ite;
        
        ite = ports.begin();
        while (ite != ports.end()) {
            this->_coWait.push_back(new ConnexionAttente(*ite));
            ++ite;
        }
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

#include <sys/select.h>

apimeal::IConnexion *Server::multiSelect()
{
    apimeal::IConnexion *ret = NULL;
    int ndfs = 0;
    fd_set sock_sel;
    int sel_ret;
    FD_ZERO(&sock_sel);
    
    std::vector<apimeal::IConnexion *>::iterator ite = this->_coWait.begin();
    while (ite != this->_coWait.end())
    {
        std::cout << (*ite)->getSocket() << std::endl;
        FD_SET((*ite)->getSocket(), &sock_sel);
        if ((*ite)->getSocket() > ndfs)
            ndfs = (*ite)->getSocket();
        ite++;
    }
    ndfs++;
    sel_ret = select(ndfs, &sock_sel, NULL, NULL, NULL);
    if (sel_ret > 0)
    {
        ite = this->_coWait.begin();
        while (ite != this->_coWait.end() && ret == NULL)
        {
            if (FD_ISSET((*ite)->getSocket(), &sock_sel))
            {
                ret = (*ite);
            }
            ite++;
        }
    }
    return ret;
}

#include <iostream>

apimeal::IConnexion*	Server::accept_client()
{
    sockaddr_in	sin_tmp;
    SOCKET	s_tmp;
    socklen_t	sin_size;
    apimeal::IConnexion *tmp;
    
    if (this->_coWait.size() <= 0)
        return (0);
    sin_size = sizeof(sin_tmp);
    signal(SIGPIPE, SIG_IGN);
    tmp = this->multiSelect();
    std::cout << "TT" << tmp << std::endl;
    if (tmp)
    {
        if ((s_tmp = accept(tmp->getSocket(), (sockaddr *)&sin_tmp, &sin_size)) < 0)
        {
            return (0);
        }
        apimeal::IConnexion *ptr = new ConnexionClient(sin_tmp, s_tmp, tmp);
        if (ptr == 0)
            return (0);
        return (ptr);
    }
    return 0;
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
    
    if (this->_coWait.size() <= 0)
        this->_log->LogError("Cannot create the waiting socket.");
    else
    {
        if (this->_coWait.size())
            this->printConnexionInfo(this->_coWait[0], "Server socket informations: ");
        Thread		thread(this->pipelineEntry);
        while (this->_coWait.size() > 0)
        {
            ptr = this->accept_client();
            if (ptr)
            {
                this->printConnexionInfo(ptr, "Client socket informations: ");
                this->checkError();
                thread.run(ptr);
            }
        }
    }
}
