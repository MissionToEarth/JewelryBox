//
//  plist_reader.h
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#ifndef plist_reader_h
#define plist_reader_h

#include <string.h>

class Plist
{
public:
    Plist() = default;
    ~Plist() = default;

    int Readfile(const std::string &filepath);
};

#endif /* plist_reader_h */
