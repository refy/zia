//
//  HttpRequest.h
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 29/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#ifndef __ZiaRef__HttpRequest__
#define __ZiaRef__HttpRequest__

#include <iostream>
#include "IHttpRequest.hpp"

class HttpRequest : public apimeal::IHttpRequest {
    
    std::string _method;
    std::string _requestUrl;
    std::string _httpVersion;
    std::string _body;
    std::map<std::string, std::string> _headers;
    
    
public:
    
    virtual void setRequestURI(const std::string &request);
    virtual void setMethod (std::string const &);
    
    virtual std::string const & 	getMethod () const;
    
    virtual std::string const & 	getRequestURI () const;
    
    virtual void 	setBody (std::string const &);
    
    virtual std::string const & 	getBody () const;
    
    virtual std::map< std::string,
    std::string > const & 	getHeaders () const;
    
    virtual void 	addHeader (std::string const &key, std::string const &value);
    virtual void 	setHeaders (std::map< std::string, std::string > const &headers);
    virtual void 	removeHeader (std::string const &key);
    
    void setHttpVersion(const std::string &);
    const std::string &getHttpVersion() const;
    
};

#endif /* defined(__ZiaRef__HttpRequest__) */
