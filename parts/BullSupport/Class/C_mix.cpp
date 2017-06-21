/**
*/

#include "C_mix.h"

#include <iostream>
#include <string.h>
using namespace std;


#include "LocalizedPlist.h"

static std::string parse_c(const char *filepath)
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
