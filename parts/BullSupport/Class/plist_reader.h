//
//  plist_reader.h
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#ifndef plist_reader_h
#define plist_reader_h

#include <iostream>
#include <unordered_map>
#include <string.h>

#define TAG_KEY  R"(<key>)"
#define TAG_KEY_CLOSE  R"(</key>)"
#define TAG_VALUE  R"(<string>)"
#define TAG_VALUE_CLOSE  R"(</string>)"


class Plist
{
public:
    using ASSOCIATIVE_MAP = std::unordered_map<std::string, std::string>();

public:
    ASSOCIATIVE_MAP  m_values;
    std::string m_source;
    
public:
    Plist() = default;
    ~Plist() = default;

//    int Readfile(const std::string &filepath);
    int ReadFile(const char* filepath);

    
    //ファイルポインタの移動
    void Move(std::ifstream &target, const std::string &dest_key);
    
    
};

#endif /* plist_reader_h */
