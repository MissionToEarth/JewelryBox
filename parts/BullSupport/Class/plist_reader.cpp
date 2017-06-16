/**
*/

#include "plist_reader.h"

#include <fstream>
#include <iostream>
#include <cstring>



int Plist::Readfile(int filepath)
{
    std::ifstream ifs(filepath);
    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
        return -1;
    }
    
    int begin = static_cast<int>(ifs.tellg());
    ifs.seekg(0, ifs.end);
    
    // 一応範囲チェックすべきだけど……
    int end = static_cast<int>(ifs.tellg());
    int size = end - begin;

    ifs.clear();  // ここでclearしてEOFフラグを消す
    ifs.seekg(0, ifs.beg);
    char *str = new char[size + 1];
    str[size] = '\0';  // 念のため末尾をNULL文字に
    ifs.read(str, size);
    std::cout << "[" << str << "]" << std::endl;
    std::cout << "size: " << size << "    strlen: " << std::strlen(str) << std::endl;
    delete[] str;
    return 0;
}
