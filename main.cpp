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

int main(int argc, char* argv[]) {

    int mode;
    string filename;
    string content;

    if (argc > 1) {
        filename = argv[1];

        if (!readFile(filename, content)) {
            return 1;
        }

        cout << "Naudojamas rezimas: failo nuskaitymas" << endl;

        string hash = hashFunction(content);
        cout << "Hash: " << hash << endl;

        return 0;
    }

    cout << "Pasirinkite rezima: " << endl;
    cout << "1 - Ivesti teksta ranka" << endl;
    cout << "2 - Nuskaityti teksta is pasirinkto failo" << endl;
    cout << "Pasirinkimas: ";

    cin >> mode;

    switch (mode) {

        case 1:
            cout << "Naudojamas rezimas: teksto ivestis ranka" << endl;
            cout << "Iveskite teksta: ";
            cin.ignore();
            getline(cin, content);

        break;

        case 2:
            cout << "Naudojamas rezimas: failo nuskaitymas" << endl;
            cout << "Turimi .txt failai: " << endl;
            system("ls *.txt");

            cout << "Iveskite failo pavadinima: ";
             cin >> filename;

            if (!readFile(filename, content)) {
                 return 1;
            }

        break;

        default:
            cout << "Neteisingas pasirinkimas!" << endl;
            return 1;
    }

    string hash = hashFunction(content);
    cout << "Hash: " << hash << endl;
    
    return 0;
}