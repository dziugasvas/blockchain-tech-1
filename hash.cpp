#include "hash.h"
#include <cstdint>
#include <sstream>
#include <iomanip>

using std::string;
using std::hex;
using std::setw;
using std::setfill;

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