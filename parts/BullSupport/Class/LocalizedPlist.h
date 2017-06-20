//
//  plist_reader.h
//  BullSupport
//
//  Created by t-harada on 2017/06/16.
//
//

#ifndef plist_reader_h
#define plist_reader_h

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


namespace LocalizedPlist
{
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
    
//    コンフリクしたデータにて
//    {
//        key　string　のペアがそれぞれ同数で入っている。　&&　過不足のない状態。（keyタグ　stringタグがコンフリクしたパートの中で閉じられている。且つ余分がない）
//        ＝＞両方を残す
//        {
//            比較する
//            成功する
//            {
//                コンフリクトの記号を消す。
//                <<<<< ===== >>>>>
//            }
//            
//        }
//    }

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

}


///** 想定: タグの基底クラス */
//class PlistTagObject
//{
//};
//class PlistTagDict{};
//class PlistTagString{};


#endif /* plist_reader_h */