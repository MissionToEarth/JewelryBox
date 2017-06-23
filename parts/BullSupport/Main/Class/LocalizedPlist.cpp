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
        DDD_LOG("key= %s\nvalue= %s", v.first.c_str(), v.second.c_str());
    }
}


#pragma mark - Member of Plist

int Plist::Pars(const std::string &source)
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
    DumpPairs(m_values);
    
    return 0;
}


int Plist::Resolve(const std::string &filepath)
{
    ReadFile(filepath.c_str());
    string source = m_source;
    if (source.find(R"(<plist )") == string::npos)
    {
        DDD_LOG_ERROR("%s : << 指定されたファイルは、plistではありません。",filepath.c_str());
        assert(false);
        exit(EXIT_FAILURE);
    }
    
    
    if (!IsConflict(source))
    {
        DDD_LOG("%s : コンフリクトしていない。", filepath.c_str());
        return 0;
    }
    
    //コンフリクトしている場合は...。
    string::size_type pos = source.find(TAG_CONFLICT_HEAD);
    while (pos != string::npos)
    {
        if (pos == string::npos) {
            break;
        }
        auto front = FindLineFrontWithPosition(source, pos);
        if (pos != front)
        {
            assert(false);
            continue;
        }
        auto last = source.find(TAG_CONFLICT_END, pos);
        last = FindNextLine(source, last);
        
        DDD_LOG("%s", source.c_str());
        assert(front < last);
        
        string conflict = source.substr(front, last - front);
        DDD_LOG("%s", conflict.c_str());
        string head = GetConflictPart(conflict, true);
        string changed = GetConflictPart(conflict, false);
        
        auto head_map = MakeKeyStringPairs(head);
        auto changed_map = MakeKeyStringPairs(changed);
        if (ComparePairs(head_map, changed_map))
        {
            head += changed;
            DDD_LOG("[%s]", head.c_str());
            source.replace(front, last - front, head);
            DDD_LOG("[%s]", source.c_str());
            pos = front;//ソース更新に対応するため、位置を戻す
        }
        else if (head_map.size() <= 0 && changed_map.size() <= 0 && NotMatchStringValue(head, changed))
        {
            DDD_LOG("[%s]", changed.c_str());
            source.replace(front, last - front, changed);
            DDD_LOG("[%s]", source.c_str());
            pos = front;//ソース更新に対応するため、位置を戻す
        }
        
        pos = source.find(TAG_CONFLICT_HEAD, ++pos);
    }
    
    WriteFile(filepath.c_str(), source);
    
    return 0;
}


int Plist::ReadFile(const char* filepath)
{
    std::ifstream ifs(filepath);
    if (ifs.fail())
    {
        ifs.close();
        DDD_LOG_WARN("ifstream で file open に失敗 : %s", filepath);
        assert(false);
        exit(EXIT_FAILURE);
    }
    
    //バッファ
    m_source = std::string((std::istreambuf_iterator<char>(ifs))
                           , std::istreambuf_iterator<char>());
    ifs.close();
    return 0;
}


int Plist::WriteFile(const char *filepath, const std::string &source)
{
    std::ofstream ofs(filepath, std::ofstream::out);
    if (ofs.fail())
    {
        ofs.close();
        DDD_LOG_WARN("ofstream で file open に失敗 : %s", filepath);
        assert(false);
        exit(EXIT_FAILURE);
    }
    
    ofs.write(source.c_str(), source.size());
    ofs.close();
    
    return 0;
}


/** 以下の形式が繰り返しているものに対応する。(コンフリクトがある場合には対応していない。
 <key>xxx</key>\n
 <string>xxxxx</string>\n    */
