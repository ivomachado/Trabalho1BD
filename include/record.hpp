#ifndef RECORD_HPP
#define RECORD_HPP

#include "field.hpp"
#include <vector>

/**
 * Abstraction class for a record and its fields. It writes and reads its
 * information to/from a byte buffer.
 * 
 * @author Ivo Machado
 */
class Record {
public:
    /** Vector of Fields for the record */
    std::vector<Field> m_data;
    /**
     * Writes the Record's data to the buffer.
     * 
     * @author Ivo Machado
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * Reads data from the buffer into the Record.
     * 
     * @author Ivo Machado
     */
    short readFromBuffer(char* buffer, short begin);
    /**
     * Creates a new Record with the data from the vector of fields received
     * as a parameter.
     * 
     * @author Ivo Machado
     */
    Record(const std::vector<Field>& data);
    /**
     * Default constructor.
     * 
     * @author Ivo Machado
     */
    Record();
};

#endif // !RECORD_HPP