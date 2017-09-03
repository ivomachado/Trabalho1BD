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
    std::vector<Field> otherBlockFields{ Field::asByteArray(DiskBlock::AVAILABLE_SIZE) };
    std::vector<DiskBlock> headerBlocks;

    headerBlocks.emplace_back(firstBlockFields);

    headerBlocks[0].readFromFile(m_file);
    m_overflowBlocks = headerBlocks[0].m_records[0].m_data[0].m_integer;
    for (int i = 1; i < HashFile::NUMBER_BLOCKS_HEADER; i++) {
        headerBlocks.emplace_back(otherBlockFields);
        headerBlocks[i].readFromFile(m_file);
    }
    m_blocksMap = Utils::BitMap(headerBlocks);
}

void HashFile::writeHeaderToDisk()
{
    std::vector<Field> firstBlockFields{ Field::asInteger(m_overflowBlocks), Field::asByteArray(DiskBlock::AVAILABLE_SIZE - 4) };
    std::vector<Field> otherBlockFields{ Field::asByteArray(DiskBlock::AVAILABLE_SIZE) };
    std::vector<DiskBlock> headerBlocks;

    headerBlocks.emplace_back(firstBlockFields);
    headerBlocks.back().m_records.emplace_back(firstBlockFields);
    fseek(m_file, 0, SEEK_SET);

    for (int i = 1; i < HashFile::NUMBER_BLOCKS_HEADER; i++) {
        headerBlocks.emplace_back(otherBlockFields);
        headerBlocks.back().m_records.emplace_back(otherBlockFields);
    }

    m_blocksMap.write(headerBlocks);
    for (int i = 0; i < HashFile::NUMBER_BLOCKS_HEADER; i++) {
        headerBlocks[i].writeToFile(m_file);
    }
}

int32_t HashFile::insert(Record rec)
{
    int32_t blockIndex = rec.m_data[m_fieldHashIndex].hash(HashFile::NUMBER_BLOCKS);
    fseek(m_file, Utils::calcBlockOffset(blockIndex, HashFile::NUMBER_BLOCKS_HEADER), SEEK_SET);
    DiskBlock choosenBlock(rec.m_data);
    if(m_blocksMap.get(blockIndex)) {
        choosenBlock.readFromFile(m_file);
    } else {
        m_blocksMap.set(blockIndex, true);
        writeHeaderToDisk();
        fseek(m_file, Utils::calcBlockOffset(blockIndex, HashFile::NUMBER_BLOCKS_HEADER), SEEK_SET);
    }
    while (!choosenBlock.insert(rec)) {
        blockIndex = choosenBlock.m_header.m_data[1].m_integer;
        if (blockIndex == 0) {
            blockIndex = choosenBlock.m_header.m_data[1].m_integer = HashFile::NUMBER_BLOCKS + m_overflowBlocks++;
            fseek(m_file, -DiskBlock::SIZE, SEEK_CUR);
            choosenBlock.writeToFile(m_file);
            writeHeaderToDisk();
            fseek(m_file, Utils::calcBlockOffset(blockIndex, HashFile::NUMBER_BLOCKS_HEADER), SEEK_SET);
            choosenBlock.m_header.m_data[0].m_integer = 0;
            choosenBlock.m_header.m_data[1].m_integer = 0;
            choosenBlock.m_records.resize(0);
        } else {
            fseek(m_file, Utils::calcBlockOffset(blockIndex, HashFile::NUMBER_BLOCKS_HEADER), SEEK_SET);
            choosenBlock.readFromFile(m_file);
        }
    }
    choosenBlock.writeToFile(m_file);
    return blockIndex;
}


std::pair<Record, int32_t> HashFile::search(Field field, std::vector<Field> recordFields)
{
    int32_t numberBlocksVisited = 0;
    int32_t blockIndex = field.hash(HashFile::NUMBER_BLOCKS);
    DiskBlock choosenBlock(recordFields);
    if (m_blocksMap.get(blockIndex)) {
        do {
            numberBlocksVisited++;
            fseek(m_file, Utils::calcBlockOffset(blockIndex, HashFile::NUMBER_BLOCKS_HEADER), SEEK_SET);
            choosenBlock.readFromFile(m_file);
            for(auto& rec : choosenBlock.m_records) {
                if(rec.m_data[m_fieldHashIndex] == field) {
                    return std::make_pair(rec, numberBlocksVisited);
                }
            }
            blockIndex = choosenBlock.m_header.m_data[1].m_integer;
        } while (blockIndex != 0);
    }
    return std::make_pair(Record(), -1);
}
