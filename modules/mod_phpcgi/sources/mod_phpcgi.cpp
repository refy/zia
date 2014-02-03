#include	<iostream>
#include	"AModule.hpp"
#include	"mod_phpcgi.hpp"
#include	"eTypeModule.hpp"
#include	<sstream>
#include <unistd.h>

mod_phpcgi::mod_phpcgi(apimeal::ILogger *log)
: AModule(log), _version(0, 1), _name("mod_phpcgi")
{}

mod_phpcgi::~mod_phpcgi()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	mod_phpcgi::getPriority() const
{
    std::map<apimeal::eTypeModule, apimeal::ePriority>	ret;
    
    ret[apimeal::CGIMODULE] = 1.0f;
    ret[apimeal::POSTCONNEXION] = 1.0f;
    ret[apimeal::SENDREQUEST] = 1.0f;
    ret[apimeal::CONTENTMODULE] = 1.0f;
    return (ret);
}

const apimeal::Version &		mod_phpcgi::getVersion() const
{
    return (this->_version);
}

const std::string &			mod_phpcgi::getName() const
{
    return (this->_name);
}

char**                          mod_phpcgi::createEnv(apimeal::IHttpRequest* req) const
{
    std::map<std::string, std::string>      env;
    char                                    port[42];
    sprintf(port, "%d", this->port);
    
    env["SERVER_SOFTWARE"] = "ziahttpd";
    env["SERVER_NAME"] = "zia";
    if (req->getHeaders().find("Host") != req->getHeaders().end())
        env["HTTP_HOST"] = req->getHeaders().at("Host");
    env["GATEWAY_INTERFACE"] = "CGI/1.1";
    env["SERVER_PROTOCOL"] = "HTTP/1.1";
    env["SERVER_PORT"] = port;
    env["REQUEST_METHOD"] = req->getMethod();
    std::string query = "";
    std::string script = req->getRequestURI();
    if (script.find("?") != script.npos)
    {
        query = script.substr(script.find("?") + 1);
        script = script.substr(0, script.find("?"));
        std::cout << query << std::endl;
    }
    env["PATH_TRANSLATED"] = script;
    env["SCRIPT_FILENAME"] = script;
    env["SCRIPT_NAME"] = script;
    env["QUERY_STRING"] = query;
    env["REMOTE_HOST"] = "REMOTE_ADDR";
    env["REMOTE_ADDR"] = this->clientIp;
    env["CONTENT_TYPE"] = "HTTP";
    env["REDIRECT_STATUS"] = "true";
    if (req->getHeaders().find("Content-Length") != req->getHeaders().end())
        env["CONTENT_LENGTH"] = req->getHeaders().at("Content-Length");
    else
        env["CONTENT_LENGTH"] = "0";
    if (req->getHeaders().find("Content-Type") != req->getHeaders().end())
        env["CONTENT_TYPE"] = req->getHeaders().at("Content-Type");
    
    char** newEnv = new char*[env.size() + 1];
    std::map<std::string, std::string>::const_iterator      it = env.begin();
    std::map<std::string, std::string>::const_iterator      ite = env.end();
    
    int     i;
    for (i = 0; it != ite; ++it, ++i)
        newEnv[i] = strdup(std::string(it->first + "=" + it->second).c_str());
    newEnv[i] = NULL;
    return newEnv;
}

void mod_phpcgi::preConnexion (apimeal::IConnexion *, apimeal::Error &){}

void mod_phpcgi::postConnexion (apimeal::IConnexion *con, apimeal::Error &e)
{
    this->clientIp = con->getIp();
    this->port = con->getPort();
    this->clientSock = con->getSocket();
}

void mod_phpcgi::preParseRequest(apimeal::IHttpRequest *, apimeal::Error &){}

void mod_phpcgi::postParseRequest (apimeal::IHttpRequest *, apimeal::Error &){}

void mod_phpcgi::contentModule (apimeal::IHttpRequest *req, apimeal::Error &e)
{
    this->cgiContent = req->getBody();
    this->env = this->createEnv(req);
}

void mod_phpcgi::error(apimeal::IHttpResponse *resp)
{
    resp->setReasonPhrase("Internal server error");
    resp->setStatusCode(500);
}

#include <sys/stat.h>

