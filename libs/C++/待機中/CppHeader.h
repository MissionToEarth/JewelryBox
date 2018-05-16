void make(data)
{
    Header h(data);
    h.write(data.getPath());
}

class Header : public CppObject
{
private:
    std::string _header_name;
    
public:
    header() = delete;
    header(std::string name, Type type = CppObject::Type::Declaration);
    virtual ~header();
    
    inline std::string getName() { return _header_name; };
    inline void setName(std::string& name) { _header_name = std::move(name); };
    
    void print();
    std::string serialize() {};
    
    //ストリーム系のオペレーターオーバーロードとかするか、そこまでいるか？
};
