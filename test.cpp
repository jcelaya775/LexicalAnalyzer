#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() {
    string line;
    ifstream infile("tokenlexemedata.txt");

     while (!infile.eof()) {
        getline(infile, line);

        cout << line << endl;
     }

    ofstream outfile("new.txt");

    for (int i=0; i<10; i++) {
        outfile << "hello" << endl;
    }
        

    return 0;
}