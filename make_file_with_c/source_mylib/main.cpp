#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <new>

#include <dlfcn.h>

#ifdef MEM_DEBUG
/**
 *  メモリの監視。
 */
extern "C" {
    static void* (*libc_malloc)(size_t);
    void* malloc(size_t __size)
    {
        printf("malloc \n");
        if (libc_malloc == NULL)
        {
            libc_malloc = (void* (*)(size_t))dlsym(RTLD_NEXT, "malloc");
        }
        return libc_malloc(__size);
    }
}

/**
 *  new オーバーロード、詳細はググれ。　１つでは足りない。
 */
//void* operator new(std::size_t __sz) throw(std::bad_alloc)
//{
//    return malloc(__sz);
//}
#endif

#define MAX 100

int main() {
    std::printf("hello\n");
    
    int *arr;
    arr = (int*)malloc(sizeof(int) * MAX);

    free(arr);
    
    std::printf("good by\n");
    return 0;
}

