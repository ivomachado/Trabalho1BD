#ifndef INDEXFILE_HPP
#define INDEXFILE_HPP

#include "field.hpp"
#include "block.hpp"
#include <cstdint>
#include <cstdio>

class IndexFile{
    public:
    FILE *m_file;
    int32_t m_locatedBlocks{0};
    int32_t m_root{0};
    IndexFile(std::string filename, std::string mode);
    ~IndexFile();
    static IndexFile Create(std::string filename);
    static IndexFile Open(std::string filename);
    void insert(Field field, int32_t blockIndex);
    void writeHeaderToDisk();
    void readHeaderFromDisk();
    //void search(Field field);


    int findLocation(Field field, DiskBlock block);
    bool isLeaf(DiskBlock block);
    bool compare(Record r1, Record r2);
    void split(DiskBlock &parent, DiskBlock &child, int32_t parentOffset, int32_t childOffset);
    void insertNonFull(DiskBlock &block, int32_t blockOffset, Field field, int32_t blockIndex);
};
#endif
