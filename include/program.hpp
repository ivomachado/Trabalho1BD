#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <cstdint>
#include <string>

/**
 * Class that centralizes the functions for the assignment's requirements.
 * 
 * @author Juliana Castro
 */
class Program {
public:
    /**
     * Opens the given file and generates a data file, and two index files 
     * (primary and secondary) from its contents.
     * 
     * @author Juliana Castro
     */
    static void upload(std::string filename = "teste.csv");
    /**
     * Searches for the ID in the data file using hashing.
     * 
     * @author Juliana Castro
     */
    static void findrec(int32_t id);
    /**
     * Searches for the ID in the primary index file.
     * 
     * @author Juliana Castro
     */
    static void seek1(int32_t id);
    /**
     * Searches for the title in the secondary index file.
     * 
     * @author Juliana Castro
     */
    static void seek2(std::string title);
    /**
     * Prints a help message.
     * 
     * @author Juliana Castro
     */
    static void help();
};

#endif // !PROGRAM_HPP