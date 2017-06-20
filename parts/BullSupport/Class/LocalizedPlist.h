//
//  plist_reader.h
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//
/** 
 コンフリクしたデータにて
 key　string　のペアがそれぞれ同数で入っている。　&&　過不足のない状態。（keyタグ　stringタグがコンフリクしたパートの中で閉じられている。且つ余分がない）
    ＝＞両方を残す。
    <>
    順番にコンフリクトを比較していく。
        成功する　ーーーー
            コンフリクトの記号を消す。
            <<<<< ===== >>>>>
            消した物で上書き。
            次のコンフリクトへ。
        失敗する　ーーーー
            何もしない一旦
    <>
 */
#ifndef plist_reader_h
#define plist_reader_h

#include "macros.h"

#include <iostream>
#include <unordered_map>
#include <string.h>

#define TAG_CONFLICT_HEAD "<<<<<<<"
#define TAG_CONFLICT_MID "======="
#define TAG_CONFLICT_END ">>>>>>>"

#define TAG_KEY  R"(<key>)"
#define TAG_KEY_CLOSE  R"(</key>)"
#define TAG_VALUE  R"(<string>)"
#define TAG_VALUE_CLOSE  R"(</string>)"


// 名前空間宣言
NAMESPACE_OPEN(LocalizedPlist)

//げろげろ　めんどい
//class Conflict
//{
//    enum class STATE
//    {
//        HEAD,
//        CHANGED,
//    };
//    STATE m_state;
//    std::string str;
//    bool Parse(const std::string &data);
//};


/** BULL localized plist への対応 */
class Plist
{
public:
    /** localized の plist に使われる key string に対応（dictなどに非対応[2017年6月20日]） */
    using ASSOCIATIVE_MAP = std::unordered_map<std::string, std::string>;
    
public:
    ASSOCIATIVE_MAP  m_values; //key / value のペアによるリスト
    std::string m_source; //
    
public:
    Plist() = default;
    ~Plist() = default;
    
    /** 正常なLocalized Plist を読み込む。key/valueペアのマップを作成する */
    int Parse(const std::string &filepath);
    
private:
    int ReadFile(const char* filepath);
    ///
    ASSOCIATIVE_MAP MakePairs(const std::string &source);
    
    /** コンフリクトのパートを取り出す。
     失敗する場合は空文字を返す。*/
    std::string GetConflictUnit(const std::string &source, std::string::size_type cur_pos);
    
public:
    //テストコード
    static void Test();
};


#pragma mark - ヘルパーメソッド
/** 指定した位置の　先頭行位置　を返す。 */
std::string::size_type FindLineFrontWithPosition(const std::string &source, std::string::size_type pos);

/** string　と　その文字列の位置　を与えられた時に、与えられた位置の次の行の先頭位置を返す。
 失敗か、次の行がない場合には nposを返す。　*/
std::string::size_type FindNextLine(const std::string &source, std::string::size_type pos);
std::string EraseConflictSymbols(const std::string &source);

NAMESPACE_CLOSE(LocalizedPlist)


///** 想定: タグの基底クラス */
//class PlistTagObject
//{
//};
//class PlistTagDict{};
//class PlistTagString{};


#endif /* plist_reader_h */
