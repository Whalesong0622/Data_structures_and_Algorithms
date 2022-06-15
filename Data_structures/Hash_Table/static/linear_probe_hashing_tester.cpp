#include "linear_probe_hashing.h"

int main()
{
    linearProbeHash<std::string,int> HashTb(5);
    for(int i = 0;i < 10;i++){
        HashTb.insert(std::to_string(i),i);
    }
    HashTb.show();
    HashTb.erase(std::to_string(1));
    HashTb.show();
}