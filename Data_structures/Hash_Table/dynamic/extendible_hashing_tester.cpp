#include "extendible_hashing.h"

int main()
{
    extendibleHash<std::string,int> HashTb(3);
    for(int i = 0;i < 16;i++){
        HashTb.insert(std::to_string(i),i);
        if(i%3 == 0 && i != 0){
            // HashTb.show();
        }
    }
    HashTb.show();
}