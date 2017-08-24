#include "indexfile.hpp"
#include "block.hpp"
#include <vector>


IndexFile::IndexFile(std::string filename, std::string mode){
    m_file = fopen(filename.c_str(), mode.c_str());
}

IndexFile::~IndexFile(){
    if(m_file != nullptr){
        fclose(m_file);
    }
}

IndexFile IndexFile::Create(std::string filename){
    IndexFile indexfile(filename, std::string("wb+"));
    return indexfile;
}

IndexFile IndexFile::Open(std::string filename){
    IndexFile indexfile(filename, std::string("rb+"));
    indexfile.readHeaderFromDisk();
    return indexfile;
}

void IndexFile::writeHeaderToDisk(){
    std::vector<Field> firstBlockFields{Field::asInteger(m_locatedBlocks), Field::asInteger(m_root)};
    DiskBlock firstBlock(firstBlockFields);
    Record header(firstBlockFields);
    firstBlock.insert(header);
    fseek(m_file, 0, SEEK_SET);
    firstBlock.writeToFile(m_file);
}

void IndexFile::readHeaderFromDisk(){
    std::vector<Field> firstBlockFields{Field::asInteger(), Field::asInteger()};
    DiskBlock firstBlock(firstBlockFields);
    firstBlock.readFromFile(m_file);
    m_locatedBlocks = firstBlock.m_records[0].m_data[0].m_integer;
    m_root = firstBlock.m_records[0].m_data[1].m_integer;
       
}



