//
//  HttpRequest.cpp
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 29/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#include "HttpRequest.h"

void HttpRequest::setRequestURI(const std::string &request){
     this->_requestUrl = request;
}

void HttpRequest::setMethod (std::string const &method){
    this->_method = method;
}

std::string const & HttpRequest::getMethod () const{
    return this->_method;
}

std::string const & HttpRequest::getRequestURI () const{
    return this->_requestUrl;
}

void HttpRequest::setBody (std::string const &body){
    this->_body = body;
}

std::string const & 	HttpRequest::getBody () const{
    return this->_body;
}

std::map< std::string,
std::string > const & 	HttpRequest::getHeaders () const{
    return this->_headers;
}

void HttpRequest::addHeader (std::string const &key, std::string const &value){
    this->_headers[key] = value;
}

void HttpRequest::setHeaders (std::map< std::string, std::string > const &headers){
    this->_headers = headers;
}

void HttpRequest::removeHeader (std::string const &key){
    this->_headers.erase(key);
}

void HttpRequest::setHttpVersion(const std::string &version){
    this->_httpVersion = version;
}

const std::string &HttpRequest::getHttpVersion() const{
    return this->_httpVersion;
}