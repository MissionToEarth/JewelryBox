//
//  StringUtilties.hpp
//  BullSupport
//
//  Created by t-harada on 2017/06/20.
//
//

#ifndef StringUtilties_hpp
#define StringUtilties_hpp

#include <fstream>
#include <string.h>

namespace StringHelper
{
    //ファイルポインタの移動
    void Move(std::ifstream &target, const std::string &dest_key);
    
    /** 文字列を区切る：
        str         対象文字列
        delimiter   区切り文字
     */
    char** split(const char* str, const char* delimiter)
    
    /** 文字列を区切る：
        str         対象文字列
        delimiter   区切り文字
     */
    std::vector<std::string> split(const std::string& str
                                   , const std::string& delimiter);
}

#endif /* StringUtilties_hpp */
