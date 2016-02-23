#ifndef _L_TABLE_H
#define _L_TABLE_H


#include <map>


template <typename T>
class CTable
{
public:
    CTable();
    virtual ~CTable();


    bool LoadAndParseTable(){
        return true;
    }

private:
    std::map<int, T> _data;
};

#endif