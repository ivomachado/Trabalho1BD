#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "record.hpp"
#include <cstdio>
#include <vector>

class DiskBlock {
public:
    DiskBlock(std::vector<Field>& recordFields);
    void ReadFromFile(FILE* file);
    void WriteToFile(FILE* file);
    static const int SIZE = 4096;
    static const int AVAILABLE_SIZE = 4092; //Menos o inteiro
    std::vector<Record> m_records;
    short m_recordSize{ 0 };
    char m_buffer[DiskBlock::SIZE];
    std::vector<Field> m_recordFields;
    Record m_header;
    short m_bufferPos{ 0 };
    static const int MAGIC_NUMBER = 4294967291;
    static const int magicNumberPos = 1;
    void writeToBuffer();
    void readFromBuffer();
    bool insert(const Record& record);
};

#endif // !BLOCK_HPP
