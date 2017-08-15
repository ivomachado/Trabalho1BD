#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>

namespace databaseTypes {

class DataType {
public:
    short virtual writeBuffer(char* buffer, short begin) = 0;
    short virtual readBuffer(char* buffer, short begin) = 0;
};

class Integer : public DataType {
    
public:
    int m_data;
    short writeBuffer(char* buffer, short begin);
    short readBuffer(char* buffer, short begin);
    Integer(int value);
    Integer();
};

class String : public DataType {
public:
    short m_maxSize;
    char* m_data;
    short readBuffer(char* buffer, short begin);
    short writeBuffer(char* buffer, short begin);
    String(const char* data, short maxSize);
    String(short maxSize);
};
};

#endif
