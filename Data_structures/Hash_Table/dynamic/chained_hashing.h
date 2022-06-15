/*
    author:whaleshark
    email:whaleshark622@gmail.com
    date:2022.06.05
*/
#ifndef _CHAINED_HASHING_H_
#define _CHAINED_HASHING_H_
#include <bits/stdc++.h>

template <typename KeyType, typename ValueType>
class chainedHash
{
private:
    int _table_size;
    struct ChainNode
    {
        KeyType _key;
        ValueType _value;
        std::shared_ptr<ChainNode> _nxt;
        ChainNode(KeyType key, ValueType value) : _key(key), _value(value), _nxt(nullptr){};
        ChainNode(){};
    };
    std::vector<std::shared_ptr<ChainNode>> _hash_table;
    int32_t getIndex(KeyType Key)
    {
        return std::hash<KeyType>{}(Key) % _table_size;
    };

public:
    chainedHash(int32_t table_size) : _table_size(table_size)
    {
        _hash_table.resize(table_size);
        for (int i = 0; i < table_size; i++)
        {
            _hash_table[i] = std::make_shared<ChainNode>(KeyType(), ValueType());
        }
    }
    void insert(KeyType key, ValueType value)
    {
        int index = getIndex(key);
        auto node_ptr = std::make_shared<ChainNode>(key, value);
        auto cur_ptr(_hash_table[index]);
        while (cur_ptr->_nxt != nullptr)
        {
            cur_ptr = cur_ptr->_nxt;
        }
        cur_ptr->_nxt = node_ptr;
    };
    bool search(KeyType key, ValueType &res)
    {
        int index = getIndex(key);
        auto ptr(_hash_table[index]);
        ptr = ptr->_nxt;
        while (ptr != nullptr)
        {
            if (ptr->_key == key)
            {
                res = ptr->_value;
                return true;
            }
            ptr = ptr->_nxt;
        }
        return false;
    };
    void erase(KeyType key)
    {
        int index = getIndex(key);
        auto ptr(_hash_table[index]);
        while (ptr != nullptr)
        {
            if (ptr->_nxt->_key == key)
            {
                ptr->_nxt = ptr->_nxt->_nxt;
                return;
            }
            ptr = ptr->_nxt;
        }
    };
};

#endif