//
//  Thread.h
//  Zia
//
//  Created by Jordan Van Walleghem on 28/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#ifndef __Zia__Thread__
#define __Zia__Thread__

#include <iostream>
#include "IThread.h"

class Thread : public IThread {

    void *(*_function_ptr)(void *);
    
public:
    Thread(void *(*start_routine)(void *));
    virtual void run(void *params);
};

#endif /* defined(__Zia__Thread__) */
