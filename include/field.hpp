#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>
#include <cstdint>
#include <iostream>

enum class DataTypes { Invalid,
    Integer,
    String };

class Field {
public:
    short m_maxSize;
    DataTypes m_type{ DataTypes::Invalid };
    Field(DataTypes type);
    Field() {}
    ~Field();
    int m_integer;
    char* m_string{ nullptr };
    static Field asInteger();
    static Field asInteger(int32_t value);
    static Field asString(short maxSize);
    static Field asString(const char* data, short maxSize);
    short writeToBuffer(char* buffer, short begin);
    short readFromBuffer(char* buffer, short begin);
    friend bool operator==(const Field& a, const Field& b);
    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

#endif
