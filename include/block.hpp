#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "record.hpp"
#include <vector>
#include <cstdio>

class DiskBlock {
public:
    DiskBlock(std::vector<Field> recordFields);
    void ReadFromFile(FILE* file);
    void WriteToFile(FILE* file);
    static const int SIZE = 4096;

private:
    std::vector<Field> m_recordFields;
    std::vector<Record> m_records;
    Record m_header;
    char m_buffer[DiskBlock::SIZE];
    short m_bufferPos{ 0 };
    static const int MAGIC_NUMBER = 4294967291;
    static const int magicNumberPos = 1;
};

#endif // !BLOCK_HPP
