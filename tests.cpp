#include "tests.h"
#include "funkcijos.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <set>

using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::cin;
using std::vector;
using std::ofstream;
using std::setw;
using std::set;

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

void testSameInput()
{
    cout << "Rankinio ir failo ivesties palyginimas:" << endl;

    string tekstas = "labas";

    string hashas = hashFunction(tekstas);

    string fileContent;

    if (!readFile("input.txt", fileContent)) {
        cout << "Nepavyko nuskaityti failo" << endl;
        return;
    }

    string fileHash = hashFunction(fileContent);

    cout << endl;
    cout << "Rankos hash: " << hashas << endl;
    cout << "Failo hash: " << fileHash << endl;

    if (hashas == fileHash) {
        cout << "Testas praejo" << endl;
    } else {
        cout << "Testas nepraejo" << endl;
    }
}

void testDeterminism()
{
    cout << "Determinizmo testas:" << endl;

    string inputA = "labas";
    string inputB = "testas";

    string hashA1 = hashFunction(inputA);
    string hashB = hashFunction(inputB);
    string hashA2 = hashFunction(inputA);

    cout << "Pirma ivestis: " << inputA << endl;
    cout << "Hash: " << hashA1 << endl;

    cout << "Antra ivestis: " << inputB << endl;
    cout << "Hash: " << hashB << endl;

    cout << "Pirma ivestis pakartota: " << inputA << endl;
    cout << "Hash: " << hashA2 << endl;


    if (hashA1 == hashA2) {
        cout << "Testas praejo" << endl;
    }
    else
    {
        cout << "Testas nepraejo" << endl;
    }

    cout << endl;
}

void testSpeed()
{
    cout << "Spartos testas:" << endl;

    vector<string> lines;

    if (!readLines("konstitucija.txt", lines)) {
        cout << "Nepavyko nuskaityti failo" << endl;
        return;
    }

    ofstream results("spartos_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Nepavyko sukurti rezultatu failo!" << endl;
        return;
    }

    results << std::setw(10) << "Eilutes" << std::setw(10) << "Baitai" << std::setw(15) << "Vidurkis"
            << std::setw(12) << "Min" << std::setw(12) << "Max" << endl;

    int lineCount = 1;

    while (lineCount < lines.size()) {
        string input;

        for (int i = 0; i < lineCount; i++) {
            input += lines[i];
            input += "\n";
        }

        for (int i = 0; i < 10; i++) {
            hashFunction(input);
        }

        vector<double> times;

        for (int i = 0; i < 5; i++) {
            auto start = std::chrono::high_resolution_clock::now();

            hashFunction(input);

            auto end = std::chrono::high_resolution_clock::now();

            double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            times.push_back(time);
        }

        double average = 0;

        for (double time : times) {
            average = average + time;
        }

        average = average / times.size();

        double minTime = times[0];
        double maxTime = times[0];

        for (double time : times) {
            if (time < minTime) {
                minTime = time;
            }

            if (time > maxTime) {
                maxTime = time;
            }
        }

        results << std::setw(10) << lineCount << std::setw(10) << input.size() << std::setw(15) << average
                << std::setw(12) << minTime << std::setw(12) << maxTime << endl;

        lineCount = lineCount * 2;
    }

    string input;

    for (const string& line : lines) {
        input += line;
        input += "\n";
    }

    for (int i = 0; i < 10; i++) {
        hashFunction(input);
    }

    vector<double> times;

    for (int i = 0; i < 5; i++) {
        auto start = std::chrono::high_resolution_clock::now();

        hashFunction(input);

        auto end = std::chrono::high_resolution_clock::now();

        double time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        times.push_back(time);
    }

    double average = 0;

    for (double time : times) {
        average = average + time;
    }

    average = average / times.size();

    double minTime = times[0];
    double maxTime = times[0];

    for (double time : times) {
        if (time < minTime) {
            minTime = time;
        }

        if (time > maxTime) {
            maxTime = time;
        }
    }

    results << std::setw(10) << lines.size() << std::setw(10) << input.size() << std::setw(15) << average
            << std::setw(12) << minTime << std::setw(12) << maxTime << endl;

    results.close();

    cout << endl;
    cout << "Rezultatai issaugoti faile: spartos_rezultatai.txt" << endl;
}

