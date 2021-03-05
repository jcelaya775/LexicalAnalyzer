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

        // pre: current line that is being scanned and index to start scanning from
        // post: checks for longest valid sequence of characters.
        // returns index where the valid id ends if lexeme is valid
        // or -1 if lexeme is invalid
        int checkId(string line, int index) {
            string id = "";
            bool valid = true;
            int i = index;

            while (i < line.length() && valid) {
                char c = line[i]; // current character

                if ( (c > 'A' && c < 'Z') || (c > 'a' && c < 'z') ) // if character is a letter
                    id += c;
                else // if not a letter
                   valid = false;           

                i++;
            }

            if (id == "") { // first character was not a letter
                lexemes.push_back(id);
                tokens.push_back("t_id");
                return -1;
            }
            else 
                return i; // return where valid id ends
        };
        // pre: current line that is being scanned and index to start scanning from
        // post: checks for longest valid sequence of characters.
        // returns index where the valid int ends if lexeme is valid
        // or -1 if lexeme is invalid
        int checkInt(string line, int index) {
            string integer = "";
            bool valid = true;
            int i = index;

            while (i < line.length() && valid) {
                char c = line[i]; // current character
                 
                if (c > '0' && c < '9') // if character is a letter
                    integer += c;
                else // if not a letter
                   valid = false;           

                i++;
            }

            if (integer == "") // first character was not a letter
                return -1;
            else {
                lexemes.push_back(integer);
                tokens.push_back("t_int");
                return i; // return where valid id ends
            }
        };
        // pre: current line that is being scanned and index to start scanning from
        // post: checks for longest valid sequence of characters.
        // returns index where the valid line ends if lexeme is valid
        // or -1 if lexeme is invalid
        int checkString(string line, int index) { // COMPARE USING CHAR INSTEAD OF LINE[I] if you get an error
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

            if (str[i-1] == '"') { // last character is a double quote
                lexemes.push_back(str);
                tokens.push_back("t_str");
                return -1;
            }
            else 
                return i; // return where valid id ends

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
            bool valid = true;

            while (!infile.eof()) {
                getline(infile, line);

                
                string word = "";
                int i=0;
                while (i < line.length() && valid) {
                    word += line[i];
                    if (tokenmap[word] != "") { // found in tokenmap
                        if (checkString(line, i) != -1) {
                            i += checkString(line, i); // shift index to next character
                            word = ""; // reset word that is being checked
                        } 
                        else {
                            lexemes.push_back(tokenmap[word]);
                            tokens.push_back(word);
                            i += word.length();
                            word = ""; 
                        }
                    }
                    else if (checkId(line, i) != -1) { // begins with a letter
                        i += checkId(line, i); // shift index to next character in line
                        word = "";
                    }
                    else if (checkInt(line, i) != -1) {
                        i += checkInt(line, i);
                        word = "";
                    }
                    else 
                        valid = false;

                    i++;
                } 

            }

            if (valid) {
                outfile << "Source code file was scanned completely." << endl;
            }
            else {
                outfile << "Source code file was scanned completely." << endl;
            }
            
            for (int i=0; i<lexemes.size(); i++) {
                outfile << tokens[i] << " : " << lexemes[i] << endl;
            }
    };
};

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