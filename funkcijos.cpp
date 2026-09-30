#include "funkcijos.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdint>

using std::string;
using std::hex;
using std::setw;
using std::setfill;
using std::ifstream;
using std::cout;
using std::endl;

string hashFunction(const string& input) {
    uint32_t state[8];

    for (int i = 0; i < 8; i++) {
        state[i] = 0;
    }

    for (unsigned char byte : input) {
        for (int i = 0; i < 8; i++) {
            state[i] = state[i] * 7 + byte + i;
        }
    }

    std::stringstream result;

    for (int i = 0; i < 8; i++) {
        result << hex << setw(8) << setfill('0') << state[i];
    }

    return result.str();
}

bool readFile (const string& filename, string& content) {

    content.clear();

    ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        cout << "Nepavyko atidaryti failo." << endl;
        return false;
    }

    char c;

    while (file.get(c)) {
        content += c;
    }

    file.close();

    return true;

}