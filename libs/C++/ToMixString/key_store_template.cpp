/**
 * KeyStore用のソースファイルを作る。
 * @note: 出力したjsonファイルに従ってKeyStore.cppファイルを作成する。
 *
 * date: 2018/05/11
 * author: owl
 */

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <sys/stat.h>
#include "picojson.h"
#include "Define.h"


#pragma mark - DATA

// 宣言用生成用部品
#define INCLUDE                 (R"(#include "cocos2d.h")")
#define COMENT_BIGIN    ("/**")
#define COMENT_END      (" */")
#define DECL_NS_BEGIN(NAME)     (R"**(namespace )**" #NAME R"**(
{)**")
#define DECL_NS_END             (R"**(})**")
#define DECL_CLASS_BIGIN        (R"**(class KeyStore
{)**")
#define DECL_CLASS_END          (R"**(};)**")
#define DECL_ENUM_BEGIN(ENUM_NAME)   (R"(enum )" #ENUM_NAME R"( {)")
#define DECL_ENUM_END           (R"**(};)**")
#define DECL_METHOD             (R"**(std::string getStorageKey(KeyStore::Type type);)**")
// ヘッダー
#define HEADER_FILENAME         ("KeyStore.hpp")
// ソース
#define CPP_FILENAME            ("KeyStore.cpp")
// MARKER of REPLACE
#define __MARK_LONG_STRING__    ("__MARK_LONG_STRING__")
#define __MARK_CASE__           ("__MARK_CASE__")
#define __MARK_KEY_CASE_TYPE__  ("__MARK_KEY_CASE_TYPE__")
#define __MARK_KEY_LENGHT__     ("__MARK_KEY_LENGHT__")
#define __MARK_KEY_POSITION__   ("__MARK_KEY_POSITION__")
/** ケース文テンプレ
 *  @note:文中の「s」は埋め込み先の関数内で定義されている変数である。
 */
#define TEMPLATE_CASE_SENTENCE  R"**(
        case __MARK_KEY_CASE_TYPE__:
        {
            char r[__MARK_KEY_LENGHT__ + 1]="";
            strncpy(r, s + __MARK_KEY_POSITION__, __MARK_KEY_LENGHT__);
            return r;
        }
)**";
/** ソースコードテンプレ */
#define TEMPLATE_CODE   R"**(//
//  KeyStore.cpp
//  BULL iOS
//
#include "KeyStore.hpp"
#include <string.h>

std::string KeyStore::getStorageKey(KeyStore::Type type)
{
    char *s = "__MARK_LONG_STRING__";
    switch(type)
    {
        __MARK_CASE__
            
        default:
            break;
    }
    CCASSERT(false, "KeySore::getStorageKey");
    return "";
})**";


#pragma mark - FUNCTIONS


bool CheckResult(picojson::object result_json)
{
    using namespace std;

    std::string mix_string = result_json[K_MIX_STRING].get<std::string>();
    picojson::array arr = result_json[K_KEY_INFO_LIST].get<picojson::array>();
    picojson::object obj;
    for (auto data : arr)
    {
        obj = data.get<picojson::object>();
        auto key_type = obj[K_KEY_TYPE].get<std::string>();
        auto key = obj[K_KEY].get<std::string>();
        int pos = atoi(obj[K_KEY_POSITION].get<std::string>().c_str());
        int size = atoi(obj[K_KEY_SIZE].get<std::string>().c_str());

        cout << "#" << endl;
        cout << "type \t:" << key_type << endl;
        cout << "key \t:" << key << endl;
        cout << "pos \t:" << pos << endl;
        cout << "size \t:" << size << endl; 
        cout << "result\t:" << mix_string.substr(pos, size) << endl;
        auto ret = (key == mix_string.substr(pos, size)) ? "SUCCESS" : "FAIL!!!";
        cout << ret << endl;

        if (key != mix_string.substr(pos, size))
        {
            return false;
        }
    }

    return true;
}

// ヘッダーファイル文生成
std::string MakeHeader(picojson::array infos)
{
    using namespace std;

    string tab = "    ";

    string ret = "";
    ret += INCLUDE;
    ret += "\n";
    ret += DECL_CLASS_BIGIN;
    ret += "\n";
    ret += tab + DECL_ENUM_BEGIN(Type);
    ret += "\n";
    int tab_cnt = 2;
    for(auto item : infos)
    {
        for (int i=0; i<tab_cnt; ++i) 
        {
            ret += tab; 
        }
        ret += item.get<picojson::object>()[K_KEY_TYPE].get<string>();
        ret += ",";
        ret += "\n";
    }
    ret += tab + DECL_ENUM_END;
    ret += "\n";
    ret += tab + DECL_METHOD;
    ret += "\n";
    ret += DECL_CLASS_END;
    return ret;    
}

