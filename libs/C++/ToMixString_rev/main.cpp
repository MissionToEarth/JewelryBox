#include "key_store_template.cpp"
#include "key_string_maker_with_csv.cpp"

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
        printf("Error\t: 引数が足りません。\n");
        return true;
    }
    
    return false;
}

int main(int argc, char* argv[])
{
    using namespace std;
    
    if (ArgumentIsWrong(argc, argv))
    {
        return -1;
    }
    
    picojson::object obj;
    Csv2KeyJson(obj, argv[1]);
    if(!CheckResult(obj))
    {
        cerr << "Fail conversion." << endl;
        return -1;
    }
    MakeKeyStoreCpp(obj);
}
