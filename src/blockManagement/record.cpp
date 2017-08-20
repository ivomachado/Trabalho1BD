#include "record.hpp"
#include "utils.hpp"

Record::Record() {}

Record::Record(const std::vector<Field>& data)
    : m_data{ data }
{
}

short Record::readFromBuffer(char* buffer, short begin)
{
    return Utils::readVectorFromBuffer(buffer, m_data, begin);
}

short Record::writeToBuffer(char* buffer, short begin)
{
    return Utils::writeVectorToBuffer(buffer, m_data, begin);
}
