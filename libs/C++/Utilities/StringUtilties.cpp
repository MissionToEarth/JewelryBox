//
//  StringUtilties.cpp
//  BullSupport
//
//  Created by t-harada on 2017/06/20.
//
//

#include "StringUtilties.hpp"
#include <cstdio>


using namespace std;

namespace StringHelper
{
    void Move(std::ifstream &target, const std::string &dest_key)
    {
        
    }
}

void split(char** buf, size_t buf_size, const char* str, const char* delimiter)
{
    //文字コードに注意。
    
}

std::vector<std::string> split(const std::string& str
                               , const std::string& delimiter)
{
    //読み込みストリーム
    istringstream iss(str);
    string tmp;
    vector<string> res;
    while(getline(iss, tmp, delimiter)){
        res.push_back(tmp);
    }
    return res;
}

std::vector<std::string> split(const string &str, char delimiter){
    vector<string> res;
    size_t current = 0, found;
    while((found = str.find_first_of(delimiter, current)) != string::npos){
        res.push_back(string(str, current, found - current));
        current = found + 1;
    }
    res.push_back(string(str, current, str.size() - current));
    return res;
}



////ifstreamとofstreamのテスト　メモリに余裕があれば、全部読み込んでから処理するで良い。
//void func(std::ifstream ifs)
//{
//    bool key_state = false;
//    std::string key_buf("");
//    std::string line_buffer("");
//    while (!ifs.eof())
//    {
//        std::getline(ifs, line_buffer);
//        printf("%s\n", line_buffer.c_str());
//        
//        if (!key_state)
//        {
//            size_t front_pos = line_buffer.find_first_not_of(TAG_KEY);
//            if (front_pos != std::string::npos)
//            {
//                key_state = true;
//                size_t end_pos = line_buffer.find(TAG_KEY_CLOSE);
//                if (end_pos != std::string::npos)
//                {
//                    end_pos = line_buffer.length();
//                }
//                string sub = line_buffer.substr(front_pos, end_pos);
//                key_buf.insert(0, sub);
//            }
//        }
//        else
//        {
//            size_t end_pos = line_buffer.find(TAG_KEY_CLOSE);
//            if (end_pos != std::string::npos)
//            {
//                end_pos = line_buffer.length();
//            }
//            string sub = line_buffer.substr(0, end_pos);
//            key_buf += sub;
//        }
//        
//    }
//    ifs.seekg(0, ios_base::beg);
//    
//    
//    std::getline(ifs, line_buffer);
//    std::ofstream ofs("/Users/t-harada/Documents/d3_develop/output.plist");
//    ofs << line_buffer;
//    
//    //探す移動する、　コンフリクトか<key>まで
//    // key value　に分解する
//    //　コンフロクトがある場合は、不可能。。。
//    
//}
