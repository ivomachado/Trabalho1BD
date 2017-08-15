#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>

enum class DataTypes { Invalid,
    Integer,
    String };

class Field {
    short m_maxSize;
    DataTypes m_type{ DataTypes::Invalid };
    Field(DataTypes type);

public:
    Field() {}
    ~Field();
    int m_integer;
    char* m_string{ nullptr };
    static Field asInteger();
    static Field asInteger(int value);
    static Field asString(short maxSize);
    static Field asString(const char* data, short maxSize);
    short writeToBuffer(char* buffer, short begin);
    short readFromBuffer(char* buffer, short begin);
};

#endif
