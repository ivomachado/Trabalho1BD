#include "indexfile.hpp"
#include "block.hpp"
#include "utils.hpp"
#include <algorithm>
#include <vector>

IndexFile::IndexFile(std::string filename, std::string mode)
{
    m_file = fopen(filename.c_str(), mode.c_str());
}

IndexFile::~IndexFile()
{
    if (m_file != nullptr) {
        fclose(m_file);
    }
}

IndexFile IndexFile::Create(std::string filename)
{
    IndexFile indexfile(filename, std::string("wb+"));
    return indexfile;
}

IndexFile IndexFile::Open(std::string filename)
{
    IndexFile indexfile(filename, std::string("rb+"));
    indexfile.readHeaderFromDisk();
    return indexfile;
}

void IndexFile::writeHeaderToDisk()
{
    std::vector<Field> firstBlockFields{ Field::asInteger(m_locatedBlocks), Field::asInteger(m_root) };
    DiskBlock firstBlock(firstBlockFields);
    Record header(firstBlockFields);
    firstBlock.insert(header);
    fseek(m_file, 0, SEEK_SET);
    firstBlock.writeToFile(m_file);
}

void IndexFile::readHeaderFromDisk()
{
    std::vector<Field> firstBlockFields{ Field::asInteger(), Field::asInteger() };
    DiskBlock firstBlock(firstBlockFields);
    firstBlock.readFromFile(m_file);
    m_locatedBlocks = firstBlock.m_records[0].m_data[0].m_integer;
    m_root = firstBlock.m_records[0].m_data[1].m_integer;
}

int IndexFile::findLocation(Field field, DiskBlock block)
{

    if (field <= block.m_records.front().m_data[0])
        return -1;
    if (field > block.m_records.back().m_data[0])
        return block.m_records.size() - 1;

    for (size_t i = 0; i < (block.m_records.size() - 1); i++) {
        if (field > block.m_records[i].m_data[0] && field <= block.m_records[i + 1].m_data[0]) {
            return i;
        }
    }

    return -2;
}

bool IndexFile::isLeaf(DiskBlock block)
{
    if(block.m_header.m_data[1].m_integer != -1) {
        return false;
    }
    for (size_t i = 0; i < block.m_records.size(); i++) {
        if (block.m_records[i].m_data[2].m_integer != -1) {
            return false;
        }
    }

    return true;
}

bool IndexFile::compare(Record r1, Record r2)
{
    if (r1.m_data[0] == r2.m_data[0])
        return false;
    return (r1.m_data[0] > r2.m_data[0]);
}

Record IndexFile::split(DiskBlock& block)
{
    DiskBlock newBlock(block.m_recordFields);
    int middle = block.m_records.size() / 2;
    Record middleKeyRecord = block.m_records[middle];
    newBlock.m_records.assign(block.m_records.begin() + middle + 1, block.m_records.end());
    block.m_records.erase(block.m_records.begin() + middle, block.m_records.end());
    newBlock.m_header.m_data[1].m_integer = middleKeyRecord.m_data[2].m_integer;
    middleKeyRecord.m_data[2].m_integer = m_locatedBlocks;
    writeHeaderToDisk();
    fseek(m_file, Utils::calcBlockOffset(m_locatedBlocks), SEEK_SET);
    newBlock.writeToFile(m_file);
    m_locatedBlocks++;
    return middleKeyRecord;
}

