/**
* Let's make decrypt key into random string.
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <random>
#include <assert.h>
#include <stdlib.h>
#include "picojson.h"

#include <utility>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


#define RESULT_LENGTH 512
#define HEAD_DIFF 42
#define OUTPUT_ASCII_RANGE (126 - HEAD_DIFF)


namespace StringUtilities
{
    void DumpVecVecString( std::vector<std::vector<std::string>> split_list)
    {
        // 格納された値をチェック
        for(auto str_vec : split_list)
        {
            for (auto str : str_vec)
            {
                std::cout << str << std::endl;
            }
        }
    }

    std::vector<std::string> Split(const std::string& input, char delimiter)
    {
        std::istringstream stream(input);

        std::string field;
        std::vector<std::string> result;
        while (std::getline(stream, field, delimiter))
        {
            result.push_back(field);
        }
        return result;
    }

    int CountSize(std::vector<std::vector<std::string>> input_list)
    {
        int cnt = 0;
        for (auto& line : input_list)
        {
            for (auto& str : line)
            {
                cnt += str.size();
            }
        }
        return cnt;
    }


    /**
     * @brief:ランダム文字列作成、（ASCII codeの特定範囲から）
     * @param:dest=格納先、size=destのサイズ（作りたい字数）
     */
    void MakeRandomString(char *dest, int size, int output_range = 126, int head_diff = 34)
    {
        assert(size > 0);

        std::random_device rd;
        std::mt19937 mt(rd());
        for (int i = 0; i < size; ++i )
        {
            dest[i] = (char)((mt() % output_range) + head_diff);
            assert((int)dest[i] >= head_diff);
            assert((int)dest[i] < 127);
            // printf("[%c]\n", dest[i]);
        }

        dest[size] = '\0';
    }

    /**
     * @brief:ランダム文字列作成、（ASCII codeの特定範囲から）
     * @param:dest=格納先、size=destのサイズ（作りたい字数）
     */
    void MakeRandomString(std::string& dest, int size, int min_range = 33, int max_range = 126)
    {
        assert(size > 0);

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<> randX(min_range, max_range);//こっちの方がいいかもしれない。
        int tmp = '\0';
        for (int i = 0; i < size; ++i )
        {
            tmp = randX(mt);
            assert(tmp >= min_range);
            assert(tmp < 127);
            dest += (char)tmp;
        }
    }
}


#pragma mark - HELPER FUNCTIONS

bool CheckResult(picojson::object result_json)
{
    using namespace std;

    std::string mix_string = result_json["mix_string"].get<std::string>();
    picojson::array arr = result_json["key_info_list"].get<picojson::array>();
    picojson::object obj;
    for (auto data : arr)
    {
        obj = data.get<picojson::object>();
        auto key_type = obj["key_type"].get<std::string>();
        auto key = obj["key"].get<std::string>();
        int pos = atoi(obj["position"].get<std::string>().c_str());
        int size = atoi(obj["size"].get<std::string>().c_str());

        cout << "#" << endl;
        cout << "type \t:" << key_type << endl;
        cout << "key \t:" << key << endl;
        cout << "pos \t:" << pos << endl;
        cout << "size \t:" << size << endl; 
        cout << "result\t:" << mix_string.substr(pos, size) << endl;
        auto ret = (key == mix_string.substr(pos, size)) ? "SUCCESS" : "FAIL";
        cout << ret << endl;

        if (key != mix_string.substr(pos, size))
        {
            return false;
        }
    }

    return true;
}


// paramをプロット
void DumpParam(int argc, char *argv[])
{
    printf("argc:%d\n",argc);
    for (int n=0; n<argc; ++n)
    {
        printf("%d:%s\n", n, argv[n]);
    }
}
// paramの整合性チェック
bool ArgumentIsWrong(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("error 引数が足りません。\n");
        return true;
    }
    
    return false;
}

/**
 *  文字列からキーを抽出する。
 */
std::string ExtractionKey(const char* mix_string, const unsigned int position, const unsigned int length)
{
    char ret[length+1];
    strncpy(ret, mix_string+position, length);
    ret[length]='\0';
    return ret;
}

/**
 *  文字列からキーを抽出する。
 */
std::string ExtractionKey(const std::string& mix_string, const unsigned int position, const unsigned int length)
{
    return mix_string.substr(position, length);
}

/**
 * @brief:入力文字列をランダムの長い文字列の中に埋め込む。それをプロットする。
 * @param:dest=格納先、input_string入力文字列、key_length入力文字列の長さ、key_position入力文字列を紛れこませる位置
 */
void MixString(char dest[RESULT_LENGTH], const char* input_string, const unsigned int key_length, const unsigned int key_position)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < RESULT_LENGTH; ++i )
    {
        dest[i] = (char)((mt() % OUTPUT_ASCII_RANGE) + HEAD_DIFF);
        assert((int)dest[i] >= HEAD_DIFF);
        assert((int)dest[i] < 127);
        //        printf("[%c]\n", dest[i]);
    }
    
    for (int cnt = 0 ; cnt < key_length; ++cnt)
    {
        dest[key_position + cnt] = input_string[cnt];
    }
    
    std::cout << std::endl;
    std::cout << "key string   \t:" << input_string << std::endl;
    printf("string length  \t:%4d\n", key_length);
    printf("string position\t:%4d\n", key_position);
    std::cout << "result :" << std::endl;
    std::cout << dest << std::endl;
}

