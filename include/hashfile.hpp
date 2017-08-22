#ifndef HASHFILE_HPP
#define HASHFILE_HPP

#include "record.hpp"
#include "utils.hpp"
#include "block.hpp"
#include "cstdint"
#include "cstdio"
#include "vector"

class HashFile {
public:
    void insert(Record rec);
    FILE* m_file{nullptr};
    HashFile();
    ~HashFile();
    HashFile(std::string filename, std::string mode);
    static HashFile Create(std::string filename);
    static HashFile Open(std::string filename);
    Utils::BitMap m_blocksMap;

    void writeHeaderToDisk();
    void readHeaderFromDisk();

    int32_t m_overflowBlocks{ 0 };
};

#endif // !HASHFILE_HPP
