/**
* Let's make decrypt key into random string.
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <random>
#include <assert.h>

#define RESULT_LENGTH 512
#define HEAD_DIFF 42
#define OUTPUT_ASCII_RANGE (126 - HEAD_DIFF)


#pragma mark - HELPER FUNCTIONS

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
    if (argc < 3)
    {
        printf("error 引数が足りません。\n");
        return true;
    }
    
    const unsigned int KEY_LENGTH = strlen(argv[1]);
    const unsigned int KEY_POSITION = atoi(argv[2]);
    if (RESULT_LENGTH < KEY_LENGTH + KEY_POSITION)
    {
        printf("error 指定の引数では生成する字数を超えます。[生成字数:%d][パラメタに従った場合の字数%d]\n", RESULT_LENGTH, KEY_POSITION + KEY_LENGTH);
        return true;
    }
    
    return false;
}

void MixString(char ret[RESULT_LENGTH], const char* input_string, const unsigned int key_length, const unsigned int key_position)
{
    std::random_device rd;  //std::random_device は毎回ハードウェアエントロピーソースを収集するため、実行速度が遅いのが欠点です。
    std::mt19937 mt(rd());  //パフォーマンスが必要な用途には、初期シードから長周期の乱数列を高速に生成するメルセンヌ・ツイスターの使用を検討しましょう。（シードにstd::random_deviceを与えると良いでしょう。）
    for (int i = 0; i < RESULT_LENGTH; ++i )
    {
        ret[i] = (char)((mt() % OUTPUT_ASCII_RANGE) + HEAD_DIFF);
        assert((int)ret[i] >= HEAD_DIFF);
        assert((int)ret[i] < 127);
        //        printf("[%c]\n", ret[i]);
    }
    
    for (int cnt = 0 ; cnt < key_length; ++cnt)
    {
        ret[key_position + cnt] = input_string[cnt];
    }
    
    std::cout << std::endl;
    std::cout << "key string   \t:" << input_string << std::endl;
    printf("string length  \t:%4d\n", key_length);
    printf("string position\t:%4d\n", key_position);
    std::cout << "result :" << std::endl;
    std::cout << ret << std::endl;
}

/*
 * @param: 1=文字列、2=埋め込む位置
 */
int main(int argc, char *argv[])
{
    DumpParam(argc, argv);
    
    if (ArgumentIsWrong(argc, argv))
    {
        std::cout << "中断" << std::endl;
        return 1;
    }
    
    
    //生成開始。
    const unsigned int KEY_LENGTH = strlen(argv[1]);
    const unsigned int KEY_POSITION = atoi(argv[2]);
    char ret[RESULT_LENGTH]="";

    MixString(ret, argv[1], strlen(argv[1]), atoi(argv[2]));
    return 0;

    std::random_device rd;  //std::random_device は毎回ハードウェアエントロピーソースを収集するため、実行速度が遅いのが欠点です。
    std::mt19937 mt(rd());  //パフォーマンスが必要な用途には、初期シードから長周期の乱数列を高速に生成するメルセンヌ・ツイスターの使用を検討しましょう。（シードにstd::random_deviceを与えると良いでしょう。）
    for (int i = 0; i < RESULT_LENGTH; ++i )
    {
        ret[i] = (char)((mt() % OUTPUT_ASCII_RANGE) + HEAD_DIFF);
        assert((int)ret[i] >= HEAD_DIFF);
        assert((int)ret[i] < 127);
//        printf("[%c]\n", ret[i]);
    }
    
    for (int cnt = 0 ; cnt < KEY_LENGTH; ++cnt)
    {
        ret[KEY_POSITION + cnt] = argv[1][cnt];
    }
    
    std::cout << std::endl;
    std::cout << "key string   \t:" << argv[1] << std::endl;
    printf("string length  \t:%4d\n", KEY_LENGTH);
    printf("string position\t:%4d\n", KEY_POSITION);
    std::cout << "result :" << std::endl;
    std::cout << ret << std::endl;
    
return 0;

}