void mod_phpcgi::CGIModule (apimeal::IHttpRequest *resp, apimeal::Error &e)
{
    pid_t pid = 1;
    int pipe_in[2];
    int pipe_out[2];
    this->PHPerror = false;
    this->cgiContent = "";
    this->isPhp = false;
    this->body = resp->getBody();
    std::string fname = resp->getRequestURI();
    struct stat buffer;
    
    if (fname.find("?") != fname.npos)
    {
        fname = fname.substr(0, fname.find("?"));
    }
    
    if ((resp->getRequestURI().find(".php") != resp->getRequestURI().npos || resp->getRequestURI().find(".html") != resp->getRequestURI().npos) && stat (fname.c_str(), &buffer) == 0)
    {
        this->isPhp = true;
        pipe(pipe_in);
        pipe(pipe_out);
        signal(SIGCHLD, SIG_IGN);
        pid = fork();
        if (pid == -1) {
            this->PHPerror = true;
            close(pipe_out[0]);
            close(pipe_out[1]);
            close(pipe_in[0]);
            close(pipe_in[1]);
            return;
        }
        if (pid == 0) {
            std::string bin("/usr/bin/php-cgi");
            char *argv[] = {
                strdup("/usr/bin/php-cgi"),
                strdup("BITE=BATE"),
                NULL
            };
            close(this->clientSock);
            dup2(pipe_in[0], 0);
            dup2(pipe_out[1], 1);
            close(pipe_in[1]);
            close(pipe_out[0]);
            exit(execve(bin.c_str(), argv, this->env));
            
        } else {
            
            int child_rt;
            close(pipe_in[0]);
            close(pipe_out[1]);
            if (this->body.size())
            {
                write(pipe_in[1], this->body.c_str(), this->body.size());
            }
            close(pipe_in[1]);
            waitpid(pid, &child_rt, 0);
            if (child_rt < 0) {
                close(pipe_out[0]);
                this->PHPerror = true;
            }
            char buff[128];
            std::string bdy;
            long size;
            size = read(pipe_out[0], buff, 128);
            while (size != -1 && size) {
                bdy.append(buff, size);
                size = read(pipe_out[0], buff, 128);
            }
            if (size == -1) {
                close(pipe_out[0]);
                this->PHPerror = true;
            }
            this->cgiContent = bdy;
            std::cout << this->cgiContent << std::endl;
            close(pipe_out[0]);
        }
    }
}

void mod_phpcgi::postGenerateResponse (apimeal::IHttpResponse *resp, apimeal::Error &)
{
    std::ostringstream oss;
    
    oss << resp->getBody().size();
    resp->addHeader("Content-Length", oss.str());
}

void mod_phpcgi::preSendRequest (apimeal::IHttpResponse *resp, apimeal::Error &)
{
    if (this->isPhp)
    {
        std::string header;
        std::string phpBody;
        long size;
        size_t pos, last_pos;
        std::string bdy = this->cgiContent;
        pos = bdy.find("\r\n\r\n");
        
        if (this->PHPerror)
        {
            this->error(resp);
            return;
        }
        header = bdy.substr(0, pos);
        if (pos != std::string::npos) {
            phpBody = bdy.substr(pos + 4);
            
            char *tmp;
            size = phpBody.size();
            std::cout << "body " << phpBody << std::endl;

            resp->setBody(phpBody);
        }
        
        last_pos = pos = 0;
        size_t line_pos;
        
        do{
            pos = header.find("\r\n", last_pos);
            std::string line = header.substr(last_pos, pos - last_pos);
            
            line_pos = line.find(": ");
            std::string key(line.substr(0, line_pos));
            std::string value(line.substr(line_pos + 2));
            
            if (key == "Status") {
                size_t pos;
                
                pos = value.find_first_of(' ');
                resp->setStatusCode(atoi(value.substr(0, pos).c_str()));
                resp->setReasonPhrase(value.substr(pos + 1));
            } else {
                resp->addHeader(key, value);
            }
            
            last_pos = pos + 2;
        } while (std::string::npos != pos);
        std::ostringstream oss;
        oss << resp->getBody().size();
        resp->addHeader("Content-Length", oss.str());
    }
}

void mod_phpcgi::release (){}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
    return (new mod_phpcgi(log));
}
