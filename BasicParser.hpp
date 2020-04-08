#ifndef BASIC_PARSER_HPP
#define BASIC_PARSER_HPP
#include <fstream>

class BasicParser {
protected:
    std::fstream file;
public:
    virtual void open(const char* file_name); 
};

#endif