#include "indexfile.hpp"
#include <vector>


IndexFile::IndexFile(std::string filename, std::string mode){
    m_file = fopen(filename.c_str(), mode.c_str());
}

IndexFile::~IndexFile(){
    if(m_file != nullptr){
        fclose(m_file);
    }
}

IndexFile::Create(std::string filename){
    Index indexfile(filename, std::string("wb+"));
    return indexfile;
}

IndexFile::Open(std::string filename){
    Index indexfile(filename, std::string("rb+"));
    indexfile.readHeaderFromDisk();
    return indexfile;
}

IndexFile::writeHeaderToDisk(){
    std::vector<Field> firstBlockFields{Field::asInteger(m_locatedBlocks), Field::asInteger(m_root)};
    DiskBlock firstBlock(firstBlockFields);
    Record header(firstBlockFields);
    firstBlock.insert(header);
    fseek(m_file, 0, SEEK_SET);
    firstBlock.WriteToFile(m_file);
}

IndexFile::readHeaderFromDisk(){
    std::vector<Field> firstBlockFields{Field::asInteger(), Field::asInteger()};
    DiskBlock firstBlock(firstBlockFields);
    firstBlock.readFromFile(m_file);
    m_locatedBlocks = firstBlock.m_records[0].m_data[0],m_integer;
    m_root = firstBlock.m_records[0].m_data[1].m_integer;
       
}



