#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    map<string, string> m;
    m["hi"] = "ello govena";

    map<string, int>::iterator mitr;

    // for (mitr=m.begin(); mitr != m.end(); mitr++) 
    //     cout << mitr->first << endl;

    cout << (m["hi"] == "") << endl;

    return 0;
}