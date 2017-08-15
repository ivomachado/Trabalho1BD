#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>

namespace databaseTypes {

class Field {
public:
    short virtual writeToBuffer(char* buffer, short begin) = 0;
    short virtual readFromBuffer(char* buffer, short begin) = 0;
};

class Integer : public Field {
    
public:
    int m_data;
    short writeToBuffer(char* buffer, short begin);
    short readFromBuffer(char* buffer, short begin);
    Integer(int value);
    Integer();
};

class String : public Field {
public:
    short m_maxSize;
    char* m_data;
    short readFromBuffer(char* buffer, short begin);
    short writeToBuffer(char* buffer, short begin);
    String(const char* data, short maxSize);
    String(short maxSize);
    ~String();
};
};

#endif
