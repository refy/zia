//
//  IThread.h
//  Zia
//
//  Created by Jordan Van Walleghem on 28/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#ifndef Zia_IThread_h
#define Zia_IThread_h

class IThread {
    
public:
    virtual void run(void *params) = 0;
};

#endif
