#include	<iostream>
#include	"AModule.hpp"
#include	"mod_ssl.hpp"
#include	"eTypeModule.hpp"
#include	<sstream>
#include <unistd.h>

mod_ssl::mod_ssl(apimeal::ILogger *log)
: AModule(log), _version(0, 1), _name("mod_ssl")
{
    SSL_library_init(); // load encryption & hash algorithms for SSL
    SSL_load_error_strings(); // load the error strings for good error reporting
}

mod_ssl::~mod_ssl()
{}

std::map<apimeal::eTypeModule, apimeal::ePriority>	mod_ssl::getPriority() const
{
    std::map<apimeal::eTypeModule, apimeal::ePriority>	ret;
    
    ret[apimeal::POSTCONNEXION] = 1.0f;
    ret[apimeal::SENDREQUEST] = 1.0f;
    return (ret);
}

const apimeal::Version &		mod_ssl::getVersion() const
{
    return (this->_version);
}

const std::string &			mod_ssl::getName() const
{
    return (this->_name);
}

void mod_ssl::preConnexion (apimeal::IConnexion *, apimeal::Error &){}

int     mod_ssl::send(const std::string &string)
{
    bool no_error = true;
    int iResult;
    const char *buf = string.c_str();
    int toWrite = (int)string.size();
    
    do
    {
        iResult = SSL_write(ssl, buf, toWrite);
        switch(SSL_get_error(ssl, iResult))
        {
            case SSL_ERROR_NONE:
                toWrite -= iResult;
                buf += iResult;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
                break;
            case SSL_ERROR_WANT_CONNECT:
            case SSL_ERROR_WANT_ACCEPT:
            case SSL_ERROR_WANT_X509_LOOKUP:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                no_error = false;
                break;
        }
    }
    while (iResult > 0 && toWrite > 0 && no_error);
    return iResult;
}

int mod_ssl::recv(std::string &buf)
{
    bool no_error = true;
    int iResult = 0;
    char bb[1025];
    do
    {
        iResult = SSL_read(ssl, bb, 1024);
        switch(SSL_get_error(ssl, iResult))
        {
            case SSL_ERROR_NONE:
                bb[iResult] = 0;
                buf += bb;
            case SSL_ERROR_ZERO_RETURN:
            case SSL_ERROR_WANT_READ:
                break;
            case SSL_ERROR_WANT_WRITE:
            case SSL_ERROR_WANT_CONNECT:
            case SSL_ERROR_WANT_ACCEPT:
            case SSL_ERROR_WANT_X509_LOOKUP:
            case SSL_ERROR_SYSCALL:
            case SSL_ERROR_SSL:
            default:
                no_error = false;
                break;
        }
    }
    while (iResult > 0 && iResult < 1024 && no_error && SSL_pending(ssl) > 0);
    return iResult;
}

void mod_ssl::postConnexion (apimeal::IConnexion *con, apimeal::Error &e)
{
    
    int iResult;
    bool no_error = true;
    
    if (con->getPort() == 8484)
    {
        this->sslEnabled = true;
        // Initializing the SSL Method
        ctx = SSL_CTX_new(SSLv23_server_method());
        if (!ctx)
        {
            return;
        }
        
        //FIXME we must get the certificates path from the configuration!
        // Load the certificate and the private key
        if (SSL_CTX_use_certificate_file(ctx, "/Users/Jordan/ssl/server.cr", SSL_FILETYPE_PEM) < 1)
        {
            this->sslEnabled = false;
            return;
        }
        if (SSL_CTX_use_PrivateKey_file(ctx, "/Users/Jordan/ssl/server.key.unsecur", SSL_FILETYPE_PEM) < 1)
        {
            this->sslEnabled = false;
            return;
        }
        
        // Creating SSL Structure
        ssl = SSL_new(ctx);
        if (!ssl)
        {
            this->sslEnabled = false;
            return;
        }
        
        
        if (SSL_set_fd(ssl, con->getSocket()) < 1)
        {
            this->sslEnabled = false;
            return;
        }
        
        // Handshake (is blocking if underlying socket is blocking!!)
        do
        {
            iResult = SSL_accept(ssl);
            switch(SSL_get_error(ssl, iResult))
            {
                case SSL_ERROR_NONE:
                case SSL_ERROR_ZERO_RETURN:
                case SSL_ERROR_WANT_READ:
                    break;
                case SSL_ERROR_WANT_WRITE:
                    break;
                case SSL_ERROR_WANT_CONNECT:
                case SSL_ERROR_WANT_ACCEPT:
                case SSL_ERROR_WANT_X509_LOOKUP:
                case SSL_ERROR_SYSCALL:
                case SSL_ERROR_SSL:
                default:
                    this->sslEnabled = false;
                    no_error = false;
                    break;
            }
        }
        while (iResult < 0 && no_error);
        std::string content;
        this->recv(content);
        con->setRequest(content);
        con->setSocket(-1);
    }
    else
        this->sslEnabled = false;
}

void mod_ssl::preParseRequest(apimeal::IHttpRequest *, apimeal::Error &){}

void mod_ssl::postParseRequest (apimeal::IHttpRequest *, apimeal::Error &){}

void mod_ssl::contentModule (apimeal::IHttpRequest *req, apimeal::Error &e)
{}


void mod_ssl::CGIModule (apimeal::IHttpRequest *resp, apimeal::Error &e)
{}

void mod_ssl::postGenerateResponse (apimeal::IHttpResponse *resp, apimeal::Error &)
{}

void mod_ssl::preSendRequest (apimeal::IHttpResponse *resp, apimeal::Error &e)
{
    if (this->sslEnabled)
    {
        std::map<std::string, std::string>::const_iterator ite;
        ite = resp->getHeaders().begin();
        std::ostringstream oss;
        oss << "HTTP/1.1 " << resp->getStatusCode() << " " << resp->getReasonPhrase() << "\n";
        this->send(oss.str());
        while (ite != resp->getHeaders().end())
        {
            oss.clear();
            oss << ite->first << ": " << ite->second << "\n";
            this->send(oss.str());
            ++ite;
        }
        this->send("\n");
        this->send(resp->getBody());
        this->send("\n");
    }
}

void mod_ssl::release (){}


extern "C" DLLAPIMEAL	apimeal::AModule*	LoadModule(apimeal::ILogger *log)
{
    return (new mod_ssl(log));
}
