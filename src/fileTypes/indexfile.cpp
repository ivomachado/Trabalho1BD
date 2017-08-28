#include "indexfile.hpp"
#include "block.hpp"
#include "utils.hpp"
#include <vector>
#include <algorithm>


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

int findLocation(Field field, DiskBlock block){

    if(field < block.m_records[0].m_string) return -1;
    
    for(int i = 0; i < block.m_records.size()-1){
        if(field > block.m_records[i].m_string && field < block.m_records[i+1].m_string){
            return i;
        }
    }
}

bool isLeaf(DiskBlock block){
    for(int i = 0; i < block.m_records.size()){
        if(block.m_records[i].m_data[2].m_integer != -1){
            return false;
        }
    }

    return true;
}

void compare(Record r1, Record r2){
    if (r1.m_data[0].m_string == r2.m_data[0].m_string) return false;
    return (r1.m_data[0].m_string > r2.m_data[0].m_string);
}

void split(int32_t parent, int index, int32_t child){
    
}

void insertNonFull(int32_t blockOffset, Field fiel, int32_t blockIndex){
    std::vector<Field> blockFields{Field::asString(300), Field::asInteger(), Field::asInteger};
    DiskBlock block(blockFields);

    fseek(m_file, blockOffset, SEEK_SET);
    block.readFromFile(m_file);

    if(isLeaf(block)){
        std::vector<Field> recordFields{Field::asString(field), Field::asInteger(blockIndex), Field::asInteger(-1)};
        Record record(recordFields);
        
        block.insert(record);
        fseek(m_file, blockOffset, SEEK_SET);
        block.writeToFile(m_file);
    }
    else{
        int index = findLocation(field, block);

        if(index != -1){
            
        }
       
    }
}


void IndexFile::insert(Field field, int32_t blockIndex){
    
    readHeaderFromDisk();

    std::vector<Field> blockFields{Field::asString(300), Field::asInteger(), Field::asInteger};
    std::vector<Field> recordFields{Field::asString(field), Field::asInteger(blockIndex), Field::asInteger(-1)};
    Record record(recordFields);

    //tree has no element
    if(m_locatedBlocks == 0){
        DiskBlock rootBlock(blockFields);

        rootBlock.insert(record);

        m_root = Utils::calcBlockOffset(0);
        m_locatedBlocks++;

        writeHeaderToDisk();
        fseek(m_file, m_root, SEEK_SET);
        rootBlock.writeToFile(m_file);
    }
    else{
        DiskBlock rootBlock(blockFields);
        fseek(m_file, m_root, SEEK_SET);
        rootBlock.readFromFile(m_file);

        if(rootBlock.m_header.m_data[0].m_integer * m_recordSize == rootBlock.AVAILABLE_SIZE){
            DiskBlock newBlock(blockFields);
            newBlock.m_header.m_data[1].m_integer = m_root;

            m_root = Utils::calcBlockOffset(m_locatedBlocks);
            m_locatedBlocks++;

            split(newBlock, -1, rootBlock);
            insertNonFull(newBlock, field, blockIndex);
            
            writeHeaderToDisk();

            fseek(m_file, Utils::calcBlockOffset(0), SEEK_SET);
            block.writeToFile(m_file);
        }
        else {
            insertNonFull(m_root, field, blockIndex);
        }           
        
        
    }

}



