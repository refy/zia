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
#include "AModule.hpp"
#include "Logger.hpp"
#include "ModuleLoader.hpp"

pipeline::pipeline(apimeal::IConnexion *client, ModuleLoader *moduleLoader):
_client(client), __continue(true), _moduleLoader(moduleLoader)
{
//    this->_moduleLoader = new ModuleLoader(ConfParser::getInstance()->getModulesPath(), *this->_error, NULL);
}

void pipeline::preParseRequest()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::PREPARSEREQUEST)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::PREPARSEREQUEST).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::PREPARSEREQUEST).end(); ++ite)
        {
            (*ite)->preParseRequest(this->_request, *this->_error);
        }
    }
}

void pipeline::postParseRequest()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::POSTPARSEREQUEST)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::POSTPARSEREQUEST).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::POSTPARSEREQUEST).end(); ++ite)
        {
            (*ite)->postParseRequest(this->_request, *this->_error);
        }
    }
}

std::pair<unsigned long, unsigned long> findCRLF(const std::string &string)
{
    std::pair<unsigned long, unsigned long> ret;
    
    if ( (ret.first = string.find("\r\n")) != string.npos)
    {
        ret.second = ret.first + 2;
        return ret;
    }
    if ( (ret.first = string.find('\n')) != string.npos)
    {
        ret.second = ret.first + 1;
        return ret;
    }
    if ( (ret.first = string.find('\r')) != string.npos)
    {
        ret.second = ret.first + 1;
        return ret;
    }
    ret.first = string.npos;
    ret.second = string.npos;
    return ret;
}

std::pair<unsigned long, unsigned long> findS(const std::string &string, const std::string &S)
{
    std::pair<unsigned long, unsigned long> ret;
    
    if ( (ret.first = string.find(S)) != string.npos)
    {
        ret.second = ret.first + S.size();
        return ret;
    }
    ret.first = string.npos;
    ret.second = string.npos;
    return ret;
}

std::string getCRLFLine(std::string &string)
{
    std::string ret;
    std::pair<unsigned long, unsigned long> pos;
    
    pos = findCRLF(string);
    if (pos.first != string.npos)
    {
        ret = string.substr(0, pos.first);
        string = string.substr(pos.second);
        return ret;
    }
    ret = string;
    string = "";
    return ret;
}

bool isHeaderComplete(const std::string &string)
{
    if (string.find("\r\n") == 0 || string.find("\n") == 0 || string.find("\r") == 0)
        return true;
    return false;
}

