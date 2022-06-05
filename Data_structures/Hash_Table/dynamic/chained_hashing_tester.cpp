#include "chained_hashing.h"

int main()
{
    chainedHash<std::string, int32_t> chainedHash(30);
    std::cout << chainedHash.getIndex("test123") << '\n';
    chainedHash.insert("123", 123);
    int32_t res;
    if (chainedHash.search("123", res))
    {
        std::cout << res << '\n';
    }
    else
    {
        std::cout << "Not found key " << '\n';
    }
    chainedHash.erase("123");
    if (chainedHash.search("123", res))
    {
        std::cout << res << '\n';
    }
    else
    {
        std::cout << "Not found key" << '\n';
    }
}