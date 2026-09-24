#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <sstream>
#include <iomanip>

using std::string;
using std::cout;
using std::ifstream;
using std::endl;
using std::cin;
using std::stringstream;
using std::hex;
using std::setw;
using std::setfill;

bool readFile (const string& filename, string& content) {

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

int main() {

    string filename;
    string content;

    cout << "Turimi .txt failai: " << endl;
    system("ls *.txt");

    cout << "Iveskite failo pavadinima: ";
    cin >> filename;

    if (!readFile(filename, content)) {
        return 1;
    }

    cout << "Nuskaitytas turinys:" << endl;
    cout << content << endl;

    string hash = hashFunction(content);
    cout << "Hash: " << hash << endl;
    
    return 0;
}