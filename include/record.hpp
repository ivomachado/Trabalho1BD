#ifndef RECORD_HPP
#define RECORD_HPP

#include "field.hpp"
#include <vector>

class Record {
    
public:
    std::vector<Field> m_data;
    short writeToBuffer(char* buffer, short begin);
    short readFromBuffer(char* buffer, short begin);

    Record(const std::vector<Field>& data);
    Record();
};

#endif // !RECORD_HPP
