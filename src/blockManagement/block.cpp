#include "block.hpp"
#include "field.hpp"
#include "utils.hpp"
#include <cstdio>
#include <vector>

DiskBlock::DiskBlock(std::vector<Field>& recordFields)
{
    m_header.m_data.emplace_back(Field::asInteger(0)); //Registros no bloco
    m_header.m_data.emplace_back(Field::asInteger(0)); //Apontador para o de overflow
    m_recordFields = recordFields;
    for (auto& field : m_recordFields) {
        m_recordSize += field.size();
    }
}

void DiskBlock::readFromFile(FILE* file)
{
    fread(m_buffer, sizeof(char), DiskBlock::SIZE, file);
    readFromBuffer();
}

void DiskBlock::writeToFile(FILE* file)
{
    writeToBuffer();
    fwrite(m_buffer, sizeof(char), DiskBlock::SIZE, file);
}

void DiskBlock::writeToBuffer()
{
    m_header.m_data[0].m_integer = static_cast<int>(m_records.size());
    m_bufferPos = m_header.writeToBuffer(m_buffer, 0);
    m_bufferPos = Utils::writeVectorToBuffer(m_buffer, m_records, m_bufferPos);
}

void DiskBlock::readFromBuffer()
{
    m_bufferPos = m_header.readFromBuffer(m_buffer, 0);
    int numberOfRecords = m_header.m_data[0].m_integer;
    m_records.resize(0);
    for (int i = 0; i < numberOfRecords; i++) {
        m_records.emplace_back(m_recordFields);
    }
    m_bufferPos = Utils::readVectorFromBuffer(m_buffer, m_records, m_bufferPos);
}

bool DiskBlock::fitOneMoreRecord() {
    return (m_records.size() + 1) * m_recordSize <= DiskBlock::AVAILABLE_SIZE;
}

bool DiskBlock::insert(const Record& record)
{
    if(fitOneMoreRecord()) {
        m_records.push_back(record);
        return true;
    }
    return false;
}
