//
//  Debug.cpp
//  BULL
//
//  Created by t-harada on 2017/11/07.
//
//

#include "Debug.hpp"

#include <execinfo.h>



int g_cnt = 0;

void dump_backtrace(const std::string& str)
{
    return;
    
    printf("debug :: -- %s",str.c_str());
    void* callstack[128];
    int i, frames = backtrace(callstack, 128);
    char** strs = backtrace_symbols(callstack, frames);
    for (i = 0; i < frames; ++i) {
        printf("debug :: %s\n", strs[i]);
    }
    free(strs);

}

std::shared_ptr<Debug> Debug::instance = {};
