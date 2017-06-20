/**
 */

#include "LocalizedPlist.h"
#include "macros.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <assert.h>

using namespace std;


namespace LocalizedPlist
{
    void DumpPairs(Plist::ASSOCIATIVE_MAP pairs)
    {
        for (auto v : pairs)
        {
            LOG("key= %s\nvalue= %s", v.first.c_str(), v.second.c_str());
        }
    }

    
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
            
            m_values.insert(std::make_pair(key, value));
        }
        
        DumpPairs(m_values);
        
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
    
    /** 以下の形式が繰り返しているものに対応する。コンフリクトがある場合には対応していない。
        <key>xxx</key>\n
        <string>xxxxx</string>\n    */
    Plist::ASSOCIATIVE_MAP Plist::MakePairs(const std::string &source)
    {
        ASSOCIATIVE_MAP pairs({});
        
        //nposが出ない想定でチェック。
        auto check = [](string::size_type n){
            if (n == string::npos)
            {
                assert(false);
            }
        };
        
        string key("");
        string value("");
        string::size_type close_n = 0;
        for (string::size_type n = 0; (n = source.find(TAG_KEY, n)) != string::npos; n++)
        {
            //コンフリクトに未対応。
            n += strlen(TAG_KEY);
            close_n = source.find(TAG_KEY_CLOSE, n);
            check(close_n);
            key = source.substr(n, close_n - n);
            
            n = source.find(TAG_VALUE, n);
            check(n);
            n += strlen(TAG_VALUE);
            close_n = source.find(TAG_VALUE_CLOSE, n);
            check(close_n);
            value = source.substr(n, close_n - n);
            
            pairs.insert(std::make_pair(key, value));
        }
        
        
        return pairs;
    }
    
    std::string Plist::GetConflictUnit(const std::string &source, std::string::size_type cur_pos)
    {
        string::size_type pos = source.find(TAG_CONFLICT_HEAD, cur_pos);
        string::size_type end = source.find(TAG_CONFLICT_END, pos);
        pos = source.find("\n", pos) + strlen("\n");
        string ret = source.substr(pos, end - pos);
        
        LOG("%s", ret.c_str());
        return ret;
    }
    
    std::string GetConflictPart(const std::string &conflict_unit, bool part)
    {
        LOG("%s", __PRETTY_FUNCTION__);
        
        string::size_type begin = 0;
        if (conflict_unit.find(TAG_CONFLICT_HEAD) != string::npos)
        {
            
            LOG("conflict開始行を削除しないとヤカン。");
            assert(false);
            exit(EXIT_FAILURE);
        }

        string::size_type mid_pos = conflict_unit.find(TAG_CONFLICT_MID);
        if (part)
        {
            //HEAD部取得
            string head = conflict_unit.substr(begin, mid_pos);
            
            LOG("%s", head.c_str());
            return head;
        }
        else
        {
            
            //相手の変更部取得
            mid_pos += strlen(TAG_CONFLICT_MID);
            string changed = conflict_unit.substr(mid_pos);
            
            LOG("%s", changed.c_str());
            return changed;
        }
    }

    
#pragma mark - テスト
    /** テスト用データ */
    const char* TEST_DATA = R"(<plist version="1.0">
    <dict>
    <key>OK</key>
    <string>OK</string>
    <<<<<<< HEAD
    <key>CANCEL</key>
    <string>キャンセル</string>
    =======
    <key>CANCELなろう</key>
    <string>あかん</string>
    >>>>>>> issue3
    
    <<<<<<< HEAD
    <key>BLADE</key>
    <string>ブレード</string>
    =======
    <key>BLADE</key>
    <string>ブレード</string>
    >>>>>>> issue3
    
    <key>Z02（国内版の変更を残す。）</key>
    <<<<<<< HEAD
    <string>睡眠不足バスター</string>
    =======
    <string>Z-MAN</string>
    >>>>>>> issue3
    
    <key>Z02（汚い変更の場合）</key>
    <<<<<<< HEAD
    <string>睡眠不足バスター</string>
    =======
    <string>Z-MAN</string>
    >>>>>>> issue3
    
    </dict>
    </plist>)";
    
    void Plist::Test()
    {
        Plist p;
        string conflict_01 = p.GetConflictUnit(TEST_DATA, 0);
        
        ASSOCIATIVE_MAP changed = p.MakePairs(GetConflictPart(conflict_01, false));
        ASSOCIATIVE_MAP head = p.MakePairs(GetConflictPart(conflict_01, true) );
        DumpPairs(head);
        DumpPairs(changed);
        
        assert(false);
        
    }
}
