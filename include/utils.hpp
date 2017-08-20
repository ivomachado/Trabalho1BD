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

inline void intToCharArray(int value, char* buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

inline int charArrayToInt(char* buffer)
{
    int num = ((buffer[0] & 0xFF) << 24) | ((buffer[1] & 0xFF) << 16) | ((buffer[2] & 0xFF) << 8) | (0xFF & (buffer[3]));
    return num;
}
}

#endif // !UTILS_HPP
