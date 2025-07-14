#ifndef UTILS_HPP
#define UTILS_HPP

#include "block.hpp"
#include "record.hpp"
#include <cstdint>
#include <iostream>
#include <vector>

/**
 * Contains utilities that are not directly related to the main problem but are helpful.
 * 
 * @author Ivo Machado
 */
namespace Utils {

/**
 * Writes the vector `m_data` to the buffer.
 * 
 * @author Ivo Machado
 */
template <typename T>
short writeVectorToBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto field : m_data) {
        begin = field.writeToBuffer(buffer, begin);
    }
    return begin;
}

/**
 * Reads the vector `m_data` from the buffer.
 * 
 * @author Ivo Machado
 */
template <typename T>
short readVectorFromBuffer(char* buffer, std::vector<T>& m_data, short begin)
{
    for (auto& field : m_data) {
        begin = field.readFromBuffer(buffer, begin);
    }
    return begin;
}

/**
 * Converts the integer `value` to a 4-char array and writes it to the buffer.
 * 
 * @author Ivo Machado
 */
inline void intToCharArray(int32_t value, char* buffer)
{
    buffer[0] = (value >> 24) & 0xFF;
    buffer[1] = (value >> 16) & 0xFF;
    buffer[2] = (value >> 8) & 0xFF;
    buffer[3] = value & 0xFF;
}

/**
 * Converts a 4-char array to an integer.
 * 
 * @author Ivo Machado
 */
inline int32_t charArrayToInt(char* buffer)
{
    int32_t num = ((buffer[0] & 0xFF) << 24) | ((buffer[1] & 0xFF) << 16) | ((buffer[2] & 0xFF) << 8) | (0xFF & (buffer[3]));
    return num;
}

/**
 * Abstracts a bitmap to facilitate setting and clearing bits.
 * 
 * @author Ivo Machado
 */
class BitMap {
public:
    /** Stores the bytes in memory */
    std::string m_data{ "" };

    /**
     * Default constructor with 0 capacity.
     * 
     * @author Ivo Machado
     */
    BitMap()
        : BitMap(0)
    {
    }

    /**
     * Creates a bitmap with data from the ByteArray fields of the blocks
     * passed as parameters.
     * 
     * @author Ivo Machado
     */
    BitMap(const std::vector<DiskBlock>& data)
    {
        for (auto& block : data) {
            for (auto& rec : block.m_records) {
                for (auto& field : rec.m_data) {
                    if (field.m_type == DataTypes::ByteArray) {
                        for (int i = 0; i < field.m_maxSize; i++) {
                            m_data += field.m_string[i];
                        }
                    }
                }
            }
        }
    }

    /**
     * Creates a bitmap with a capacity that is the first multiple of 8
     * greater than or equal to the requested size.
     * 
     * @author Ivo Machado
     */
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

    /**
     * Returns the boolean value at the specified position.
     * 
     * @author Ivo Machado
     */
    bool get(int32_t pos)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        return (m_data[charIndex] & (1 << bitIndex)) > 0;
    }

    /**
     * Assigns the given value to the requested position.
     * 
     * @author Ivo Machado
     */
    void set(int32_t pos, bool value)
    {
        int32_t charIndex = pos / 8;
        int32_t bitIndex = pos % 8;

        m_data[charIndex] = value ? m_data[charIndex] | (1 << bitIndex) : m_data[charIndex] & (~(1 << bitIndex));
    }

    /**
     * Writes the bitmap, divided among the ByteArray attributes of several blocks.
     * 
     * @author Ivo Machado
     */
    void write(std::vector<DiskBlock>& data)
    {
        int pos = 0;
        for (auto& block : data) {
            for (auto& rec : block.m_records) {
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
    }
};

/**
 * Calculates the byte offset of the requested block, considering the file header overhead.
 * 
 * @author Ivo Machado
 */
inline int64_t calcBlockOffset(int32_t blockIndex, int32_t headerOverhead = 1)
{
    return (static_cast<int64_t>(blockIndex) + static_cast<int64_t>(headerOverhead)) * static_cast<int64_t>(DiskBlock::SIZE);
}
}

#endif // !UTILS_HPP