//
//  HttpResponse.cpp
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 30/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#include "HttpResponse.h"

HttpResponse::HttpResponse():
    _statusCode(200), _reasonPhrase("OK")
{}

void HttpResponse::setReasonPhrase(const std::string &reason){
    this->_reasonPhrase = reason;
}

void HttpResponse::setStatusCode (int code){
    this->_statusCode = code;
}

int 	HttpResponse::getStatusCode () const{
    return this->_statusCode;
}

std::string const & 	HttpResponse::getReasonPhrase () const{
    return this->_reasonPhrase;
}

void HttpResponse::setBody (std::string const &body){
    this->_body = body;
}

std::string const & 	HttpResponse::getBody () const{
    return this->_body;
}

std::map< std::string,
std::string > const & 	HttpResponse::getHeaders () const{
    return this->_headers;
}

void HttpResponse::addHeader (std::string const &key, std::string const &value){
    this->_headers[key] = value;
}

void HttpResponse::setHeaders (std::map< std::string, std::string > const &headers){
    this->_headers = headers;
}

void HttpResponse::removeHeader (std::string const &key){
    this->_headers.erase(key);
}

void HttpResponse::setHttpVersion(const std::string &version){
    this->_httpVersion = version;
}

const std::string &HttpResponse::getHttpVersion() const{
    return this->_httpVersion;
}