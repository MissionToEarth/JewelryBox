#ifndef PATH_UTILS_HPP
#define PATH_UTILS_HPP
#include <string>


namespace PathUtils
{
/**
  パスからベースネームを取得。
  注意「./akak/」<-この場合は空になるよ。
 */
std::string basename(const std::string& path);


}

#endif
