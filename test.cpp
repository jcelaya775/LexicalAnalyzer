#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() {
    // string line;
    // ifstream infile("tokenlexemedata.txt");

    //  while (!infile.eof()) {
    //     getline(infile, line);

    //     cout << line << endl;
    //  }

    // ofstream outfile("new.txt");

    // for (int i=0; i<10; i++) {
    //     outfile << "hello" << endl;
    // }
    string s;
    char c;
    cout << "Enter character: ";
    cin >> c;
    cout << endl;

    for (int i=0; i<10; i++) 
        s += c;

    cout << s << endl;

    // if ( (c > 'A' && c < 'Z') || (c > 'a' && c < 'z') )
    //     cout << "Is a letter!" << endl;
    // else    
    //     cout << "No letter here!" << endl;

    return 0;
}