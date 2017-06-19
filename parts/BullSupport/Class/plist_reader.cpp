/**
*/

#include "plist_reader.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <assert.h>

using namespace std;


int Plist::ReadFile(const char* filepath)
{
    std::ifstream ifs(filepath);
    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
        assert(false);
        return -1;
    }
    
    //バッファ
    m_source = std::string((std::istreambuf_iterator<char>(ifs))
                           , std::istreambuf_iterator<char>());
    std::cout << "[" << m_source << "]" << std::endl;
    return 0;
}


void func(std::ifstream ifs)
{
    bool key_state = false;
    std::string key_buf("");
    std::string line_buffer("");
    while (!ifs.eof())
    {
        std::getline(ifs, line_buffer);
        printf("%s\n", line_buffer.c_str());
        
        if (!key_state)
        {
            size_t front_pos = line_buffer.find_first_not_of(TAG_KEY);
            if (front_pos != std::string::npos)
            {
                key_state = true;
                size_t end_pos = line_buffer.find(TAG_KEY_CLOSE);
                if (end_pos != std::string::npos)
                {
                    end_pos = line_buffer.length();
                }
                string sub = line_buffer.substr(front_pos, end_pos);
                key_buf.insert(0, sub);
            }
        }
        else
        {
            size_t end_pos = line_buffer.find(TAG_KEY_CLOSE);
            if (end_pos != std::string::npos)
            {
                end_pos = line_buffer.length();
            }
            string sub = line_buffer.substr(0, end_pos);
            key_buf += sub;
        }
        
    }
    ifs.seekg(0, ios_base::beg);
    
    
    std::getline(ifs, line_buffer);
    std::ofstream ofs("/Users/t-harada/Documents/d3_develop/output.plist");
    ofs << line_buffer;
    
    //探す移動する、　コンフリクトか<key>まで
    // key value　に分解する
    //　コンフロクトがある場合は、不可能。。。
    
}

void Plist::Move(std::ifstream &target, const std::string &dest_key)
{
    
}
