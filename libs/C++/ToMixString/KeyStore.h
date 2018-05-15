#include "cocos2dx.h"
class KeyStore
{
    enum Type {
        IMAGE
        STORAGE
        AAAAA
        BBBBB
        CCCCC
        DDDDD
    };
    std::string getStorageKey(KeyStore::Type type);
};