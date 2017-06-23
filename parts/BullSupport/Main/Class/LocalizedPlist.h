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
    
    /** plist形式の、key／valueタグをマップに格納する。 */
    int Pars(const std::string &source);
    
    /** 正常なLocalized Plist を読み込む。key/valueペアのマップを作成する */
    int Resolve(const std::string &filepath);
private:
    int ReadFile(const char* filepath);
    int WriteFile(const char* filepath, const std::string &source);
    ///
    ASSOCIATIVE_MAP MakeKeyStringPairs(const std::string &source);
    
public:
    //テストコード
    static void Test();
};


#pragma mark - ヘルパーメソッド

/** Git： コンフリクトあるか？ */
bool IsConflict(const std::string &source);

/** Git:　コンフリクトした部分のHEAD部か、変更部を取得 */
std::string GetConflictPart(const std::string &conflict_unit, bool part);

/** コンフリクトのパートを取り出す。
 失敗する場合は空文字を返す。*/
std::string GetConflictUnit(const std::string &source, std::string::size_type cur_pos);


/**
    [要注意]：[2017年6月21日]現時点で 全ての文字列が UTF-8 である事を想定。　＝＞　全角文字への対応をしなければならない。
 */

/** 文字列のSplit */
//std::vector<std::string> Split(std::string &source, const char delimiter[]);

/** 文字列の範囲指定による置換：begin〜end の範囲を置き換える */
void ReplaceWithRange(std::string &source, std::string::size_type begin, std::string::size_type end, const std::string replace);

/** 指定した位置の　先頭行位置　を返す。 */
std::string::size_type FindLineFrontWithPosition(const std::string &source, std::string::size_type pos);

/** string　と　その文字列の位置　を与えられた時に、与えられた位置の次の行の先頭位置を返す。
 失敗したらnposを返す。
 次の行がない場合は末尾の位置を返す。　*/
std::string::size_type FindNextLine(const std::string &source, std::string::size_type pos);

/** 指定した文字列が含まれる行を削除する。モード（0：無条件、1：行の先頭にある場合のみ。...） */
void EraseFindLine(std::string &source, const std::string &search_string, short mode);

/** git にてコンフリクトした際の記号を消す。 */
std::string EraseConflictSymbols(const std::string &source);

/** key に重複があるかどうか */
bool IsContainsDuplicate(const Plist::ASSOCIATIVE_MAP &p1, const Plist::ASSOCIATIVE_MAP &p2);

/** 格納されたペアの数が同じで、key が重複していない。 */
bool ComparePairs(const Plist::ASSOCIATIVE_MAP &p1, const Plist::ASSOCIATIVE_MAP &p2);

/** <string>だけのコンフリクト部分として、比較する。
    パラメタはそれぞれ、"<string>xxxxx</string>" というパートが１つだけ含まれているとする。
    return true : タグに囲まれた内容が一致しない場合。
    return false : それ以外 */
bool NotMatchStringValue(const std::string &left, const std::string &right);


NAMESPACE_CLOSE(LocalizedPlist)

#endif /* plist_reader_h */
