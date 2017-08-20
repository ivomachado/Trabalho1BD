#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>

namespace Utils {

template <typename T>
short writeVectorToBuffer(char* buffer, std::vector<T> &m_data, short begin)
{
    for (auto field : m_data) {
        begin = field.writeToBuffer(buffer, begin);
    }
    return begin;
}

template <typename T>
short readVectorFromBuffer(char* buffer, std::vector<T> &m_data, short begin)
{
    for (auto& field : m_data) {
        begin = field.readFromBuffer(buffer, begin);
    }
    return begin;
}

}

#endif // !UTILS_HPP
