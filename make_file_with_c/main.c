#include <stdio.h>
//#define  __USE_GNU
#include <dlfcn.h>

#define LOG(x, y) printf( x , y ); printf("\n");
//LOGD
//LOGI
//LOGW
//LOGE

int main (int argc, char *argv[])
{
	printf("method in main()\n");
    LOG("引数 %d 個", argc);
    for (int i= 0; i<argc; i++)
    {
        LOG("%s", argv[i]);
    }
    
    printf("%p\n", __builtin_return_address(0));
    printf("%p\n", __builtin_return_address(1));
    printf("%p\n", __builtin_return_address(2));
    printf("%p\n", __builtin_return_address(3));

    printf("正常終了\n");
    return 0;
}
