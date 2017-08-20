#include "block.hpp"
#include "field.hpp"
#include "utils.hpp"
#include <cstdio>
#include <vector>

DiskBlock::DiskBlock(std::vector<Field> recordFields)
{
    m_header.m_data.emplace_back(Field::asInteger(DiskBlock::MAGIC_NUMBER));
    m_header.m_data.emplace_back(Field::asInteger(0)); //Registros no bloco
    m_recordFields = recordFields;
}

void DiskBlock::ReadFromFile(FILE* file)
{
    fread(m_buffer, sizeof(char), DiskBlock::SIZE, file);
    m_bufferPos = m_header.readFromBuffer(m_buffer, m_bufferPos);
    m_records.resize(m_header.m_data[0].m_integer);
    m_bufferPos = Utils::readVectorFromBuffer(m_buffer, m_records, m_bufferPos);
}

void DiskBlock::WriteToFile(FILE* file)
{
    m_header.m_data[0].m_integer = m_records.size();
    m_bufferPos = m_header.writeToBuffer(m_buffer, m_bufferPos);
    m_bufferPos = Utils::writeVectorToBuffer(m_buffer, m_records, m_bufferPos);
    fwrite(m_buffer, sizeof(char), DiskBlock::SIZE, file);
}