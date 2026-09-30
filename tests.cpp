#include "tests.h"
#include "hash.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::string;

void testInputs() {

    string inputs[] = {
        "",
        "a",
        "b"
    };

    for (const string& input : inputs) {
        string hash = hashFunction(input);

        cout << "Ivestis: \"" << input << "\"" << endl;
        cout << "Hash: " << hash << endl;
        cout << endl;
    }

    srand(time(0));

    string characters =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";

    string longInput;

    for (int i = 0; i < 1200; i++) {
        int randomIndex = rand() % characters.length();
        longInput += characters[randomIndex];
    }

    string longHash = hashFunction(longInput);

    cout << "Atsitiktine ASCII ivestis" << endl;
    cout << "Ivesties ilgis: " << longInput.length() << endl;
    cout << "Hash: " << longHash << endl;
    cout << endl;

    string originalas = "ciatestas";

    string pakeistaPradz = "xiatestas";
    string pakeistasVidur = "ciatxstas";
    string pakeistaPabaig = "ciatestax";

    cout << "Vieno simbolio pakeitimai: " << endl;

    cout << "Originalas: " << originalas << endl;
    cout << "Hash: " << hashFunction(originalas) << endl;

    cout << "Pakeista pradzia: " << pakeistaPradz << endl;
    cout << "Hash: " << hashFunction(pakeistaPradz) << endl;

    cout << "Pakeistas vidurys: " << pakeistasVidur << endl;
    cout << "Hash: " << hashFunction(pakeistasVidur) << endl;

    cout << "Pakeista pabaiga: " << pakeistaPabaig << endl;
    cout << "Hash: " << hashFunction(pakeistaPabaig) << endl;

    cout << endl;

    string structuredInput = "abcabcabcabcabcabcabcabc";

    cout << "Strukturuota ivestis:" << endl;
    cout << "Ivestis: " << structuredInput << endl;
    cout << "Hash: " << hashFunction(structuredInput) << endl;
    cout << endl;

    cout << "Strukturuotos ivestys:" << endl;

    cout << "Pasikartojantys simboliai:" << endl;
    cout << hashFunction("abcabcabcabc") << endl;

    cout << "Pakeista simboliu tvarka:" << endl;
    cout << hashFunction("abcdef") << endl;
    cout << hashFunction("fedcba") << endl;

    cout << "Tarpas pradzioje:" << endl;
    cout << hashFunction(" tekstas") << endl;

    cout << "Tarpas pabaigoje:" << endl;
    cout << hashFunction("tekstas ") << endl;

    cout << "Be naujos eilutes: " << endl;
    cout << hashFunction("tekstas") << endl;

    cout << "Su naujos eilutes simboliu: " << endl;
    cout << hashFunction("tekstas\n") << endl;

    cout << endl;

    cout << "UTF-8 ivestis:" << endl;

    string utf8Input = "ąčęėįšųūž";

    cout << "Ivestis: " << utf8Input << endl;
    cout << "Hash: " << hashFunction(utf8Input) << endl;

    cout << endl;
}