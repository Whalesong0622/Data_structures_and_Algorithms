/*
    author:whaleshark
    email:whaleshark622@gmail.com
    date:2022.06.15
*/
#ifndef _EXTENDIBLE_HASHING_H_
#define _EXTENDIBLE_HASHING_H_
#include <bits/stdc++.h>

template <typename KeyType, typename ValueType>
class extendibleHash
{
private:
    int _global;
    int _max_bucket_size;
    struct Node
    {
        int _local;
        std::vector<std::pair<KeyType,ValueType> >Bucket;
        Node(int local) : _local(local) {};
    };
    std::vector<std::shared_ptr<Node>> _hash_table;
    int32_t getIndex(KeyType Key)
    {
        return std::hash<KeyType>{}(Key) % (1<<_global);
    };
public:
    extendibleHash(int32_t max_bucket_size) : _max_bucket_size(max_bucket_size)
    {
        _global = 1;
        _hash_table.resize(2);
        for (int i = 0; i < 2; i++)
        {
            _hash_table[i] = std::make_shared<Node>(1);
        }
    }
    void insert(KeyType key, ValueType value)
    {
        ValueType res;
        if(search(key,res) == true)return;
        int index = getIndex(key);
        auto hash_val = std::hash<KeyType>{}(key);
        auto ptr(_hash_table[index]);
        while(ptr->Bucket.size() == _max_bucket_size){
            if(ptr->_local == _global){
                for(int i = 0;i < (1<<_global);i++){
                    _hash_table.push_back(_hash_table[i]);
                }
                _global++;
            }
            auto Node_zero = std::make_shared<Node>(ptr->_local+1);
            auto Node_one = std::make_shared<Node>(ptr->_local+1);
            for(auto it:ptr->Bucket){
                auto hash_val = std::hash<KeyType>{}(it.first);
                if(hash_val&(1<<(ptr->_local))){
                    Node_one->Bucket.push_back(it);
                }else{
                    Node_zero->Bucket.push_back(it);
                }
            }
            int zero_index,one_index;
            if(index+(1<<(_global-1)) >= _hash_table.size()){
                zero_index = index-(1<<(_global-1));
                one_index = index;
            }else{
                zero_index = index;
                one_index = index+(1<<(_global-1));
            }
            _hash_table[zero_index] = Node_zero;
            _hash_table[one_index] = Node_one;
            if(hash_val&(1<<(ptr->_local))){
                ptr = Node_one;
            }else{
                ptr = Node_zero;
            }
        }
        ptr->Bucket.push_back(std::make_pair(key,value));
    };
    bool search(KeyType key, ValueType &res)
    {
        int index = getIndex(key);
        auto ptr(_hash_table[index]);
        for(auto it:ptr->Bucket){
            if(it.first == key){
                res = it.second;
                return true;
            }
        }
        return false;
    };
    void erase(KeyType key)
    {
        int index = getIndex(key);
        auto ptr(_hash_table[index]);
        for(int i = 0;i < ptr->Bucket.size();i++){
            auto it = ptr->Bucket[i];
            if(it.first == key){
                ptr->Bucket.erase(ptr->Bucket.begin()+i);
                return;
            }
        }
    };
    void show(){
        std::cout<<"global:"<<_global<<'\n';
        for(int i = 0;i < (1<<_global);i++){
            std::cout<<"_hash_table["<<i<<"],"<<_hash_table[i]->_local<<'\n';
            for(auto it:_hash_table[i]->Bucket){
                std::cout<<"hash:"<<(std::hash<KeyType>{}(it.first)%(1<<_global))
                <<",key:"<<it.first<<",val:"<<it.second<<'\n';
            }
        }
        std::cout<<"show end"<<'\n';
    }
};

#endif