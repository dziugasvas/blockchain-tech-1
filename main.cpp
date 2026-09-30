#include "hash.h"
#include "tests.h"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::ifstream;
using std::endl;
using std::cin;

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
    cout << "3 - Atlikti testavimus" << endl;
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

        case 3:
            cout << "Naudojamas rezimas: testavimas" << endl;
            testInputs();
            return 0;

        default:
            cout << "Neteisingas pasirinkimas!" << endl;
            return 1;
    }

    string hash = hashFunction(content);
    cout << "Hash: " << hash << endl;
    
    return 0;
}