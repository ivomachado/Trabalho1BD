#include "hashfile.hpp"
#include "field.hpp"

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
    hashfile.m_blocksMap = Utils::BitMap(HashFile::NUMBER_BLOCKS);
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
    firstBlock.readFromFile(m_file);
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
    fseek(m_file, 0, SEEK_SET);
    firstBlock.writeToFile(m_file);
}

int32_t calcBlockOffset(int32_t blockIndex)
{
    return (blockIndex + 1) * DiskBlock::SIZE;
}

int32_t HashFile::insert(Record rec)
{
    int32_t blockIndex = rec.m_data[m_fieldHashIndex].hash(HashFile::NUMBER_BLOCKS);
    fseek(m_file, calcBlockOffset(blockIndex), SEEK_SET);
    DiskBlock choosenBlock(rec.m_data);
    if(m_blocksMap.get(blockIndex)) {
        choosenBlock.readFromFile(m_file);
    } else {
        m_blocksMap.set(blockIndex, true);
        writeHeaderToDisk();
        fseek(m_file, calcBlockOffset(blockIndex), SEEK_SET);
    }
    while (!choosenBlock.insert(rec)) {
        blockIndex = choosenBlock.m_header.m_data[1].m_integer;
        if (blockIndex == 0) {
            blockIndex = choosenBlock.m_header.m_data[1].m_integer = HashFile::NUMBER_BLOCKS + m_overflowBlocks++;
            fseek(m_file, -DiskBlock::SIZE, SEEK_CUR);
            choosenBlock.writeToFile(m_file);
            writeHeaderToDisk();
            fseek(m_file, calcBlockOffset(blockIndex), SEEK_SET);
            choosenBlock.m_header.m_data[0].m_integer = 0;
            choosenBlock.m_header.m_data[1].m_integer = 0;
            choosenBlock.m_records.resize(0);
        } else {
            fseek(m_file, calcBlockOffset(blockIndex), SEEK_SET);
            choosenBlock.readFromFile(m_file);
        }
    }
    choosenBlock.writeToFile(m_file);
    return blockIndex;
}
