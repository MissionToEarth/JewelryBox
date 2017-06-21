/**
 2017年6月19日
 */

#include "stdio.h"

// dirty huck is indentation of namespace block.
#define NAMESPACE_OPEN(_name) namespace _name {
#define NAMESPACE_CLOSE(_name) }
#define alice_namespace_open NAMESPACE_OPEN(ALICE)
#define alice_namespace_close NAMESPACE_CLOSE(ALICE)

alice_namespace_open

//デバッグ用のLOGマクロ
#ifdef DEBUG
//
#define DDD_LOG(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)
//
#define DDD_LOG_WARN(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)
#else   //
#define DDD_LOG(...)
#define DDD_LOG_WARN(...)
#endif  // END OF DEBUG LOG MACRO

#define DDD_LOG_ERROR(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)

alice_namespace_close
