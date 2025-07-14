#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "field.hpp"
#include "record.hpp"
#include <cstdint>
#include <cstdio>
#include <vector>

/**
 * Class responsible for abstracting a block; all disk read and write access 
 * is done through it.
 * 
 * @author Ivo Machado
 */
class DiskBlock {
public:
    DiskBlock(std::vector<Field>& recordFields);
    /**
     * Reads a block from the disk of a file previously positioned at the correct
     * address into a char buffer. Then, based on the number of records in the
     * block, it parses them into in-memory records.
     * 
     * @author Ivo Machado
     */
    void readFromFile(FILE* file);
    /**
     * Parses the in-memory records into the buffer and writes to the file.
     * 
     * @author Ivo Machado
     */
    void writeToFile(FILE* file);
    /**
     * Size of the block in bytes.
     * 
     * @author Ivo Machado
     */
    static const int SIZE = 4096;
    /** 
     * Available size considering the space occupied by the block header.
     * (Size - 2 integers)
     */
    static const int AVAILABLE_SIZE = 4088;
    /** Vector of records in the block. */
    std::vector<Record> m_records;
    /** Size of a single record in bytes. */
    short m_recordSize{ 0 };
    /**
     * Char buffer where the disk block is read into and from which it's written
     * to disk.
     * 
     * @author Ivo Machado
     */
    char m_buffer[DiskBlock::SIZE];
    /**
     * The schema for the records in this block.
     * 
     * @author Ivo Machado
     */
    std::vector<Field> m_recordFields;
    /**
     * The block header.
     * 
     * @author Ivo Machado
     */
    Record m_header;
    /**
     * Current position in the buffer for the next write/read operation.
     * 
     * @author Ivo Machado
     */
    short m_bufferPos{ 0 };
    /**
     * Writes the block header and all its records to the buffer.
     * 
     * @author Ivo Machado
     */
    void writeToBuffer();
    /**
     * Reads the block header and all its records from the buffer.
     * 
     * @author Ivo Machado
     */
    void readFromBuffer();
    /**
     * Tries to insert a new record into the block if it fits.
     * 
     * @author Ivo Machado
     */
    bool insert(const Record& record);
    /**
     * Indicates if one more record can fit in the block.
     * 
     * @author Ivo Machado
     */
    bool fitOneMoreRecord();
};

#endif // !BLOCK_HPP