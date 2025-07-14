#ifndef INDEXFILE_HPP
#define INDEXFILE_HPP

#include "field.hpp"
#include "block.hpp"
#include "record.hpp"
#include <cstdint>
#include <cstdio>
#include <string>
#include <utility>


/**
 * Class responsible for managing a dense index file, whether primary
 * or secondary. This is where the B-Tree is actually implemented.
 * 
 * @author Juliana Castro
 */
class IndexFile{
    public:
    /** File pointer */
    FILE *m_file;
    /** Number of allocated nodes in the tree */
    int32_t m_locatedBlocks{0};
    /** Pointer to the root of the tree */
    int32_t m_root{-1};
    /**
     * Opens a file with the specified mode.
     * 
     * @author Juliana Castro
     */
    IndexFile(std::string filename, std::string mode);
    /**
     * Saves the header to disk upon destruction.
     * 
     * @author Juliana Castro
     */
    ~IndexFile();
    /**
     * Creates a new index file.
     * 
     * @author Juliana Castro
     */
    static IndexFile Create(std::string filename);
    /**
     * Opens an existing index file.
     * 
     * @author Juliana Castro
     */
    static IndexFile Open(std::string filename);
    /**
     * Inserts a new key given by `field` into the index, with `dataBlockIndex` as
     * the data pointer.
     * 
     * @author Juliana Castro
     */
    void insert(Field field, int32_t dataBlockIndex);
    /**
     * Writes the header to disk.
     * 
     * @author Juliana Castro
     */
    void writeHeaderToDisk();
    /**
     * Reads the file header into memory.
     * 
     * @author Juliana Castro
     */
    void readHeaderFromDisk();
    /**
     * Searches the index. Returns the data pointer if the specified field is found,
     * or -1 if not found. The second element of the pair is the number of blocks
     * read from disk to find the result.
     * 
     * @author Juliana Castro
     */
    std::pair<int32_t, int32_t> search(Field field);
    /** Maximum number of keys in a tree node; it's always even. */
    size_t m_fanOut{0};

    /**
     * Finds the index pointer that should be followed to search for/insert a field.
     * 
     * @author Juliana Castro
     */
    int findLocation(Field field, DiskBlock block);
    /**
     * Returns true if a block is a leaf node.
     * 
     * @author Juliana Castro
     */
    bool isLeaf(DiskBlock block);
    /**
     * Splits the block passed as a parameter into two new blocks.
     * 
     * @author Juliana Castro
     */
    Record split(DiskBlock& block);

    /**
     * Inserts the field and its data pointer into the appropriate leaf and moves up
     * the tree, performing necessary splits.
     * 
     * @author Juliana Castro
     */
    Record insertNonFull(DiskBlock& block, int32_t blockOffset, Field field, int32_t dataBlockIndex);
};
#endif