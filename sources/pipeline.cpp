//
//  pipeline.cpp
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 29/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#include "pipeline.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include "ConfParser.hpp"

pipeline::pipeline(apimeal::IConnexion *client):
_client(client), __continue(true)
{}

void pipeline::parseRequest(){
    //preParse
    std::string request = this->_client->getRequest();
    this->_request->setMethod(request.substr(0, request.find(' ')));
    request = request.substr(request.find(' ') + 1);
    this->_request->setRequestURI(request.substr(0, request.find(' ')));
    request = request.substr(request.find(' ') + 1);
    this->_request->setHttpVersion(request.substr(0, request.find('\n') - 1));
    request = request.substr(request.find('\n') + 1);
    while (request.size())
    {
        std::string param = request.substr(0, request.find('\n'));
        if (param.size() > 0)
            this->_request->addHeader(param.substr(0, param.find(':')), param.substr(param.find(':') + 1));
        request = request.substr(request.find('\n') + 1);
    }
    //postParse
}

std::string pipeline::findDocRoot()
{
    std::string docRoot = "";
    
    docRoot = ConfParser::getInstance()->getDocumentRoot(this->_request->getHeaders().find("Host")->second);
    if (docRoot.size() <= 0)
        docRoot = ConfParser::getInstance()->getDocumentRoot("*");
    if (docRoot.size() <= 0 && ConfParser::getInstance()->getVirtualHost().size() > 0)
        docRoot = ConfParser::getInstance()->getDocumentRoot(ConfParser::getInstance()->getVirtualHost()[0]);
    if (docRoot.size() <= 0)
    {
        this->_error->IsError = true;
        this->_error->Message = "Bad request";
        this->_error->Code = 400;
    }
    return docRoot;
}

std::string pipeline::fileGetContent(const std::string &fileName)
{
    char buffer[256];
    long readed;
    std::string content;
    std::string realFile = this->findDocRoot() + fileName;
    
    if (this->_error->IsError == false)
    {
        int fd = open(realFile.c_str(), O_RDONLY);
        if (fd < 0)
        {
            this->_response->setStatusCode(404);
            this->_response->setReasonPhrase("Not Found");
        }
        else
        {
            do {
                readed = read(fd, buffer, 255);
                if (readed > 0)
                {
                    buffer[readed] = 0;
                    content += buffer;
                }
            } while (readed >= 255);
        }
        close(fd);
    }
    return content;
}

void pipeline::getPostBody()
{
    int bodySize = atoi(this->_request->getHeaders().find("Content-Length")->second.c_str());
    std::cout << "Host " << this->_request->getHeaders().find("Host")->second << std::endl;
    std::cout << "BodySize " << bodySize << std::endl;
    int pos = 0;
    char buffer[1025];
    long readed = 0;
    std::string body;
    
    
    do
    {
        if (bodySize - pos >= 1024)
            readed = read(this->_client->getSocket(), buffer, 1024);
        else
            readed = read(this->_client->getSocket(), buffer, bodySize - pos);
        buffer[readed] = 0;
        body += buffer;
        pos += readed;
    } while (pos < bodySize && readed > 0);
    
    this->_request->setBody(body);
}

void pipeline::getContent()
{
    if (this->_request->getMethod() == "POST")
    {
        if (this->_request->getHeaders().find("Content-Length") != this->_request->getHeaders().end())
        {
            this->getPostBody();
        }
    }
    // contentModule
}

#include <time.h>

std::string pipeline::genDate()
{
    char buffer[512];
    std::string ret;
    time_t temps;
    
    time(&temps);
    strftime(buffer, 511, "%a, %d %b %Y %H:%M:%S", gmtime(&temps));
    ret = buffer;
    ret += " GMT";
    return ret;
}

#include <sstream>

void pipeline::generateResponse()
{
    //CGI
    if (this->_error->IsError == false &&
        (this->_request->getMethod() == "GET" || this->_request->getMethod() == "POST" ||
         this->_request->getMethod() == "HEAD"))
        this->_response->setBody(this->fileGetContent(this->_request->getRequestURI()));
    this->_response->addHeader("Date", this->genDate());
    std::ostringstream oss;
    oss << this->_response->getBody().size();
    this->_response->addHeader("Content-Length", oss.str());
    if (this->_request->getMethod() == "HEAD")
        this->_response->setBody("");
    //post
}

void pipeline::writeToSocket(const std::string &content, SOCKET socket)
{
    const char *toWrite = content.c_str();
    unsigned long length = content.size();
    int pos = 0;
    
    while (pos < length)
    {
        if (length - pos >= 2048)
            write(socket, toWrite + pos, 2048);
        else
            write(socket, toWrite + pos, length - pos);
        pos += 2048;
    }
}

void pipeline::writeHeaderToSocket(const std::string &key, const std::string &value, SOCKET socket)
{
    std::string header = key;
    header += ": ";
    header += value;
    header += "\n";
    this->writeToSocket(header, socket);
}

void pipeline::sendResponse()
{
    std::map<std::string, std::string>::const_iterator ite;
    
    ite = this->_response->getHeaders().begin();
    std::ostringstream oss;
    oss << "HTTP/1.1 " << this->_response->getStatusCode() << " " << this->_response->getReasonPhrase() << "\n";
    writeToSocket(oss.str(), this->_client->getSocket());
    while (ite != this->_response->getHeaders().end())
    {
        writeHeaderToSocket(ite->first, ite->second, this->_client->getSocket());
        ++ite;
    }
    writeToSocket("\n", this->_client->getSocket());
    writeToSocket(this->_response->getBody(), this->_client->getSocket());
    writeToSocket("\n", this->_client->getSocket());
    //end
}

bool pipeline::_continue(){
    return this->__continue;
}

bool pipeline::requestIsComplete(const std::string &request)
{
//    std::cout << request << std::endl;
    if (request.find("\r\n\r\n") != request.npos || request.find("\n\n") != request.npos)
        return true;
    return false;
}

void pipeline::readRequest()
{
    std::string request;
    long readed = 0;
    char buffer[256];

    do
    {
        readed = read(this->_client->getSocket(), buffer, 255);
        if (readed > 0)
        {
            buffer[readed] = 0;
            request += buffer;
        }
    } while ((readed >= 255 || this->requestIsComplete(request) == false) && readed > 0);
    if (request.size() == 0)
        this->__continue = false;
    std::cout << request << std::endl;
    this->_client->setRequest(request);
}

void pipeline::postConnexion(){
    //postConnexionhook
    if (this->_client->getRequest().size() <= 0)
        this->readRequest();
}

void pipeline::run(){
    while (this->_continue())
    {
        this->_error = new apimeal::Error;
        this->_response = new HttpResponse;
        this->_request = new HttpRequest;
        this->postConnexion();
        this->parseRequest();
        this->getContent();
        this->generateResponse();
        this->sendResponse();
        delete this->_response;
        delete this->_request;
        delete this->_error;
        this->_client->setRequest("");
    }
    std::cout << "Connexion closed" << std::endl;
    close(this->_client->getSocket());
}