/**
 */

#include "LocalizedPlist.h"

#include <fstream>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <assert.h>

using namespace std;
using namespace ALICE;

//  名前空間宣言
NAMESPACE_OPEN(LocalizedPlist)


#pragma mark - 

static void DumpPairs(Plist::ASSOCIATIVE_MAP pairs)
{
    for (auto v : pairs)
    {
        LOG("key= %s\nvalue= %s", v.first.c_str(), v.second.c_str());
    }
}


#pragma mark - Member of Plist

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
    
    
    if (IsConflict(source))
    {
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
    
    //        LOG("%s", ret.c_str());
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

<key>Z03（汚い変更の場合）</key>
<<<<<<< HEAD
<string>睡眠不足バスター</string>
=======
<string>
Z-MAN
</string>
<key>

GoogleEarth
</key>
<string>Who am I?</string>
>>>>>>> issue3
</dict>
</plist>)";



void Plist::Test()
{
    {
    }
    {
        string test("abcdefz");
        LOG("[%s]", test.substr(test.length() - 1).c_str());
        string gust("abcdefあz");
        LOG("[%s]", gust.substr(gust.length() - 1).c_str());
        gust.push_back('\n');
        LOG("末尾に改行追加：[%s]：", gust.c_str());
        LOG("erase:[%s]", gust.erase(1, gust.length()).c_str());
        string east("abcイロハ");
        LOG("[%s]", east.substr(east.length() - 3).c_str());//全角文字の場合は、length()などで考慮されていないので、困る。
    }
    {
        string tmp("aaaaaa\nbbbbbbbbbb\ncccccccccc");
        auto ret01 = FindNextLine(tmp, 0);
        auto ret02 = FindNextLine(tmp, 10);
        LOG("1 [%s]", tmp.substr(ret01).c_str());
        LOG("2 [%s]", tmp.substr(ret02).c_str());
    }
    {
        string test(TEST_DATA);
        EraseFindLine(test, TAG_CONFLICT_HEAD, 0);
        LOG("==erase conflict head==\n[%s]", test.c_str());
        test = std::string(TEST_DATA);
        EraseFindLine(test, TAG_CONFLICT_HEAD, 1);
        EraseFindLine(test, TAG_CONFLICT_END, 1);
        LOG("==erase conflict head mode:1==\n[%s]", test.c_str());
    }
    {
        string tmp = EraseConflictSymbols(TEST_DATA);
        LOG("==EraseConflictSymbols==\n[%s]", tmp.c_str());
    }
    
    Plist p;
    string conflict_01 = p.GetConflictUnit(TEST_DATA, 0);
    LOG("==GetConflictUnit==\n[%s]", conflict_01.c_str());
    
    ASSOCIATIVE_MAP changed = p.MakePairs(GetConflictPart(conflict_01, false));
    ASSOCIATIVE_MAP head = p.MakePairs(GetConflictPart(conflict_01, true) );
    DumpPairs(head);
    DumpPairs(changed);
    
    LOG(IsContainsDuplicate(head, changed) ? "重複している　key　がある" : "重複していない key はそれぞれ");
    LOG(ComparePairs(head, changed) ? "keyはバラバラ、数は一致" : "意図しない状態");
    
    assert(false);
}


#pragma mark - ヘルパーメソッド

bool IsConflict(const std::string &source)
{
    auto pos = source.find(TAG_CONFLICT_HEAD);
    if (pos == string::npos)
    {
        return false;
    }
    auto front = FindLineFrontWithPosition(source, pos);
    if (pos == front)
    {
        return true;
    }
    
    return false;
}


void ReplaceWithRange(std::string &source, std::string::size_type begin, std::string::size_type end, const std::string replace)
{
    source.replace(begin, end - begin, replace);
}


std::string::size_type FindLineFrontWithPosition(const std::string &source, std::string::size_type pos)
{
    auto front = source.rfind("\n", pos);
    if (front == string::npos)
    {
        // 改行がない場合は先頭位置でしょう。
        return 0;
    }
    return front + strlen("\n");
}


std::string::size_type FindNextLine(const std::string &source, std::string::size_type pos)
{
    try
    {
        auto ret = source.find("\n", pos);
        if (ret == string::npos)
        {
            return source.length();
        }
        return ret + strlen("\n");
    }
    catch(std::exception ex)
    {
        LOG("%s", ex.what());
        assert(false);
        return string::npos;
    }
}


void EraseFindLine(std::string &source, const std::string &search_string, short mode)
{
    switch(mode)
    {
        case 0:
        {
            //含まれている行を消す
            string::size_type front = source.find(search_string);
            while( front != string::npos )
            {
                front = FindLineFrontWithPosition(source, front);
                auto last = FindNextLine(source, front);
                if (last == string::npos)
                {
                    assert(false);
                    exit(EXIT_FAILURE);
                }
                source.erase(front, last - front);
                
                front = source.find(search_string, front);
            }
        }
            
        case 1:
            //先頭にある場合のみ消す。
        {
            string::size_type pos = source.find(search_string);
            typeof(pos) front = 0;
            while( pos != string::npos )
            {
                front = FindLineFrontWithPosition(source, pos);
                if (pos != front)
                {
                    //先頭行ではなかった場合。
                    pos = source.find(search_string, ++pos);
                    continue;
                }
                auto last = FindNextLine(source, pos);
                if (last == string::npos)
                {
                    assert(false);
                    exit(EXIT_FAILURE);
                }
                source.erase(front, last - front);
                
                pos = source.find(search_string, front);
            }
        }
    }
}


/** git コンフリクトを表す行を消す。 */
std::string EraseConflictSymbols(const std::string &source)
{
    std::string ret(source);
    std::string::size_type conflict_line = 0;
    typeof(conflict_line) next_line = 0;
    while(conflict_line != string::npos)
    {
        conflict_line = ret.find(TAG_CONFLICT_HEAD, conflict_line);
        conflict_line = FindLineFrontWithPosition(ret, conflict_line);
        next_line = FindNextLine(ret, conflict_line);
        if (conflict_line != string::npos
            && next_line != string::npos)
        {
            ret.erase(conflict_line, next_line - conflict_line);
        }
        else
        {
            break;//"<<<<<<< HEAD"が無ければ以降も無いはず。
        }
        
        conflict_line = ret.find(TAG_CONFLICT_MID, conflict_line);
        if (conflict_line != string::npos)
        {
            conflict_line = FindLineFrontWithPosition(ret, conflict_line);
            auto next_line = FindNextLine(ret, conflict_line);
            if (next_line == string::npos)
            {
                assert(false);
                return "";
            }
            ret.erase(conflict_line, next_line - conflict_line);
        }
        
        conflict_line = ret.find(TAG_CONFLICT_END, conflict_line);
        if (conflict_line != string::npos)
        {
            conflict_line = FindLineFrontWithPosition(ret, conflict_line);
            auto next_line = FindNextLine(ret, conflict_line);
            if (next_line == string::npos)
            {
                assert(false);
                return "";
            }
            ret.erase(conflict_line, next_line - conflict_line);
        }
    }
    return ret;
}


bool IsContainsDuplicate(const Plist::ASSOCIATIVE_MAP &left, const Plist::ASSOCIATIVE_MAP &right)
{
    for (auto item : left)
    {
        if ( right.find(item.first) == right.end())
        {
            return true;
        }
    }
    return false;
}


bool ComparePairs(const Plist::ASSOCIATIVE_MAP &p1, const Plist::ASSOCIATIVE_MAP &p2)
{
    return true;
}

NAMESPACE_CLOSE(LocalizedPlist)
