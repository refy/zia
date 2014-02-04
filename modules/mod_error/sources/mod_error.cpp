#include	<iostream>
#include	"AModule.hpp"
#include	"mod_error.hpp"
#include	"eTypeModule.hpp"
#include	<sstream>
#include <unistd.h>

mod_error::mod_error(apimeal::ILogger *log)
: AModule(log), _version(0, 1), _name("mod_error")
{}

mod_error::~mod_error()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	mod_error::getPriority() const
{
    std::map<apimeal::eTypeModule, apimeal::ePriority>	ret;
    
    ret[apimeal::SENDREQUEST];
    return (ret);
}

const apimeal::Version &		mod_error::getVersion() const
{
    return (this->_version);
}

const std::string &			mod_error::getName() const
{
    return (this->_name);
}

void mod_error::preConnexion (apimeal::IConnexion *, apimeal::Error &){}

void mod_error::postConnexion (apimeal::IConnexion *con, apimeal::Error &e)
{}
void mod_error::preParseRequest(apimeal::IHttpRequest *, apimeal::Error &){}

void mod_error::postParseRequest (apimeal::IHttpRequest *, apimeal::Error &){}

void mod_error::contentModule (apimeal::IHttpRequest *req, apimeal::Error &e)
{}


void mod_error::CGIModule (apimeal::IHttpRequest *resp, apimeal::Error &e)
{}

void mod_error::postGenerateResponse (apimeal::IHttpResponse *resp, apimeal::Error &)
{}

void mod_error::preSendRequest (apimeal::IHttpResponse *resp, apimeal::Error &e)
{
    if (e.IsError)
    {
        std::ostringstream oss;
        oss << e.Code;
        oss << " - " + e.Message;
        resp->setBody(oss.str());
        std::ostringstream iss;
        iss << resp->getBody().size();
        resp->addHeader("Content-Length", iss.str());
    }
}

void mod_error::release (){}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
    return (new mod_error(log));
}