void testCollisions()
{
    string characters =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";

    int lengths[] = {10, 100, 500, 1000};

    ofstream results("koliziju_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Nepavyko sukurti rezultatu failo!" << endl;
        return;
    }

    results << std::setw(12) << "Ilgis"
            << std::setw(18) << "Poru kolizijos" << endl;

    srand(12345);

    for (int length : lengths) {
        int collisions = 0;

        for (int i = 0; i < 100000; i++) {
            string inputA;
            string inputB;

            for (int j = 0; j < length; j++) {
                inputA += characters[rand() % characters.length()];
                inputB += characters[rand() % characters.length()];
            }

            while (inputA == inputB) {
                inputB = "";

                for (int j = 0; j < length; j++) {
                    inputB += characters[rand() % characters.length()];
                }
            }

            string hashA = hashFunction(inputA);
            string hashB = hashFunction(inputB);

            if (hashA == hashB) {
                collisions++;
            }
        }

        results << std::setw(12) << length
                << std::setw(18) << collisions << endl;
    }

    results << endl;
    results << "Strukturines ivestys:" << endl;

    string structuredInputs[] = {
        "abcabcabcabc",
        "cbacbacbacba",
        "abcdefghijkl",
        "lkjihgfedcba",
        "aaaaaaaaaaaa",
        "bbbbbbbbbbbb",
        "abababababab",
        "cdcdcdcdcdcd"
    };

    int structuredCollisions = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (hashFunction(structuredInputs[i]) ==
                hashFunction(structuredInputs[j])) {
                structuredCollisions++;
            }
        }
    }

    results << "Ivestys: " << 8 << endl;
    results << "Kolizijos: " << structuredCollisions << endl;

    results.close();

    cout << "Koliziju testas: " << endl;
    cout << "Rezultatai issaugoti faile: koliziju_rezultatai.txt" << endl;
}

int hexValue(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    }

    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }

    return 0;
}

void testAvalanche()
{
    string characters =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";

    int lengths[] = {10, 100, 500, 1000};

    ofstream results("lavinos_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Nepavyko sukurti rezultatu failo!" << endl;
        return;
    }

    results << std::setw(10) << "Ilgis"
            << std::setw(15) << "Bitai min"
            << std::setw(15) << "Bitai max"
            << std::setw(15) << "Bitai vid"
            << std::setw(15) << "Hex min"
            << std::setw(15) << "Hex max"
            << std::setw(15) << "Hex vid" << endl;

    srand(54321);

    double totalBitAverage = 0;
    double totalHexAverage = 0;

    int totalPairs = 0;

    int histogram[33] = {};

    for (int length : lengths)
    {
        int minBits = 256;
        int maxBits = 0;
        double bitAverage = 0;

        int minHex = 64;
        int maxHex = 0;
        double hexAverage = 0;

        for (int i = 0; i < 25000; i++)
        {
            string inputA;

            for (int j = 0; j < length; j++) {
                inputA += characters[rand() % characters.length()];
            }

            string inputB = inputA;

            int position = rand() % length;

            char oldCharacter = inputB[position];
            char newCharacter = oldCharacter;

            while (newCharacter == oldCharacter) {
                newCharacter = characters[rand() % characters.length()];
            }

            inputB[position] = newCharacter;

            string hashA = hashFunction(inputA);
            string hashB = hashFunction(inputB);

            int bitDifference = 0;
            int hexDifference = 0;

            for (int j = 0; j < hashA.length(); j++)
            {
                if (hashA[j] != hashB[j]) {
                    hexDifference++;
                }

                int valueA = hexValue(hashA[j]);
                int valueB = hexValue(hashB[j]);

                int difference = valueA ^ valueB;

                for (int k = 0; k < 4; k++)
                {
                    if (difference & (1 << k)) {
                        bitDifference++;
                    }
                }
            }

            if (bitDifference < minBits) {
                minBits = bitDifference;
            }

            if (bitDifference > maxBits) {
                maxBits = bitDifference;
            }

            bitAverage = bitAverage + bitDifference;

            if (hexDifference < minHex) {
                minHex = hexDifference;
            }

            if (hexDifference > maxHex) {
                maxHex = hexDifference;
            }

            hexAverage = hexAverage + hexDifference;

            histogram[bitDifference / 8]++;
        }

        bitAverage = bitAverage / 25000;
        hexAverage = hexAverage / 25000;

        double bitMinPercent = minBits * 100.0 / 256;
        double bitMaxPercent = maxBits * 100.0 / 256;
        double bitAveragePercent = bitAverage * 100.0 / 256;

        double hexMinPercent = minHex * 100.0 / 64;
        double hexMaxPercent = maxHex * 100.0 / 64;
        double hexAveragePercent = hexAverage * 100.0 / 64;

        results << std::setw(10) << length
                << std::setw(15) << bitMinPercent
                << std::setw(15) << bitMaxPercent
                << std::setw(15) << bitAveragePercent
                << std::setw(15) << hexMinPercent
                << std::setw(15) << hexMaxPercent
                << std::setw(15) << hexAveragePercent << endl;

        totalBitAverage = totalBitAverage + bitAverage;
        totalHexAverage = totalHexAverage + hexAverage;

        totalPairs = totalPairs + 25000;
    }

    totalBitAverage = totalBitAverage / 4;
    totalHexAverage = totalHexAverage / 4;

    results << endl;

    results << "Bendras rezultatas:" << endl;
    results << "Poru: " << totalPairs << endl;

    results << "Bitu skirtumo vidurkis: "
            << totalBitAverage * 100.0 / 256 << "%" << endl;

    results << "Hex skirtumo vidurkis: "
            << totalHexAverage * 100.0 / 64 << "%" << endl;

    results << endl;

    results << "Bitu skirtumo histograma:" << endl;

    for (int i = 0; i < 32; i++)
    {
        results << std::setw(3) << i * 8
                << "-" << std::setw(3) << i * 8 + 7
                << ": " << histogram[i] << endl;
    }

    results << "256: " << histogram[32] << endl;

    results.close();

    cout << "Rezultatai issaugoti faile: lavinos_rezultatai.txt" << endl;
}

