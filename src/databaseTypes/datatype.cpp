#include "datatype.hpp"
#include <cstdio>
#include <cstring>

databaseTypes::Integer::Integer(int value)
    : m_data{ value }
{
}

databaseTypes::Integer::Integer()
{
}

databaseTypes::String::String(const char* data, short maxSize)
    : databaseTypes::String::String(maxSize)
{
    strcpy(m_data, data);
}

databaseTypes::String::String(short maxSize)
: m_maxSize{ maxSize }
{
    m_data = new char[maxSize];
}

short databaseTypes::String::writeBuffer(char* buffer, short begin)
{
    strcpy(buffer + begin, m_data);
    return strlen(m_data) + begin;
}

short databaseTypes::Integer::writeBuffer(char* buffer, short begin)
{
    sprintf(buffer + begin, "%d", m_data);
    return begin + sizeof(int);
}

short databaseTypes::String::readBuffer(char* buffer, short begin)
{
    strcpy(m_data, buffer + begin);
    return strlen(m_data) + begin;
}

short databaseTypes::Integer::readBuffer(char* buffer, short begin)
{
    sscanf(buffer + begin, "%d", &m_data);
    return begin + sizeof(int);
}
