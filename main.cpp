#include <iostream>
#include <fstream>
#include <string>
#include "LexAnalyzer.h"

using namespace std;

int main() {
    string inputFile, outputFile;

    cout << "Enter input file name: ";
    cin >> inputFile;
    cout << "Enter output file name: ";
    cin >> outputFile;

    ifstream infile(inputFile);
    ofstream outfile(outputFile);

    if (!infile) {
        cout << "error opening input file..." << endl;
        exit(-1);
    }
    if (!outfile) {
        cout << "error opening output file..." << endl;
        exit(-1);
    }

    LexAnalyzer analyzer(infile);
    // analyzer.scanFile(/*source code*/, outfile);

    return 0;
}