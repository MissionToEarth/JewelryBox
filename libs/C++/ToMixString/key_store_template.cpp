/**
 * KeyStore用のソースファイルを作る。
 *
 * date: 2018/05/11
 * author: owl
 */

#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>


#pragma mark - DATA

// MARKER of REPLACE
#define __MARK_LONG_STRING__  ("__MARK_LONG_STRING__")
#define __MARK_CASE__     ("__MARK_CASE__")
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

std::string MakeCaseSentence(const char* case_type, const char* position, const char* length)
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
        template_case_sentence.replace(pos, strlen(__MARK_KEY_LENGHT__), length);
        pos = template_case_sentence.find(__MARK_KEY_LENGHT__);
    }while(pos != std::string::npos);
    
    return template_case_sentence;
}

/**
 *  @brief:
 *  @param:
 */
int main(int argc, char *argv[])
{
    using namespace std;
    const char *MixString = argv[1];
    
    //キーを混ぜた文字列を置換する。
    std::string template_code = TEMPLATE_CODE;
    std::string::size_type pos = template_code.find(__MARK_LONG_STRING__);
    assert(pos != std::string::npos);
    template_code.replace(pos, std::strlen(__MARK_LONG_STRING__), MixString );
    
    //ケース分のパートを置換する。
    pos = template_code.find(__MARK_CASE__);
    assert(pos != std::string::npos);
    template_code.replace(pos, std::strlen(__MARK_LONG_STRING__), "" );
    int case_num = atoi(argv[2]);
    for(int i = 0; i < case_num; ++i)
    {
        string sentence;
        sentence = MakeCaseSentence("STORAGE", "318", "10");
        template_code.replace(pos, 0, sentence);
        
        pos += sentence.size();
    }
    
    //書き込み
    ofstream outputfile("KeyStore.cpp");
    outputfile << template_code;
    outputfile.close();
    
    return 0;
}



//jsonを使う準備

//#include "picojson.h"
//
//    //ケース分のパートを置換する。
//    //jsonを想定すると
//    std::string json="";
//    picojson::value v;
//    const std::string err = picojson::parse(v, json);
//    if (err.empty() == false)
//    {
//        std::cerr << err << std::endl;
//        return 2;
//    }
//    picojson::object& obj = v.get<picojson::object>();
//    obj["string"].get<std::string>();

