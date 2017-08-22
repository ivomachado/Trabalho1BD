#include "hashfile.hpp"
#include "field.hpp"

HashFile::HashFile()
{
}

HashFile::HashFile(std::string filename, std::string mode)
{
    m_file = fopen(filename.c_str(), mode.c_str());
}

HashFile::~HashFile()
{
    if (m_file != nullptr) {
        fclose(m_file);
    }
}

HashFile HashFile::Create(std::string filename)
{
    HashFile hashfile(filename, std::string("wb+"));
    hashfile.m_blocksMap = Utils::BitMap((DiskBlock::AVAILABLE_SIZE-4)*8);
    return hashfile;
}

HashFile HashFile::Open(std::string filename)
{
    HashFile hashfile(filename, std::string("rb+"));
    hashfile.readHeaderFromDisk();
    return hashfile;
}

void HashFile::readHeaderFromDisk()
{
    std::vector<Field> firstBlockFields{ Field::asInteger(), Field::asByteArray(DiskBlock::AVAILABLE_SIZE - 4) };
    DiskBlock firstBlock(firstBlockFields);
    firstBlock.ReadFromFile(m_file);
    m_overflowBlocks = firstBlock.m_records[0].m_data[0].m_integer;
    m_blocksMap = Utils::BitMap(firstBlock.m_records);
}

void HashFile::writeHeaderToDisk()
{
    std::vector<Field> firstBlockFields{ Field::asInteger(m_overflowBlocks), Field::asByteArray(DiskBlock::AVAILABLE_SIZE - 4) };
    DiskBlock firstBlock(firstBlockFields);
    Record firstHeader(firstBlockFields);
    firstBlock.insert(firstHeader);
    m_blocksMap.write(firstBlock.m_records);
    firstBlock.WriteToFile(m_file);
}
