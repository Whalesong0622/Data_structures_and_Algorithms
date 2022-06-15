/*
    author:whaleshark
    email:whaleshark622@gmail.com
    date:2022.06.15
*/
#ifndef _LINEAR_PROBE_HASHING_H_
#define _LINEAR_PROBE_HASHING_H_
#include <bits/stdc++.h>

template <typename KeyType, typename ValueType>
class linearProbeHash
{
private:
    int32_t _size;
    int32_t _obj_num;
    struct Frame
    {
        KeyType _key;
        ValueType _value;
        bool tomb;
        bool valid;
        Frame() : tomb(false), valid(false){};
    };
    std::vector<Frame> _hash_table;
    int32_t getIndex(KeyType Key)
    {
        return std::hash<KeyType>{}(Key) % (_size);
    };

public:
    linearProbeHash(int32_t size) : _size(size), _obj_num(0)
    {
        _hash_table.resize(size);
    }
    bool insert(KeyType key, ValueType value)
    {
        if (_obj_num == _size)
            return false;
        int32_t index = getIndex(key);
        for (int i = 0; i < _size; i++)
        {
            int32_t cur_index = (index + i) % _size;
            if (_hash_table[cur_index].valid)
                continue;
            _hash_table[cur_index]._key = key;
            _hash_table[cur_index]._value = value;
            _hash_table[cur_index].valid = true;
            _hash_table[cur_index].tomb = true;
            _obj_num++;
            return true;
        }
        return false;
    };
    bool search(KeyType key, ValueType &res)
    {
        int32_t index = getIndex(key);
        for (int i = 0; i < _size; i++)
        {
            int32_t cur_index = (index + i) % _size;
            if (!_hash_table[cur_index].tomb)
                return false;
            if (_hash_table[cur_index]._key == key)
            {
                if(_hash_table[cur_index].valid){
                    res = _hash_table[cur_index].value;
                    return true;
                }else{
                    return false;
                }
            }
            return false;
        }
    };
    void erase(KeyType key){
        int32_t index = getIndex(key);
        for (int i = 0; i < _size; i++)
        {
            int32_t cur_index = (index + i) % _size;
            if (!_hash_table[cur_index].tomb)return;
            if (_hash_table[cur_index]._key == key)
            {
                _hash_table[cur_index].valid = false;
                return;
            }
            return;
        }
    };
    void show()
    {
        puts("-------");
        for(int i = 0;i < _size;i++){
            if(_hash_table[i].valid){
                std::cout<<i<<":"<<_hash_table[i]._key<<" "<<_hash_table[i]._value<<'\n';
            }else{
                std::cout<<i<<":NULL"<<'\n';
            }
        }
        puts("-------");
    }
};

#endif