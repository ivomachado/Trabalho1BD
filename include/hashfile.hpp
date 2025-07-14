#ifndef HASHFILE_HPP
#define HASHFILE_HPP
#include "block.hpp"
#include "cstdint"
#include "cstdio"
#include "field.hpp"
#include "record.hpp"
#include "utils.hpp"
#include "vector"
#include <utility>
#include <string>

/**
 * Class responsible for managing the data file using hashing.
 * 
 * @author Ivo Machado
 */
class HashFile {
public:
    /**
     * Inserts the given Record into its proper position in the hash table
     * or in overflow blocks and returns the index of the block where the
     * insertion was made.
     * 
     * @author Ivo Machado
     */
    int32_t insert(Record rec);
    /** File pointer */
    FILE* m_file{ nullptr };
    /**
     * Writes the file header to disk and closes the file.
     * 
     * @author Ivo Machado
     */
    ~HashFile();
    /**
     * Opens the file `filename` with the mode passed as a parameter.
     * 
     * @author Ivo Machado
     */
    HashFile(std::string filename, std::string mode);
    /**
     * Creates a new file with the given name.
     * 
     * @author Ivo Machado
     */
    static HashFile Create(std::string filename);
    /**
     * Opens an existing file with the given name.
     * 
     * @author Ivo Machado
     */
    static HashFile Open(std::string filename);
    /**
     * Number of blocks used for the file header.
     * 
     * @author Ivo Machado
     */
    static const int NUMBER_BLOCKS_HEADER = 46;
    /** Total number of blocks allocated for hashing. */
    static const int32_t NUMBER_BLOCKS{ (DiskBlock::AVAILABLE_SIZE * NUMBER_BLOCKS_HEADER - 4) * 8 };
    /** The index of the record field to be used for hashing, defaults to 0. */
    int m_fieldHashIndex{ 0 };

    /** In-memory bitmap of occupied blocks. */
    Utils::BitMap m_blocksMap;
    /**
     * Writes the file header to disk.
     * 
     * @author Ivo Machado
     */
    void writeHeaderToDisk();
    /**
     * Reads the file header into memory.
     * 
     * @author Ivo Machado
     */
    void readHeaderFromDisk();
    /** Number of overflow blocks in memory. */
    int32_t m_overflowBlocks{ 0 };
    /**
     * Searches for the field in the file. `recordFields` is the schema of the records stored in it.
     * 
     * @author Ivo Machado
     */
    std::pair<Record, int32_t> search(Field field, std::vector<Field> recordFields);
    /**
     * Compares all records in the block at `blockIndex` with the given `field`,
     * using `fieldIndex` to select the field within each record.
     * 
     * @author Ivo Machado
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields, int fieldIndex);
    /**
     * Gets a record from a block that has the hash field equal to the given `field`.
     * 
     * @author Ivo Machado
     */
    Record getFromBlock(int32_t blockIndex, Field field, std::vector<Field> recordFields);
};
#endif // !HASHFILE_HPP