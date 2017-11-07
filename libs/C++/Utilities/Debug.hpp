//
//  Debug.hpp
//  BULL
//
//  Created by t-harada on 2017/11/07.
//
//

#ifndef Debug_hpp
#define Debug_hpp

//#include "cocos2d.h"
//#include <stdio.h>


extern int g_cnt;

void dump_backtrace(const std::string& str = "");


struct Debug
{
public:
    enum STATE : short
    {
        Default,
        AsyncLoad
    };
    
public:
    static std::shared_ptr<Debug> getInstance(){
        if (!instance) {
            CCLOG("Debug getInstance in if{}: %d" , g_cnt++);
            instance.reset(new Debug());
        }
        return instance;
    };
    
    STATE state;
    
public:
    ~Debug(){};
private:
    Debug()
    :state(Default)
    {};
    
    static std::shared_ptr<Debug> instance;
};

#endif /* Debug_hpp */
