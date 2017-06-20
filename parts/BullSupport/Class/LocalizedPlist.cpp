/**
*/

#include "plist_reader.h"
#include "macros.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <assert.h>

using namespace std;

namespace BULL_LocalizedPlist
{



#include <cstdio>
std::string parse_c(const char *filepath)
{
    FILE *fp;
    char s[256];
    char *c_pPos;
    
    if ((fp = fopen(filepath, "r")) == NULL)
    {
        printf("file open error!!\n");
        exit(EXIT_FAILURE);	/* エラーの場合は通常、異常終了する */
    }
    
    //　一旦
    bool conflict_dirty = false;//コンフリクトがある物かどうか。
    enum class STATE : int { READ, };
    STATE state = STATE::READ; //実行状態
    
    while (fgets(s, 256, fp) != NULL)
    {
        /* ここではfgets()により１行単位で読み出し */
        printf("%s", s);
        
        c_pPos = strstr(s, TAG_CONFLICT_HEAD);
        if (c_pPos != NULL)
        {
            //コンフリクト　開始行
            conflict_dirty = false;
        }
        c_pPos = strstr(s, TAG_CONFLICT_MID);
        if (c_pPos != NULL)
        {
            
        }
        c_pPos = strstr(s, TAG_CONFLICT_END);
        if (c_pPos != NULL)
        {
            //コンフリクト　終了行
        }
        
        c_pPos = strstr(s, TAG_KEY);
        if (c_pPos != NULL)
        {
            
        }
        c_pPos = strstr(s, TAG_KEY_CLOSE);
        if (c_pPos != NULL)
        {
            
        }
        c_pPos = strstr(s, TAG_VALUE);
        if (c_pPos != NULL)
        {
            
        }
        c_pPos = strstr(s, TAG_VALUE_CLOSE);
        if (c_pPos != NULL)
        {
            
        }
    }
    
    fclose(fp);
    
    return 0;
}




int Plist::Parse(const std::string &filepath)
{
    int ret = ReadFile(filepath.c_str());
    if ( ret != 0)
    {
        LOG_WARN("読み込み失敗 : %s", filepath.c_str());
        assert(false);
        exit(EXIT_FAILURE);
    }
    string source = m_source;
    
    string key("");
    string value("");
    string::size_type close_n = 0;
    for (string::size_type n = 0; (n = source.find(TAG_KEY, n)) != string::npos; n++)
    {
        //コンフリクトに未対応。
        n += strlen(TAG_KEY);
        close_n = source.find(TAG_KEY_CLOSE, n);
        key = source.substr(n, close_n - n);
        
        n = source.find(TAG_VALUE, n);
        n += strlen(TAG_VALUE);
        close_n = source.find(TAG_VALUE_CLOSE, n);
        value = source.substr(n, close_n - n);
        
        cout << n << " : " << close_n << " : " << key << " : " << value << endl;

        m_values.insert(std::make_pair(key, value));
    }

    for (auto v : m_values)
    {
        LOG("key= %s\nvalue= %s", v.first.c_str(), v.second.c_str());
    }

    return 0;
}

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
    LOG("[%s]", m_source.c_str());
    
    return 0;
}

}
