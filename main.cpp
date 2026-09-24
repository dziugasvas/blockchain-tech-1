#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>

using std::string;
using std::cout;
using std::ifstream;
using std::endl;
using std::cin;

bool readFile (const string& filename, string& content) {

    ifstream file(filename);

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

void hashFunction(const string& input) {
    uint32_t state[8];

    for (int i = 0; i < 8; i++) {
        state[i] = 0;
    }
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

    hashFunction(content);
    
    return 0;
}