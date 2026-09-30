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

void testInputs()
{
    cout << "Ivesties testai: ";

    int testai = 0;
    int sekmingi = 0;

    testai++;
    if (hashFunction("") != "") {
        sekmingi++;
    }

    testai++;
    if (hashFunction("a") != "") {
        sekmingi++;
    }

    testai++;
    if (hashFunction("a") != hashFunction("b")) {
        sekmingi++;
    }

    string characters =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";

    string longInput;

    for (int i = 0; i < 1200; i++) {
        int randomIndex = rand() % characters.length();
        longInput += characters[randomIndex];
    }

    testai++;
    if (hashFunction(longInput) != "") {
        sekmingi++;
    }

    string originalas = "ciatestas";

    string pakeistaPradz = "xiatestas";
    string pakeistasVidur = "ciatxstas";
    string pakeistaPabaig = "ciatestax";

    testai++;
    if (hashFunction(originalas) != hashFunction(pakeistaPradz)) {
        sekmingi++;
    }

    testai++;
    if (hashFunction(originalas) != hashFunction(pakeistasVidur)) {
        sekmingi++;
    }

    testai++;
    if (hashFunction(originalas) != hashFunction(pakeistaPabaig)) {
        sekmingi++;
    }

    testai++;
    if (hashFunction("abcabcabcabc") != hashFunction("abcdef")) {
        sekmingi++;
    }

    testai++;
    if (hashFunction("abcdef") != hashFunction("fedcba")) {
        sekmingi++;
    }

    testai++;
    if (hashFunction(" tekstas") != hashFunction("tekstas ")) {
        sekmingi++;
    }

    testai++;
    if (hashFunction("tekstas") != hashFunction("tekstas\n")) {
        sekmingi++;
    }

    string utf8Input = "ąčęėįšųūž";

    testai++;
    if (hashFunction(utf8Input) != "") {
        sekmingi++;
    }

    cout << sekmingi << "/" << testai << " testai sekmingi" << endl;
}

void testSameInput()
{
    string tekstas = "labas";
    string hashas = hashFunction(tekstas);

    string fileContent;

    if (!readFile("input.txt", fileContent)) {
        cout << "Rankines ir failo ivesties testas: Nepavyko" << endl;
        return;
    }

    string fileHash = hashFunction(fileContent);

    if (hashas == fileHash) {
        cout << "Rankines ir failo ivesties testas: Sekmingas" << endl;
    }
    else {
        cout << "Rankines ir failo ivesties testas: Nepavyko" << endl;
    }
}

void testDeterminism()
{
    string inputA = "labas";
    string inputB = "testas";

    string hashA1 = hashFunction(inputA);
    string hashB = hashFunction(inputB);
    string hashA2 = hashFunction(inputA);

    if (hashA1 == hashA2 && hashA1 != hashB) {
        cout << "Determinizmo testas: Sekmingas" << endl;
    }
    else {
        cout << "Determinizmo testas: Nepavyko" << endl;
    }
}

void testEfficiency()
{
    vector<string> lines;

    if (!readLines("konstitucija.txt", lines)) {
        cout << "Efektyvumo testas: Nepavyko nuskaityti failo" << endl;
        return;
    }

    ofstream results("efektyvumo_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Efektyvumo testas: Nepavyko sukurti rezultatu failo" << endl;
        return;
    }

    results << std::setw(10) << "Eilutes"
            << std::setw(10) << "Baitai"
            << std::setw(15) << "Vidurkis"
            << std::setw(12) << "Min"
            << std::setw(12) << "Max" << endl;

    int lineCount = 1;

    while (true) {
        int currentLineCount = lineCount;

        if (currentLineCount > lines.size()) {
            currentLineCount = lines.size();
        }

        string input;

        for (int i = 0; i < currentLineCount; i++) {
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

            double time =
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    end - start
                ).count();

            times.push_back(time);
        }

        double average = 0;

        for (double time : times) {
            average += time;
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

        results << std::setw(10) << currentLineCount
                << std::setw(10) << input.size()
                << std::setw(15) << average
                << std::setw(12) << minTime
                << std::setw(12) << maxTime << endl;

        if (currentLineCount == lines.size()) {
            break;
        }

        lineCount = lineCount * 2;
    }

    results.close();

    cout << "Efektyvumo testas: Rezultatai issaugoti" << endl;
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

    results << std::setw(12) << "Ilgis" << std::setw(18) << "Poru kolizijos" << endl;

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

    cout << "Koliziju testas: Rezultatai issaugoti" << endl;
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

                int difference =
                    hexValue(hashA[j]) ^ hexValue(hashB[j]);

                for (int k = 0; k < 4; k++) {
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

            if (hexDifference < minHex) {
                minHex = hexDifference;
            }

            if (hexDifference > maxHex) {
                maxHex = hexDifference;
            }

            bitAverage += bitDifference;
            hexAverage += hexDifference;

            histogram[bitDifference / 8]++;
        }

        bitAverage = bitAverage / 25000;
        hexAverage = hexAverage / 25000;

        results << std::setw(10) << length
                << std::setw(15) << minBits * 100.0 / 256
                << std::setw(15) << maxBits * 100.0 / 256
                << std::setw(15) << bitAverage * 100.0 / 256
                << std::setw(15) << minHex * 100.0 / 64
                << std::setw(15) << maxHex * 100.0 / 64
                << std::setw(15) << hexAverage * 100.0 / 64
                << endl;

        totalBitAverage += bitAverage;
        totalHexAverage += hexAverage;
    }

    results << endl;
    results << "Bendras rezultatas:" << endl;
    results << "Poru: 100000" << endl;

    results << "Bitu skirtumo vidurkis: "
            << totalBitAverage / 4 * 100.0 / 256 << "%" << endl;

    results << "Hex skirtumo vidurkis: "
            << totalHexAverage / 4 * 100.0 / 64 << "%" << endl;

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

    cout << "Lavinos efektas: Rezultatai issaugoti" << endl;
}

void testSalt()
{
    string target = "4729";
    string salt = "ABC";

    ofstream results("spejimo_rezultatai.txt");

    if (!results.is_open()) {
        cout << "Nepavyko sukurti rezultatu failo!" << endl;
        return;
    }

    string targetHash = hashFunction(target);

    int attempts = 0;
    int firstAttempts = 0;
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

            if (firstAttempts == 0) {
                firstAttempts = attempts;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    double time = std::chrono::duration_cast<std::chrono::microseconds>
                  (end - start).count();

    results << "Be druskos" << endl;
    results << "Tikslas: " << target << endl;
    results << "Bandymu: " << attempts << endl;
    results << "Sutapimu: " << matches << endl;
    results << "Bandymu iki pirmo sutapimo: " << firstAttempts << endl;
    results << "Laikas: " << time << " us" << endl;
    results << endl;


    targetHash = hashFunction(target + salt);

    attempts = 0;
    firstAttempts = 0;
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

            if (firstAttempts == 0) {
                firstAttempts = attempts;
            }
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
    results << "Bandymu iki pirmo sutapimo: " << firstAttempts << endl;
    results << "Laikas: " << time << " us" << endl;
    results << endl;


    string secret = "X7pQ2";
    string secretHash = hashFunction(target + secret);

    results << "Slaptas atsitiktinumas" << endl;
    results << "Atsitiktinumas: " << secret << endl;

    if (hashFunction(target + secret) == secretHash) {
        results << "Hash patikrinimas: TAIP" << endl;
    }

    results.close();

    cout << "Spejimo testas: Rezultatai issaugoti" << endl;
}