Plist::ASSOCIATIVE_MAP Plist::MakeKeyStringPairs(const std::string &source)
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
        assert(NotMatchStringValue("<string>イロハ</string>","<string>irohas</string>") == true);
        assert(NotMatchStringValue("<string>あいう\n</string>","<string>あいう\n</string>") == false);
        assert(NotMatchStringValue("<string>あいう\n</string>","<string>あいう\n</string>\n<string>ddddd</string>") == false);
        assert(NotMatchStringValue("<string>あああ</string>","<key>あああ</key>") == false);
    }
    {
        string test("abcdefz");
        DDD_LOG("[%s]", test.substr(test.length() - 1).c_str());
        string gust("abcdefあz");
        DDD_LOG("[%s]", gust.substr(gust.length() - 1).c_str());
        gust.push_back('\n');
        DDD_LOG("末尾に改行追加：[%s]：", gust.c_str());
        DDD_LOG("erase:[%s]", gust.erase(1, gust.length()).c_str());
        string east("abcイロハ");
        DDD_LOG("[%s]", east.substr(east.length() - 3).c_str());//全角文字の場合は、length()などで考慮されていないので、困る。
    }
    {
        string tmp("aaaaaa\nbbbbbbbbbb\ncccccccccc");
        auto ret01 = FindNextLine(tmp, 0);
        auto ret02 = FindNextLine(tmp, 10);
        DDD_LOG("1 [%s]", tmp.substr(ret01).c_str());
        DDD_LOG("2 [%s]", tmp.substr(ret02).c_str());
    }
    {
        string test(TEST_DATA);
        EraseFindLine(test, TAG_CONFLICT_HEAD, 0);
        DDD_LOG("==erase conflict head==\n[%s]", test.c_str());
        test = std::string(TEST_DATA);
        EraseFindLine(test, TAG_CONFLICT_HEAD, 1);
        EraseFindLine(test, TAG_CONFLICT_END, 1);
        DDD_LOG("==erase conflict head mode:1==\n[%s]", test.c_str());
    }
    {
        string tmp = EraseConflictSymbols(TEST_DATA);
        DDD_LOG("==EraseConflictSymbols==\n[%s]", tmp.c_str());
    }
    
    Plist p;
    string conflict_01 = GetConflictUnit(TEST_DATA, 0);
    DDD_LOG("==GetConflictUnit==\n[%s]", conflict_01.c_str());
    
    ASSOCIATIVE_MAP changed = p.MakeKeyStringPairs(GetConflictPart(conflict_01, false));
    ASSOCIATIVE_MAP head = p.MakeKeyStringPairs(GetConflictPart(conflict_01, true) );
    DumpPairs(head);
    DumpPairs(changed);
    
    DDD_LOG(IsContainsDuplicate(head, changed) ? "重複している　key　がある" : "重複していない key はそれぞれ");
    DDD_LOG(ComparePairs(head, changed) ? "数は一致して、keyはそれぞれに固有" : "意図しない状態");
    
    if (ComparePairs(head, changed))
    {
        EraseFindLine(conflict_01, TAG_CONFLICT_MID, 1);
        
    }
    
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


std::string GetConflictPart(const std::string &conflict_unit, bool part)
{
    DDD_LOG("%s", __PRETTY_FUNCTION__);
    
    string::size_type begin = conflict_unit.find(TAG_CONFLICT_HEAD);
    if (begin == string::npos)
    {
        begin = 0;
    }
    else
    {
        begin = FindNextLine(conflict_unit, begin);
    }
    
    string::size_type mid_pos = conflict_unit.find(TAG_CONFLICT_MID);
    if (part)
    {
        //HEAD部取得
        string head = conflict_unit.substr(begin, mid_pos - begin);
        DDD_LOG("===%s",head.c_str());
        return head;
    }
    else
    {
        //相手の変更部取得
        mid_pos = FindNextLine(conflict_unit, mid_pos);
        string changed = conflict_unit.substr(mid_pos);
        EraseFindLine(changed, TAG_CONFLICT_END, 1);
        DDD_LOG("===%s", changed.c_str());
        return changed;
    }
}


std::string GetConflictUnit(const std::string &source, std::string::size_type cur_pos)
{
    string::size_type pos = source.find(TAG_CONFLICT_HEAD, cur_pos);
    string::size_type end = source.find(TAG_CONFLICT_END, pos);
    pos = source.find("\n", pos) + strlen("\n");
    string ret = source.substr(pos, end - pos);
    
    //        DDD_LOG("%s", ret.c_str());
    return ret;
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
        DDD_LOG("%s", ex.what());
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
            decltype(pos) front = 0;
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
    decltype(conflict_line) next_line = 0;
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
    if (p1.size() <= 0 || p2.size() <= 0 || p1.size() != p2.size())
    {
        return false;
    }
    for(auto v : p1)
    {
        if (p2.find(v.first) != p2.end())
        {
            return false;
        }
    }
    
    return true;
}

/** <string>タグの内容が異なっていればtrue */
bool NotMatchStringValue(const std::string &left, const std::string &right)
{
    //チェック
    if(   left.find(TAG_VALUE)==string::npos        || right.find(TAG_VALUE)==string::npos
       || left.find(TAG_VALUE_CLOSE)==string::npos  || right.find(TAG_VALUE_CLOSE)==string::npos
       || left.find(TAG_KEY)!=string::npos          || right.find(TAG_KEY)!=string::npos
       || left.find(TAG_KEY_CLOSE)!=string::npos    || right.find(TAG_KEY_CLOSE)!=string::npos)
    {
        return false;
    }
    
    {
        //タグが2個以上含まれているか？
        auto pos = left.find(TAG_VALUE);
        if (left.find(TAG_VALUE, ++pos) != string::npos )
        {
            return false;
        }
        pos = right.find(TAG_VALUE);
        if (right.find(TAG_VALUE, ++pos) != string::npos )
        {
            return false;
        }
    }
    
    auto find_value = [](const std::string &str){
        string::size_type pos = str.find(TAG_VALUE) + strlen(TAG_VALUE);
        decltype(pos) last = str.find(TAG_VALUE_CLOSE);
        return str.substr(pos, last - pos);
    };
    string l = find_value(left);
    string r = find_value(right);
    
    if (l != r)
    {
        return  true;
    }
    return false;
}

NAMESPACE_CLOSE(LocalizedPlist)
