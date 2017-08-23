#include "field.hpp"
#include "utils.hpp"
#include <cstdio>
#include <functional>
#include <cstring>

Field::Field(DataTypes type)
    : m_type{ type }
{
}

Field Field::asInteger()
{
    return Field(DataTypes::Integer);
}

Field Field::asString(short maxSize)
{
    Field field(DataTypes::String);
    field.m_string = new char[maxSize];
    field.m_maxSize = maxSize;
    return field;
}

Field Field::asInteger(int32_t value)
{
    Field field = Field::asInteger();
    field.m_integer = value;
    return field;
}

Field Field::asString(const char* data, short maxSize)
{
    Field field = Field::asString(maxSize);
    field.m_string = std::string(data);
    return field;
}

Field Field::asByteArray(short maxSize)
{
    Field field(DataTypes::ByteArray);
    field.m_maxSize = maxSize;
    field.m_string = std::string(maxSize, static_cast<char>(0));
    return field;
}

short Field::writeToBuffer(char* buffer, short begin)
{
    switch (m_type) {
    case DataTypes::Integer:
        Utils::intToCharArray(m_integer, buffer + begin);
        return begin + sizeof(int);
    case DataTypes::String:
        strcpy(buffer + begin, m_string.c_str());
        return m_maxSize + begin;
    case DataTypes::ByteArray:
        for (short i = 0; i < m_maxSize; i++) {
            buffer[begin + i] = m_string[i];
        }
        return m_maxSize + begin;
    case DataTypes::Invalid:
        return begin;
    }
    return begin;
}

short Field::readFromBuffer(char* buffer, short begin)
{
    switch (m_type) {
    case DataTypes::Integer:
        sscanf(buffer + begin, "%d", &m_integer);
        m_integer = Utils::charArrayToInt(buffer + begin);
        return begin + sizeof(int);
    case DataTypes::String:
        m_string = std::string(buffer + begin);
        return m_maxSize + begin;
    case DataTypes::ByteArray:
        for (short i = 0; i < m_maxSize; i++) {
            m_string[i] = buffer[begin + i];
        }
        return m_maxSize + begin;
    case DataTypes::Invalid:
        return begin;
    }
    return begin;
}

bool operator==(const Field& a, const Field& b)
{
    if (a.m_type == b.m_type) {
        switch (a.m_type) {
        case DataTypes::Integer:
            return a.m_integer == b.m_integer;
        case DataTypes::String:
        case DataTypes::ByteArray:
            return a.m_string == b.m_string;
        case DataTypes::Invalid:
            return false;
        }
    }
    return false;
}

short Field::size()
{
    switch (m_type) {
    case DataTypes::Integer:
        return 4;
    case DataTypes::ByteArray:
    case DataTypes::String:
        return m_maxSize;
    case DataTypes::Invalid:
        return 0;
    }
    return 0;
}

int32_t Field::hash(int32_t size) {
    switch (m_type) {
    case DataTypes::Integer:
        return std::hash<int32_t>{}(m_integer) % size;
    case DataTypes::String:
    case DataTypes::ByteArray:
        return std::hash<std::string>{}(m_string) % size;
    case DataTypes::Invalid:
        return 0;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Field& field)
{
    switch (field.m_type) {
    case DataTypes::Integer:
        return os << field.m_integer;
    case DataTypes::String:
    case DataTypes::ByteArray:
        return os << field.m_string;
    case DataTypes::Invalid:
        return os;
    }
    return os;
}
