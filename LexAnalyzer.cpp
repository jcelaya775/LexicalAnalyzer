#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class LexAnalyzer {
    private:
        vector<string> lexemes;  // source code file lexemes   
    	vector<string> tokens;   // source code file tokens
    	map<string, string> tokenmap;  // valid lexeme/token pairs

    	// other private methods 

        int checkAlpha(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where the valid id ends if lexeme is valid
            // or -1 if lexeme is invalid
            string id = "";
            bool valid = true;
            int i = index;

            char c = line[i];
            if (c > '0' && c < '9') // first character is a number
                return -1;

            while (i < line.length() && valid) {
                c = line[i]; // current character
                cout << "character: " << c << endl;

                if ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ) // if character is a letter or number
                    id += c;
                else 
                   valid = false;           

                i++;
            }

            cout << "id: " << id << endl;
            
            if (tokenmap[id] != "") { // valid keyword
                lexemes.push_back(id);
                tokens.push_back(tokenmap[id]);
            } else { // valid id
                lexemes.push_back(id);
                tokens.push_back("t_id");
            }

            return i; // return where valid id ends
        };
        
        int checkInt(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where the valid int ends if lexeme is valid
            // or -1 if lexeme is invalid
            string integer = "";
            bool valid = true;
            int i = index;

            char c = line[i];
            if (c <= '0' || c >= '9') // first character is a not a number
                return -1;

            while (i < line.length() && valid) {
                char c = line[i]; // current character
                 
                if (c >= '0' && c <= '9') // if character is a letter
                    integer += c;
                else // if not a letter
                   valid = false;           

                i++;
            }

            cout << "int: " << integer << endl;

            if (i != line.length() && integer[i] >= 'A' && integer[i] <= 'z') // next character is a letter
                
                return -1;
            else {
                lexemes.push_back(integer);
                tokens.push_back("t_int");
                return i; // return where valid id ends
            }
        };
        
        int checkString(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where the valid string ends if lexeme is valid
            // or -1 if lexeme is invalid
            string str = "";
            bool valid = true;
            int i = index;

            char c = line[i];
            if (c == '"') // first character is a double quote
                i++;
            else
                return -1;

            while (i < line.length() && valid) {
                c = line[i]; // current character

                if  (c == '"') // end of string
                    valid = false;
                else 
                   str += c;

                i++;
            }

            cout << "string: " << str << endl;

            if (str[i-1] == '"') { // last character is a double quote
                lexemes.push_back(str);
                tokens.push_back("t_str");
                return i; // return where valid id ends
            }
            else 
                return -1;

        };

    public: 
        LexAnalyzer(istream &infile){
            // pre: parameter refers to open data file consisting of token and
            // lexeme pairs i.e.  s_and and t_begin begin t_int 27.  Each pair    // appears on its own input line.
            // post: tokenmap has been populated
            // istreambuf_iterator<string> isitr(infile);
            string lexeme, token;
            while (infile >> token >> lexeme) {
                tokenmap[lexeme] = token;
                cout << token << " " << lexeme << endl;
            }
        };
        void scanFile(istream& infile, ostream& outfile) {
            // pre: 1st parameter refers to an open text file that contains source 
            // code in the language, 2nd parameter refers to an open empty output 
            // file 
            // post: If no error, the token and lexeme pairs for the given input 
            // file have been written to the output file.  If there is an error, 
            // the incomplete token/lexeme pairs, as well as an error message have // written to the output file.  A success or fail message has printed // to the console.
            string line;
            bool valid;
            
            cout << endl;

            while (!infile.eof()) {
                getline(infile, line);

                cout << line << endl;
                
                valid = true;
                int i=0;
                while (i < line.length() && valid) {
                    char c = line[i];

                    int alphaResult, intResult, stringResult;

                    alphaResult = checkAlpha(line, i);
                    intResult = checkInt(line, i);
                    stringResult = checkString(line, i);

                    if (alphaResult != -1)
                        i = alphaResult;
                    else if (intResult != -1)
                        i = intResult;
                    else if (stringResult != -1)
                        i = stringResult;
                    else 
                        valid = false;
                } 

            }

            if (valid) {
                outfile << "Source code file was scanned completely." << endl;
                cout <<  "Source code file was scanned completely." << endl;
            }
            else {
                outfile << "Source code file was scanned completely." << endl;
                cout << "Source code file was scanned completely." << endl;
            }
            
            for (int i=0; i<lexemes.size(); i++) {
                outfile << tokens[i] << " : " << lexemes[i] << endl;
            }
    };
};

int main() {
    // string datafilename, inputfilename, outputfilename;

    // // cout << "Enter data file name: ";
    // // cin >> datafilename;
    // // cout << "Enter input file name: ";
    // // cin >> inputfilename;
    // // cout << "Enter output file name: ";
    // // cin >> outputfilename;

    ifstream datafile("tokenlexemedata.txt");
    ifstream infile("sample.txt");
    ofstream outfile("output.txt");

    if (!datafile) {
        cout << "error opening data file..." << endl;
        exit(-1);
    }
    if (!infile) {
        cout << "error opening input file..." << endl;
        exit(-1);
    }
    if (!outfile) {
        cout << "error opening output file..." << endl;
        exit(-1);
    }

    LexAnalyzer analyzer(datafile);
    analyzer.scanFile(infile, outfile);

    return 0;
}