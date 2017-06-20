//
//  main.cpp
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#include "LocalizedPlist.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

void Test()
{
    LocalizedPlist::Plist::Test();
}

int main(int argc, const char * argv[])
{
    printf("%s\n", argv[0] );
    
    Test();
    
    LocalizedPlist::Plist p;
    std::string str("/Users/t-harada/Documents/d3_develop/Resouce/conflict_tmp.plist");
    p.Parse(str.c_str());
    
    
    
    //プログラム一旦止めるため、cinさせる。
    int n=0;
    std::string s;
    std::cin >> n >> s;
    printf("%d,%s", n, s.c_str());

    return 0;
}
