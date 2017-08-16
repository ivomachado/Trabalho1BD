#include "record.hpp"

Record::Record(const std::vector<Field>& data)
    : m_data{ data }
{
}

short Record::readFromBuffer(char* buffer, short begin)
{
    for(auto field: m_data) {
        begin = field.readFromBuffer(buffer, begin);
    }
    return begin;
}

short Record::writeToBuffer(char* buffer, short begin)
{
    for(auto field: m_data) {
        begin = field.writeToBuffer(buffer, begin);
    }
    return begin;
}
