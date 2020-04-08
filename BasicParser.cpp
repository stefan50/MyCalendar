#include "BasicParser.hpp"
#include <fstream>

void BasicParser::open(const char* file_name) {
    file.open(file_name, std::ios::out);
}