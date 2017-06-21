#include <stdio.h>
#include <dlfcn.h>

/**
 *  バックトレース
 *  　=> man backtrace
 *  または、__builtin_return_address(0) と dladdr を使う。
 */
namespace MyLib
{
    void backtrace(void* address)
    {
        Dl_info info;
        dladdr(__builtin_return_address(0), &info);
        printf("[%s] parent func name => %p [%s]\n",
               __func__,
               __builtin_return_address(0),
               info.dli_sname);
    }
}
