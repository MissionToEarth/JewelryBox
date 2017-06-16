//
//  plist_reader.h
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#ifndef plist_reader_h
#define plist_reader_h

class Plist
{
public:
    Plist() = default;
    ~Plist() = default;
public:
    int Readfile(const char *filepath);
    int Readfile(const std::string &filepath);
};

#endif /* plist_reader_h */
