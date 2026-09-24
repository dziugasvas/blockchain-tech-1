#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::ifstream;
using std::endl;
using std::cin;

bool readFile (const string& filename) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Nepavyko atidaryti failo." << endl;
        return false;
    }

    char c;

    while (file.get(c)) {
        cout << c;
    }

    file.close();

    return true;

}


int main() {

    string filename;

    cout << "Turimi .txt failai: " << endl;
    system("ls *.txt");

    cout << "Iveskite failo pavadinima: ";
    cin >> filename;

    if (!readFile(filename)) {
        return 1;
    }
    

    return 0;
}