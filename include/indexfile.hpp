#ifndef INDEXFILE_HPP
#define INDEXFILE_HPP

#include "field.hpp"
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
};
#endif
