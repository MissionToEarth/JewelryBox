//
//  main.cpp
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#include <iostream>
#include <stdio.h>
#include "plist_reader.h"


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    Plist p;
    std::string str("aaa");
    p.Readfile(str);
    
    
    return 0;
}
