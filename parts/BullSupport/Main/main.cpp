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

/** 引数を２つ受け取る。 */
int main(int argc, const char * argv[])
{
    if (argc < 2)
    {
        DDD_LOG("引数が足りない。localized用plistファイルへのパスを教えてください。");
        exit(EXIT_FAILURE);
    }
    
    int i;
    for(i=0; i<argc; i++)
    {
        DDD_LOG("%s", argv[i]);
    }
    
    
//    Test();
    
    LocalizedPlist::Plist p;
    p.Resolve(argv[1]);

    return 0;
}
