#include "field.hpp"
#include "utils.hpp"
#include <cstdio>
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
    strcpy(field.m_string, data);
    return field;
}

short Field::writeToBuffer(char* buffer, short begin)
{
    switch (m_type) {
    case DataTypes::Integer:
        Utils::intToCharArray(m_integer, buffer + begin);
        return begin + sizeof(int);
    case DataTypes::String:
        strcpy(buffer + begin, m_string);
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
        strcpy(m_string, buffer + begin);
        return m_maxSize + begin;
    case DataTypes::Invalid:
        return begin;
    }
    return begin;
}

bool operator==(const Field& a, const Field& b) {
    if(a.m_type == b.m_type) {
        switch(a.m_type) {
            case DataTypes::Integer:
                return a.m_integer == b.m_integer;
            case DataTypes::String:
                return a.m_string == b.m_string;
            case DataTypes::Invalid:
                return false;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Field& field) {
    switch (field.m_type) {
    case DataTypes::Integer:
        return os << field.m_integer;
    case DataTypes::String:
        return os << field.m_string;
    case DataTypes::Invalid:
        return os;
    }
    return os;
}

Field::~Field()
{
    if (m_string != nullptr) {
        // delete[] m_string;
    }
}
