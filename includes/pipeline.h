//
//  pipeline.h
//  ZiaRef
//
//  Created by Jordan Van Walleghem on 29/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#ifndef __ZiaRef__pipeline__
#define __ZiaRef__pipeline__

#include <iostream>
#include "IConnexion.hpp"
#include "Error.hpp"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "ModuleLoader.hpp"

class pipeline {
    
    apimeal::IConnexion *_client;
    apimeal::Error *_error;
    HttpRequest *_request;
    HttpResponse *_response;
    ModuleLoader *_moduleLoader;
    
    void setExtensionHeader(const std::string &ext);
    bool __continue;
    std::string fileGetContent(const std::string &fileName);
    std::string findDocRoot();
    void readRequest();
    void postConnexion();
    void parseRequest();
    void getContent();
    void preSendResponse();
    void preGenerateResponse();
    void postGenerateResponse();
    void generateResponse();
    void sendResponse();
    bool _continue();
    std::string genDate();
    void getPostBody();

    void preParseRequest();

    void postParseRequest();
    
    bool requestIsComplete(std::string &);
    void writeToSocket(const std::string &content, SOCKET socket);
    void writeHeaderToSocket(const std::string &key, const std::string &value, SOCKET socket);
public:
    
    pipeline(apimeal::IConnexion *, ModuleLoader *moduleLoader);
    void run();
    
};

#endif /* defined(__ZiaRef__pipeline__) */
