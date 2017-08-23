#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>
#include <cstdint>
#include <iostream>

enum class DataTypes { Invalid,
    Integer,
    String,
    ByteArray };

class Field {
public:
    short m_maxSize;
    DataTypes m_type{ DataTypes::Invalid };
    Field(DataTypes type);
    Field() {}
    int32_t m_integer;
    std::string m_string;
    static Field asInteger();
    static Field asInteger(int32_t value);
    static Field asString(short maxSize);
    static Field asByteArray(short maxSize);
    static Field asString(const char* data, short maxSize);
    int32_t hash(int32_t size);
    short size();
    short writeToBuffer(char* buffer, short begin);
    short readFromBuffer(char* buffer, short begin);
    friend bool operator==(const Field& a, const Field& b);
    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

#endif
