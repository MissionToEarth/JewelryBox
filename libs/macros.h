/**
 2017年6月19日
 */

#include "stdio.h"

//#define DEBUG

//デバッグ用のLOGマクロ
#ifdef DEBUG
//
#define LOG(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)
//
#define LOG_WARN(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)
#else   //
#define LOG(...)
#define LOG_WARN(...)
#endif  // END OF DEBUG LOG MACRO

#define LOG_ERROR(...) do{ \
printf(__VA_ARGS__); \
printf("\n"); \
}while(0)
