
/**
  パスからベースネームを取得。
  注意「./akak/」<-この場合は空になるよ。
 */
std::string basename(const std::string& path)
{
    size_t pos = path.rfind('/');
    return path.substr(pos+1);
}