// case文を作る。必要なパラメータを置換する。
std::string MakeCaseSentence(picojson::value val)
{
    using namespace std;
    
    std::string template_case_sentence = TEMPLATE_CASE_SENTENCE;
    std::string::size_type pos = std::string::npos;
    picojson::object obj = val.get<picojson::object>();

    // set case ~
    pos = template_case_sentence.find(__MARK_KEY_CASE_TYPE__);
    assert(pos != std::string::npos);
    template_case_sentence.replace(pos, strlen(__MARK_KEY_CASE_TYPE__), obj[K_KEY_TYPE].get<string>());
    
    // set position
    pos = template_case_sentence.find(__MARK_KEY_POSITION__);
    assert(pos != std::string::npos);
    template_case_sentence.replace(pos, strlen(__MARK_KEY_POSITION__), obj[K_KEY_POSITION].get<string>());
    
    // set size
    pos = template_case_sentence.find(__MARK_KEY_LENGHT__);
    assert(pos != std::string::npos);
    do
    {
        template_case_sentence.replace(pos, strlen(__MARK_KEY_LENGHT__), obj[K_KEY_SIZE].get<string>());
        pos = template_case_sentence.find(__MARK_KEY_LENGHT__);
    }while(pos != std::string::npos);
    
    return template_case_sentence;
}

std::string MakeCaseSentence(const char* case_type, const char* position, const char* size)
{
    using namespace std;
    
    std::string template_case_sentence = TEMPLATE_CASE_SENTENCE;
    std::string::size_type pos;
    
    // set case ~
    pos = template_case_sentence.find(__MARK_KEY_CASE_TYPE__);
    assert(pos != std::string::npos);
    template_case_sentence.replace(pos, strlen(__MARK_KEY_CASE_TYPE__), case_type);
    
    // set position
    pos = template_case_sentence.find(__MARK_KEY_POSITION__);
    assert(pos != std::string::npos);
    template_case_sentence.replace(pos, strlen(__MARK_KEY_POSITION__), position);
    
    // set size
    pos = template_case_sentence.find(__MARK_KEY_LENGHT__);
    assert(pos != std::string::npos);
    do
    {
        template_case_sentence.replace(pos, strlen(__MARK_KEY_LENGHT__), size);
        pos = template_case_sentence.find(__MARK_KEY_LENGHT__);
    }while(pos != std::string::npos);
    
    return template_case_sentence;
}


/**
 *  @brief:jsonファイルを読み込んでパースする。
 *  @param:
 */
bool ParseOfPicoJson(char *file, picojson::value& dest)
{
    using namespace std;
    cout << file << endl;

    std::ifstream fs;
    fs.open(file, std::ios::in);
    assert(fs);
    if (fs.fail())
    {
        fs.close(); //自動変数のストリームだからcloseしなくても大丈夫。ホントはね。
        return false;
    }

    // jsonパース
    fs >> dest;//オペレーターオーバーロードされてた
    fs.close();
    // cout << val.serialize() << endl;//チェック
    if (!picojson::get_last_error().empty() || fs.fail())
    {
        cout << picojson::get_last_error() << endl;
        return false;
    }

    return true;
}

/**
 *  @brief:
 *  @param: argv[1]に json のファイルパスを指定する。
 */
int main(int argc, char *argv[])
{
    using namespace std;
    // jsonの取得
    picojson::value val;
    if( !ParseOfPicoJson(argv[1], val) )
    {
        cout << "parse failure" << endl;
        return -1;
    }
    // CheckResult(val.get<picojson::object>()); //読み込みファイルのキーが正しいかの確認
    picojson::object obj = val.get<picojson::object>();

    // キーを混ぜた文字列を置換するパート。
    std::string mix_string(obj[K_MIX_STRING].get<string>());
    std::string template_code = TEMPLATE_CODE;
    std::string::size_type pos = template_code.find(__MARK_LONG_STRING__);
    assert(pos != std::string::npos);
    template_code.replace(pos, std::strlen(__MARK_LONG_STRING__), mix_string );

    // case文のパートを置換する。
    pos = template_code.find(__MARK_CASE__);
    assert(pos != std::string::npos);
    template_code.replace(pos, std::strlen(__MARK_LONG_STRING__), "" );
    picojson::array key_infos = obj[K_KEY_INFO_LIST].get<picojson::array>();
    for (auto& info : key_infos)
    {
        string sentence;
        sentence = MakeCaseSentence(info);
        template_code.replace(pos, 0, sentence);        
        pos += sentence.size();
    }

    //書き込み
    if (mkdir("output", S_IRWXU | S_IRWXG | S_IRWXO))
    {
        perror("output");
    }
    string path = "./output/";
    path += CPP_FILENAME;
    ofstream outputfile(path);
    assert(outputfile);
    outputfile << template_code;
    outputfile.close();

    path = "./output/";
    path += HEADER_FILENAME;
    string header = "";
    header = MakeHeader(obj[K_KEY_INFO_LIST].get<picojson::array>());
    outputfile.open(path);
    assert(outputfile);
    outputfile << header;
    outputfile.close();
    
    return 0;
}
