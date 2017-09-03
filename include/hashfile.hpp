#ifndef HASHFILE_HPP
#define HASHFILE_HPP
#include "block.hpp"
#include "cstdint"
#include "cstdio"
#include "functional"
#include "record.hpp"
#include "utils.hpp"
#include "vector"
class HashFile {
public:
    int32_t insert(Record rec);
    FILE* m_file{ nullptr };
    ~HashFile();
    HashFile(std::string filename, std::string mode);
    static HashFile Create(std::string filename);
    static HashFile Open(std::string filename);
    static const int NUMBER_BLOCKS_HEADER = 46;
    static const int32_t NUMBER_BLOCKS{ (DiskBlock::AVAILABLE_SIZE * NUMBER_BLOCKS_HEADER - 4) * 8 };
    int m_fieldHashIndex{ 0 };
    Utils::BitMap m_blocksMap;
    void writeHeaderToDisk();
    void readHeaderFromDisk();
    int32_t m_overflowBlocks{ 0 };
    std::pair<Record, int32_t> search(Field field, std::vector<Field> recordFields);
};
#endif // !HASHFILE_HPP
