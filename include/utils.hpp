#ifndef UTILS_HPP
#define UTILS_HPP

#include "block.hpp"
#include "record.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

namespace Utils {

template <typename T>
short writeVectorToBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto field : m_data) {
        begin = field.writeToBuffer(buffer, begin);
    }
    return begin;
}

template <typename T>
short readVectorFromBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto& field : m_data) {
        begin = field.readFromBuffer(buffer, begin);
    }
    return begin;
}

inline void intToCharArray(int32_t value, char* buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

inline int32_t charArrayToInt(char* buffer)
{
    int32_t num = ((buffer[0] & 0xFF) << 24) | ((buffer[1] & 0xFF) << 16) | ((buffer[2] & 0xFF) << 8) | (0xFF & (buffer[3]));
    return num;
}

class BitMap {
public:
    std::string m_data{ "" };
    BitMap()
        : BitMap(0)
    {
    }
    BitMap(const std::vector<Record>& data)
    {
        for (auto& rec : data) {
            for (auto& field : rec.m_data) {
                if (field.m_type == DataTypes::ByteArray) {
                    for (int i = 0; i < field.m_maxSize; i++) {
                        m_data += field.m_string[i];
                    }
                }
            }
        }
    }

    BitMap(int32_t size)
    {
        if (size % 8 == 0) {
            size /= 8;
        } else {
            size /= 8;
            size++;
        }
        m_data = std::string(size, static_cast<char>(0));
    }

    bool get(int32_t pos)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        return (m_data[charIndex] & (1 << bitIndex)) > 0;
    }

    void set(int32_t pos, bool value)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        m_data[charIndex] = value ? m_data[charIndex] | (1 << bitIndex) : m_data[charIndex] & (~(1 << bitIndex));
    }

    void write(std::vector<Record>& data)
    {
        int pos = 0;
        for (auto& rec : data) {
            for (auto& field : rec.m_data) {
                if (field.m_type == DataTypes::ByteArray) {
                    for (int i = 0; i < field.m_maxSize; i++) {
                        field.m_string[i] = m_data[pos + i];
                    }
                    pos += field.m_maxSize;
                }
            }
        }
    }
};

inline int32_t calcBlockOffset(int32_t blockIndex)
{
    return (blockIndex + 1) * DiskBlock::SIZE;
}
}

#endif // !UTILS_HPP
