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
}

#endif /* StringUtilties_hpp */
