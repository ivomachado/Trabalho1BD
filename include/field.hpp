#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <cstring>
#include <cstdint>
#include <iostream>
#include <string>

/**
 * Possible Field types.
 * 
 * @author Ivo Machado
 */
enum class DataTypes { Invalid,
    Integer,
    String,
    ByteArray };

/**
 * An abstraction class for atomic fields with their possible data types. 
 * It writes and reads its information to/from a byte buffer.
 * 
 * @author Ivo Machado
 */
class Field {
public:
    /** Maximum size of the string or byte array. */
    short m_maxSize;
    /** The type of the Field, defaults to Invalid. */
    DataTypes m_type{ DataTypes::Invalid };
    /** Constructs with the given type. */
    Field(DataTypes type);
    /** Default constructor. */
    Field() {}
    /** Stores the integer value. */
    int32_t m_integer;
    /** Stores the string and byte array value. */
    std::string m_string{""};
    /** 
     * Creates an Integer type Field without a defined value.
     * 
     * @author Ivo Machado
     */
    static Field asInteger();
    /** 
     * Creates an Integer type Field with a value defined by the parameter.
     * 
     * @author Ivo Machado
     */
    static Field asInteger(int32_t value);
    /** 
     * Creates a String type Field without a defined value and with a maximum size.
     * 
     * @author Ivo Machado
     */
    static Field asString(short maxSize);
    /** 
     * Creates a ByteArray type Field without a defined value and with a maximum size.
     * 
     * @author Ivo Machado
     */
    static Field asByteArray(short maxSize);
    /** 
     * Creates a String type Field with a value and maximum size defined by the parameters.
     * 
     * @author Ivo Machado
     */
    static Field asString(const char* data, short maxSize);
    /** 
     * Returns the position to which the Field instance belongs in a hash table of size 'size'.
     * 
     * @author Ivo Machado
     */
    int32_t hash(int32_t size);
    /** 
     * Returns the size in bytes that the field occupies on disk.
     * 
     * @author Ivo Machado
     */
    short size();
    /**
     * Writes the field's value to the buffer starting from the 'begin' position.
     * 
     * @author Ivo Machado
     */
    short writeToBuffer(char* buffer, short begin);
    /**
     * Reads the field's data from the buffer starting from the 'begin' position.
     * 
     * @author Ivo Machado
     */
    short readFromBuffer(char* buffer, short begin);
    /**
     * Equality operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator==(const Field& a, const Field& b);
    /**
     * Inequality operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator!=(const Field& a, const Field& b);
    /**
     * Greater than operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator>(const Field& a, const Field& b);
    /**
     * Less than operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator<(const Field& a, const Field& b);
    /**
     * Less than or equal to operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator<=(const Field& a, const Field& b);
    /**
     * Greater than or equal to operator.
     * 
     * @author Ivo Machado
     */
    friend bool operator>=(const Field& a, const Field& b);
    /**
     * Output stream operator for a Field.
     * 
     * @author Ivo Machado
     */
    friend std::ostream& operator<<(std::ostream& os, const Field& field);
};

#endif