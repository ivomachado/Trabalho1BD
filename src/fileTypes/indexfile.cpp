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

    if(field < block.m_records.front().m_data[0].asString) return -1;
    if(field > block.m_records.back().m_data[0].asString) return block.m_records.size()-1;
    
    for(int i = 0; i < block.m_records.size()-1){
        if(field > block.m_records[i].m_data[0].asString && field < block.m_records[i+1].m_data.m_string){
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

void split(DiskBlock &parent, DiskBlock &child, int32_t parentOffset, int32_t childOffset){
    //create a right child block
    std::vector<Field> blockFields{Field::asString(300), Field::asInteger(), Field::asInteger};
    DiskBlock newChild(blockFields);

    int half = child.m_records.size()/2;

    //copy the second half of the child to the new child
    newChild.m_records(child.m_records.begin()+(half+1), child.m_records.end());

    //insert in the parent the element that is the middle of the child
    std::vector<Field> recordFields{Field::asString(child.m_records[middle].m_data[0].asString),
            Field::asInteger(child.m_records[middle].m_data[1].asInteger), 
            Field::asInteger(Utils::calcBlockOffset(m_locatedBlocks))};
    Record record(recordFields);
    parent.m_records.insert(record);

    //erase the second half of the child
    child.m_records.erase(child.begin()+half, child.m_records.end());


    //write to file all the blocks
    fseek(m_file, parentOffset, SEEK_SET);
    parent.writeToFile(m_file);

    fseek(m_file, childOffset, SEEK_SET);
    child.writeToFile(m_file);

    fseek(m_file, Utils::calcBlockOffset(m_locatedBlocks), SEEK_SET);
    parent.writeToFile(m_file);
    
    //update and write the header
    m_locatedBlocks++;   
    writeHeaderToDisk();     
}

void insertNonFull(DiskBlock &block, int32_t blockOffset, Field field, int32_t blockIndex){

    std::vector<Field> blockFields{Field::asString(300), Field::asInteger(), Field::asInteger};

    //if leaf insert and write to file
    if(isLeaf(block)){
        std::vector<Field> recordFields{Field::asString(field), Field::asInteger(blockIndex), Field::asInteger(-1)};
        Record record(recordFields);
        
        block.insert(record);
        fseek(m_file, blockOffset, SEEK_SET);
        block.writeToFile(m_file);
    }
    else{
        //find position
        int index = findLocation(field, block);

        //read the child
        fseek(m_file, block.m_records[index].m_data[1].asInteger);
        DiskBlock child(blockFields);
        child.readFromFile(m_file);
       
        //child is full
        if(rootBlock.m_header.m_data[0].m_integer * m_recordSize == rootBlock.AVAILABLE_SIZE){

            split(block, child, blockOffset, block.m_records[index].m_data[1].asInteger);
        }
       
        insertNonFull(child,block.m_records[index].m_data[1].asInteger, field, blockIndex);
              
    }
}


void IndexFile::insert(Field field, int32_t blockIndex){
    
    readHeaderFromDisk();

    std::vector<Field> blockFields{Field::asString(300), Field::asInteger(), Field::asInteger};
    std::vector<Field> recordFields{Field::asString(field), Field::asInteger(blockIndex), Field::asInteger(-1)};
    Record record(recordFields);

    //tree has no element
    if(m_locatedBlocks == 0){
        //create a new block as root
        DiskBlock rootBlock(blockFields);

        rootBlock.insert(record);

        m_root = Utils::calcBlockOffset(0);
        m_locatedBlocks++;

        writeHeaderToDisk();
        fseek(m_file, m_root, SEEK_SET);
        rootBlock.writeToFile(m_file);
    }
    else{
        //read root from disk
        DiskBlock rootBlock(blockFields);
        fseek(m_file, m_root, SEEK_SET);
        rootBlock.readFromFile(m_file);

        //root is full
        if(rootBlock.m_header.m_data[0].m_integer * m_recordSize == rootBlock.AVAILABLE_SIZE){

            //create a new block
            DiskBlock newBlock(blockFields);

            //overflow pointer of the new block point the root
            newBlock.m_header.m_data[1].m_integer = m_root;

            //new block became the root
            m_root = Utils::calcBlockOffset(m_locatedBlocks);
            m_locatedBlocks++;

            //split the old root
            split(newBlock, rootBlock, m_root, newBlock.m_header.m_data[1].m_integer);
            insertNonFull(newBlock, m_root, field, blockIndex);
        }
        else {
            insertNonFull(rootBlock, m_root, field, blockIndex);
        }           
        
        
    }

}