/**
 * @brief:ランダム文字列作成、（ASCII codeの特定範囲から）
 * @param:dest=格納先、size=destのサイズ（作りたい字数）
 */
void RandomString(char *dest, int size)
{
    assert(size > 0);

    std::random_device rd;
    std::mt19937 mt(rd());
    for (int i = 0; i < size; ++i )
    {
        dest[i] = (char)((mt() % OUTPUT_ASCII_RANGE) + HEAD_DIFF);
        assert((int)dest[i] >= HEAD_DIFF);
        assert((int)dest[i] < 127);
               // printf("[%c]\n", dest[i]);
    }

    dest[size] = '\0';
}

/**
 * @brief:ランダム文字列作成、（ASCII codeの特定範囲から）
 * @param:dest=格納先、size=destのサイズ（作りたい字数）
 */
void RandomString(std::string& dest, int size)
{
    assert(size > 0);

    std::random_device rd;
    std::mt19937 mt(rd());
    int tmp = '\0';
    for (int i = 0; i < size; ++i )
    {
        tmp = (mt() % OUTPUT_ASCII_RANGE) + HEAD_DIFF;
        assert(tmp >= HEAD_DIFF);
        assert(tmp < 127);
        dest += (char)tmp;
    }
}


void AddKeyData(picojson::object& dest_data, const std::string& key_name, const std::string& key_str, int pos, int size)
{
    dest_data.insert(std::make_pair("key_type", key_name));
    dest_data.insert(std::make_pair("key", key_str));
    dest_data.insert(std::make_pair("position", std::to_string(pos)));
    dest_data.insert(std::make_pair("size", std::to_string(size)));
}

void WriteFile(const std::string& filename, picojson::object obj)
{
     //書き込み
    picojson::value val(obj);
    std::ofstream outputfile(filename);
    outputfile << val.serialize();
    outputfile.close();   
}

/*
 * @param: 1=文字列、2=埋め込む位置
        ↓↓↓↓↓↓↓↓↓↓↓↓
 * @param: 変更予定 ＝＞ 1=文字列、...、
 */
int main(int argc, char *argv[])
{
    using namespace std;

    //DumpParam(argc, argv);
    if (ArgumentIsWrong(argc, argv))
    {
        std::cout << "中断" << std::endl;
        return -1;
    }
    
    //ファイル読み込みから、行ごとにカンマ区切りで分割。
    std::ifstream ifs(argv[1]);
    if (ifs.fail()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }
    std::string buf_str;
    std::vector<std::vector<std::string>> str_list;
    while (getline(ifs, buf_str)) 
    {
        str_list.push_back(StringUtilities::Split(buf_str, ','));
    }

    // とりあえずランダム文字列作成する。
    string ret;
    RandomString(ret, RESULT_LENGTH);

    //分割想定の位置決め準備。
    std::random_device rnd;
    std::mt19937 mt(rnd());
    const int UNIT_SIZE = RESULT_LENGTH / str_list.size() - 1;//-1は気休め調整
    std::uniform_int_distribution<> randX(10, UNIT_SIZE);


    picojson::array data_list;// key_name, position, size,
    int pos_count = 0;
    for (auto item : str_list)
    {
        try
        {
            //キー文字列を配置
            string key_name = item.at(0);
            string key_str = item.at(1);

            std::uniform_int_distribution<>::param_type param(1, UNIT_SIZE - key_str.size());
            randX.param(param);
            int dif_pos = randX(mt) + pos_count;

            ret.replace(dif_pos, key_str.size(), key_str);

            //json_objを追加
            picojson::object data;
            AddKeyData(data, key_name, key_str, dif_pos, key_str.size());//小さいプログラムだからクラス化しなかった。（データ系のクラスについて）
            data_list.push_back(picojson::value(data));

            pos_count += UNIT_SIZE + 1;//気休め程度の間隔調整としてちょい加算

            // {
            //     // 取り出して確認
            //     std::string ss = ExtractionKey(ret, dif_pos, key_str.size());
            //     std::cout << "get key :[" << ss << "]" << std::endl;
            //     std::cout << "pos :" << dif_pos << ", size :" << key_str.size() << std::endl;
            // }
        }
        catch (const exception e)
        {
            std::cerr << "key情報取得失敗" << std::endl;            
            return -1;
        }
    }
        
    // jsonとして保存
    picojson::object key_store_data;
    key_store_data.emplace("mix_string", ret);
    key_store_data.emplace("key_info_list", data_list);
    WriteFile("mixed_key.json", key_store_data);

    if(!CheckResult(key_store_data))
    {
        return -1;
    }

    return 0;
}