void pipeline::parseRequest(){
    this->preParseRequest();
    std::string line;
    std::string request = this->_client->getRequest();
    unsigned long pos;
    line = getCRLFLine(request);
    if (line.size())
    {
        if ((pos = line.find(' ')) != line.npos)
        {
            this->_request->setMethod(line.substr(0, pos));
            line = line.substr(pos + 1);
            if ((pos = line.find(' ')) != line.npos)
            {
                this->_request->setRequestURI(line.substr(0, pos));
                this->_request->setHttpVersion(line.substr(pos + 1));
            }
            else
                this->_request->setRequestURI(line);
        }
        else
            this->_request->setMethod(line);
        while (request.size() && isHeaderComplete(request) == false)
        {
            line = getCRLFLine(request);
            if (line.size() > 0 && (pos = line.find(": ")) != line.npos)
            {
                std::string value = line.substr(pos + 2);
                std::string param = line.substr(0, pos);
                this->_request->addHeader(param, value);
            }
        }
    }
    if (this->_request->getHeaders().find("Host") != this->_request->getHeaders().end())
    {
        this->_request->addHeader("RealURI", this->_request->getRequestURI());
        this->_request->setRequestURI(this->findDocRoot() + this->_request->getRequestURI());
    }
    while (request.find("\r") ==0 || request.find("\n") == 0)
    {
        request = request.substr(1);
    }
    this->_client->setRequest(request);
    this->postParseRequest();
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

void pipeline::setExtensionHeader(const std::string &ext)
{
    if (ext.size() > 1)
    {
        if (ext == ".jpg" || ext == ".png" || ext == ".bmp" || ext == ".gif")
        {
            this->_response->addHeader("Content-Type", "image");
        }
    }
    else if (this->_response->getHeaders().find("Content-Type") == this->_response->getHeaders().end()){
        this->_response->addHeader("Content-Type", "text/html");
    }
}

#include <fstream>

std::string pipeline::fileGetContent(const std::string &fileName)
{
    std::string content;
    
    if (this->_error->IsError == false)
    {
        std::ifstream infile;
        infile.open(fileName.c_str());
        if (infile.is_open() == false)
        {
            this->_response->setStatusCode(404);
            this->_response->setReasonPhrase("Not Found");
            this->_error->Code = 404;
            this->_error->Message = "Not Found";
            this->_error->IsError = true;
            std::cout << "PD" << std::endl;
        }
        else
        {
            infile.seekg(0, std::ios::end);
            content.resize(infile.tellg());
            infile.seekg(0, std::ios::beg);
            infile.read(&content[0], content.size());
            infile.close();
            std::string extension;
            if (fileName.rfind('.') != fileName.npos)
                extension = fileName.substr(fileName.rfind("."));
            this->setExtensionHeader(extension);
        }
        infile.close();
    }
    return content;
}

void pipeline::getPostBody()
{
    int bodySize = atoi(this->_request->getHeaders().find("Content-Length")->second.c_str()) - (int)this->_client->getRequest().size();
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
   
    if (body.size())
        this->_client->setRequest(this->_client->getRequest() + body);
    body = this->_client->getRequest().substr(0,  atoi(this->_request->getHeaders().find("Content-Length")->second.c_str()));
    
    this->_request->setBody(body);
}

void pipeline::getContent()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    bool contentModule = false;
    
    if (this->_moduleLoader->getSortedMap().find(apimeal::CONTENTMODULE)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::CONTENTMODULE).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::CONTENTMODULE).end(); ++ite)
        {
            (*ite)->contentModule(this->_request, *this->_error);
            contentModule = true;
        }
    }
    
    if (this->_request->getMethod() == "POST")
    {
        if (this->_request->getHeaders().find("Content-Length") != this->_request->getHeaders().end())
        {
            this->getPostBody();
        }
    }
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

void pipeline::preGenerateResponse()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::CGIMODULE)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::CGIMODULE).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::CGIMODULE).end(); ++ite)
        {
            (*ite)->CGIModule(this->_request, *this->_error);
        }
    }
}

void pipeline::postGenerateResponse()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::POSTGENERATERESPONSE)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::POSTGENERATERESPONSE).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::POSTGENERATERESPONSE).end(); ++ite)
        {
            (*ite)->postGenerateResponse(this->_response, *this->_error);
        }
    }
}

#include <sstream>

void pipeline::generateResponse()
{
    
    this->preGenerateResponse();
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
    this->postGenerateResponse();
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

void pipeline::preSendResponse()
{
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::SENDREQUEST)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::SENDREQUEST).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::SENDREQUEST).end(); ++ite)
        {
            (*ite)->preSendRequest(this->_response, *this->_error);
        }
    }
}

void pipeline::sendResponse()
{
    this->preSendResponse();
    
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

bool pipeline::requestIsComplete(std::string &request)
{
    while (request.find('\n') == 0 || request.find('\r') == 0)
    {
        request = request.substr(0, 1);
    }
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
    this->_client->setRequest(this->_client->getRequest() + request);
}

void pipeline::postConnexion(){
    
    std::vector<apimeal::AModule *>::const_iterator ite;
    if (this->_moduleLoader->getSortedMap().find(apimeal::POSTCONNEXION)
        != this->_moduleLoader->getSortedMap().end())
    {
        for (ite = this->_moduleLoader->getSortedMap().at(apimeal::POSTCONNEXION).begin(); ite != this->_moduleLoader->getSortedMap().at(apimeal::POSTCONNEXION).end(); ++ite)
        {
            (*ite)->postConnexion(this->_client, *this->_error);
        }
    }
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
    close(this->_client->getSocket());
}