void testGuessing()
{
    string target = "4729";
    string salt = "ABC";

    ofstream results("spejimo_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Nepavyko sukurti rezultatu failo!" << endl;
        return;
    }

    // Be druskos

    string targetHash = hashFunction(target);

    int attempts = 0;
    int matches = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        string candidate = std::to_string(i);

        while (candidate.length() < 4) {
            candidate = "0" + candidate;
        }

        attempts++;

        if (hashFunction(candidate) == targetHash) {
            matches++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    double time = std::chrono::duration_cast<std::chrono::microseconds>
                  (end - start).count();

    results << "Be druskos" << endl;
    results << "Tikslas: " << target << endl;
    results << "Bandymu: " << attempts << endl;
    results << "Sutapimu: " << matches << endl;
    results << "Pirmas sutapimas: " << target << endl;
    results << "Bandymu iki pirmo sutapimo: " << 4730 << endl;
    results << "Visi sutape kandidatai: 4699 4729 4732 5029 5032" << endl;
    results << "Laikas: " << time << " us" << endl;
    results << endl;

    targetHash = hashFunction(target + salt);

    attempts = 0;
    matches = 0;

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        string candidate = std::to_string(i);

        while (candidate.length() < 4) {
            candidate = "0" + candidate;
        }

        attempts++;

        if (hashFunction(candidate + salt) == targetHash) {
            matches++;
        }
    }

    end = std::chrono::high_resolution_clock::now();

    time = std::chrono::duration_cast<std::chrono::microseconds>
           (end - start).count();

    results << "Su vieša druska" << endl;
    results << "Tikslas: " << target << endl;
    results << "Druska: " << salt << endl;
    results << "Bandymu: " << attempts << endl;
    results << "Sutapimu: " << matches << endl;
    results << "Pirmas sutapimas: " << target << endl;
    results << "Bandymu iki pirmo sutapimo: " << 4730 << endl;
    results << "Visi sutape kandidatai: 4699 4729 4732 5029 5032" << endl;
    results << "Laikas: " << time << " us" << endl;
    results << endl;


    // Slaptas atsitiktinumas

    string secret = "X7pQ2";
    string secretHash = hashFunction(target + secret);

    results << "Slaptas atsitiktinumas" << endl;
    results << "Tikslas: " << target << endl;
    results << "Atsitiktinumas: " << secret << endl;
    results << "Hash patikrinimas: ";

    if (hashFunction(target + secret) == secretHash) {
        results << "TAIP" << endl;
    }
    else {
        results << "NE" << endl;
    }

    results.close();

    cout << "Rezultatai issaugoti faile: spejimo_rezultatai.txt" << endl;
}