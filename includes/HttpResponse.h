//
//  HttpResponse.h
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 30/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#ifndef __ZiaRef__HttpResponse__
#define __ZiaRef__HttpResponse__

#include <iostream>
#include "IHttpResponse.hpp"

class HttpResponse : public apimeal::IHttpResponse {
    
    int _statusCode;
    std::string _reasonPhrase;
    std::string _httpVersion;
    std::string _body;
    std::map<std::string, std::string> _headers;
    
    
public:
    
    HttpResponse();
    
    virtual void setReasonPhrase(const std::string &);
    virtual void setStatusCode (int);
    
    virtual int 	getStatusCode () const;
    
    virtual std::string const & 	getReasonPhrase () const;
    
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

#endif /* defined(__ZiaRef__HttpResponse__) */
