//
//  Thread.cpp
//  Zia
//
//  Created by Jordan Van Walleghem on 28/01/14.
//  Copyright (c) 2014 Jordan Van Walleghem. All rights reserved.
//

#include "Thread.h"

Thread::Thread(void *(*start_routine)(void *))
{
    this->_function_ptr = start_routine;
}

void Thread::run(void *params)
{
    pthread_t ta;
    
    pthread_create(&ta, NULL, this->_function_ptr, params);
}