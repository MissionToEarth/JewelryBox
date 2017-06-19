//
//  main.cpp
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#include "plist_reader.h"

#include <iostream>
#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    printf("%s\n", argv[0] );
    
    Plist p;
    std::string str("/Users/t-harada/Documents/d3_develop/Resouce/conflict_tmp.plist");
    p.ReadFile(str.c_str());
    
    
    
    //プログラム一旦止めるため、cinさせる。
    int n=0;
    std::string s;
    std::cin >> n >> s;
    printf("%d,%s", n, s.c_str());

    return 0;
}
