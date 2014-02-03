#include	<iostream>
#include	"AModule.hpp"
#include	"mod_dir.hpp"
#include	"eTypeModule.hpp"
#include	<sstream>
#include <sys/stat.h>
#include <dirent.h>

mod_dir::mod_dir(apimeal::ILogger *log)
: AModule(log), _version(0, 1), _name("mod_dir")
{}

mod_dir::~mod_dir()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	mod_dir::getPriority() const
{
    std::map<apimeal::eTypeModule, apimeal::ePriority>	ret;
    
    ret[apimeal::POSTPARSEREQUEST] = 0.5f;
    ret[apimeal::CGIMODULE] = 0.5f;
    //    ret[apimeal::POSTGENERATERESPONSE] = 0.5f;
    return (ret);
}

const apimeal::Version &		mod_dir::getVersion() const
{
    return (this->_version);
}

const std::string &			mod_dir::getName() const
{
    return (this->_name);
}

void mod_dir::preConnexion (apimeal::IConnexion *, apimeal::Error &){}
void mod_dir::postConnexion (apimeal::IConnexion *, apimeal::Error &){}
void mod_dir::preParseRequest(apimeal::IHttpRequest *, apimeal::Error &){}

void mod_dir::postParseRequest (apimeal::IHttpRequest *req, apimeal::Error &e)
{
    struct stat st;
    
    isDir = false;
    this->requested = req->getRequestURI();
    if (req->getHeaders().find("Host") != req->getHeaders().end())
        this->host = req->getHeaders().at("Host");
    if (req->getHeaders().find("RealURI") != req->getHeaders().end())
        this->URI = req->getHeaders().at("RealURI");
    if (stat(req->getRequestURI().c_str(), &st) == 0)
    {
        if (S_ISDIR(st.st_mode))
        {
            isDir = true;
        }
    }
}

void mod_dir::contentModule (apimeal::IHttpRequest *, apimeal::Error &){}

void mod_dir::CGIModule (apimeal::IHttpResponse *, apimeal::Error &)
{}

void mod_dir::postGenerateResponse (apimeal::IHttpResponse *resp, apimeal::Error &e)
{
    struct stat st;
    
    if (this->isDir)
    {
        if (this->requested[this->requested.size() - 1] != '/')
        {
            e.Message = "Moved Permanently";
            e.Code = 301;
            resp->setReasonPhrase("Moved Permanently");
            resp->setStatusCode(301);
            resp->addHeader("Location", "http://" + host + URI + "/");
        }
        else if (stat((this->requested + "index.php").c_str(), &st) == 0 && S_ISREG(st.st_mode))
        {
            e.Message = "Moved Permanently";
            e.Code = 301;
            resp->setReasonPhrase("Moved Permanently");
            resp->setStatusCode(301);
            resp->addHeader("Location", "http://" + host + URI + "index.php");
        }
        else if (stat((this->requested + "index.html").c_str(), &st) == 0 && S_ISREG(st.st_mode))
        {
            e.Message = "Moved Permanently";
            e.Code = 301;
            resp->setReasonPhrase("Moved Permanently");
            resp->setStatusCode(301);
            resp->addHeader("Location", "http://" + host + URI + "index.html");
        }
        else
        {
            DIR *dir;
            struct dirent *ent;
            if ((dir = opendir(this->requested.c_str())) != NULL)
            {
                resp->setBody("");
                while ((ent = readdir (dir)) != NULL)
                {
                    if (std::string(ent->d_name) != ".")
                        resp->setBody(resp->getBody() + "<a href=\"" + ent->d_name + "\">" + ent->d_name + "</a><br/>");
                }
                closedir (dir);
                std::ostringstream oss;
                
                oss << resp->getBody().size();
                resp->addHeader("Content-Length", oss.str());
            }
        }
    }
    
}

void mod_dir::preSendRequest (apimeal::IHttpResponse *resp, apimeal::IConnexion *, apimeal::Error &){}

void mod_dir::release (){}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
    return (new mod_dir(log));
}