Record IndexFile::insertNonFull(DiskBlock& block, int32_t blockOffset, Field field, int32_t dataBlockIndex)
{
    //if leaf insert and write to file
    if (isLeaf(block)) {
        std::vector<Field> recordFields{ field, Field::asInteger(dataBlockIndex), Field::asInteger(-1) };
        Record record(recordFields);

        block.m_records.push_back(record);
        std::sort(block.m_records.begin(), block.m_records.end(), [](const Record& a, const Record& b) -> bool {
            return a.m_data[0] <= b.m_data[0];
        });
        Record rec;
        if (block.m_records.size() > m_order) {
            rec = split(block);
        }
        fseek(m_file, Utils::calcBlockOffset(blockOffset), SEEK_SET);
        block.writeToFile(m_file);
        return rec;
    } else {
        //find position
        int index = findLocation(field, block);
        int childOffset;

        //read the child

        //if the child is pointed by the overflow pointer
        if (index == -1) {
            childOffset = block.m_header.m_data[1].m_integer;
        } else {
            childOffset = block.m_records[index].m_data[2].m_integer;
        }
        fseek(m_file, Utils::calcBlockOffset(childOffset), SEEK_SET);

        DiskBlock childBlock(block.m_recordFields);
        childBlock.readFromFile(m_file);

        Record resultadoInsercao = insertNonFull(childBlock, childOffset, field, dataBlockIndex);

        if (resultadoInsercao.m_data.size() != 0) {
            block.m_records.push_back(resultadoInsercao);
            std::sort(block.m_records.begin(), block.m_records.end(), [](const Record& a, const Record& b) -> bool {
                return a.m_data[0] <= b.m_data[0];
            });
            Record resultadoSplit;
            if (block.m_records.size() > m_order) {
                resultadoSplit = split(block);
            }
            fseek(m_file, Utils::calcBlockOffset(blockOffset), SEEK_SET);
            block.writeToFile(m_file);
            return resultadoSplit;
        }
    }
    return Record();
}

void IndexFile::insert(Field field, int32_t dataBlockIndex)
{

    std::vector<Field> blockFields{ field, Field::asInteger(), Field::asInteger() };
    std::vector<Field> recordFields{ field, Field::asInteger(dataBlockIndex), Field::asInteger(-1) };
    Record record(recordFields);
    if (m_order == 0) {
        int recordSize = 0;
        for (auto& field : recordFields) {
            recordSize += field.size();
        }
        m_order = DiskBlock::AVAILABLE_SIZE / recordSize;
        m_order = m_order % 2 == 1 ? m_order - 1 : m_order;
    }

    if (m_locatedBlocks == 0) {
        DiskBlock rootBlock(blockFields);
        rootBlock.m_header.m_data[1].m_integer = -1;

        rootBlock.insert(record);

        m_root = 0;
        m_locatedBlocks++;

        writeHeaderToDisk();
        fseek(m_file, Utils::calcBlockOffset(m_root), SEEK_SET);
        rootBlock.writeToFile(m_file);
    } else {
        //read root from disk
        DiskBlock rootBlock(blockFields);
        fseek(m_file, Utils::calcBlockOffset(m_root), SEEK_SET);
        rootBlock.readFromFile(m_file);

        Record rec = insertNonFull(rootBlock, m_root, field, dataBlockIndex);
        if(rec.m_data.size()  > 0) {
            DiskBlock newRoot(rootBlock.m_recordFields);
            newRoot.m_header.m_data[1].m_integer = m_root;
            newRoot.m_records.push_back(rec);
            m_root = m_locatedBlocks;
            m_locatedBlocks++;
            fseek(m_file, Utils::calcBlockOffset(m_root), SEEK_SET);
            newRoot.writeToFile(m_file);
            writeHeaderToDisk();
        }
    }
}

int32_t IndexFile::search(Field field)
{
    std::vector<Field> blockFields{ field, Field::asInteger(), Field::asInteger() };
    int32_t blockOffset = m_root;
    DiskBlock block(blockFields);
    while (true) {
        if (blockOffset == -1) {
            return -1;
        }
        fseek(m_file, Utils::calcBlockOffset(blockOffset), SEEK_SET);
        block.readFromFile(m_file);
        size_t index = findLocation(field, block) + 1;
        if (index != block.m_records.size()) {
            if (block.m_records[index].m_data[0] == field) {
                return block.m_records[index].m_data[1].m_integer;
            }
        }
        if (index == 0) {
            blockOffset = block.m_header.m_data[1].m_integer;
        } else {
            blockOffset = block.m_records[index - 1].m_data[2].m_integer;
        }
    }
}
