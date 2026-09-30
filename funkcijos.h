#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>

std::string hashFunction(const std::string& input);
bool readFile(const std::string& filename, std::string& content);
bool readLines(const std::string& filename, std::vector<std::string>& lines);

#endif