#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int main() {
    string line = "var3;";
    int index = 0;

    string id = "";
    bool valid = true;
    int i = index;

    char c = line[i];
    if (c > '0' && c < '9') { // first character is a number
        cout << "error" << endl;
        exit(-1);
    }

    while (i < line.length() && valid) {
        c = line[i]; // current character

        cout << "character: " << c << endl;

        if ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ) {// if character is a letter or number
            id += c;
            cout << "id so far: " << id << endl;
        }
        else {
            valid = false;
            cout << "error in: " << c << endl;
        }
                    

        i++;
    }
    cout << "id: " << id << endl;
    
    if (id == "main") // valid keyword
        cout << "t_main : " << "main" << endl; 
    else // valid id
        cout << "t_id : " << id << endl;
    
    cout <<  i << endl; // return where valid id ends

    return 0;
}