#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

std::string hashFunction(const std::string& input);

bool readFile(const std::string& filename, std::string& content);

#endif