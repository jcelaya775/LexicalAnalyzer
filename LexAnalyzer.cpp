#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class LexAnalyzer{
    private:
        vector<string> lexemes;  // source code file lexemes   
    	vector<string> tokens;   // source code file tokens
    	map<string, string> tokenmap;  // valid lexeme/token pairs
    	// other private methods 
        // pre: current line that is being scanned
        // post: checks for longest valid sequence of characters.
        // returns index of last valid character if lexeme is valid
        // or -1 if lexeme is invalid
        int checkId(string lexeme); 
        // pre: current line that is being scanned
        // post: checks for longest valid sequence of characters.
        // returns index of last valid character if lexeme is valid
        // or -1 if lexeme is invalid
        int checkInt(string lexeme);
        // pre: current line that is being scanned
        // post: checks for longest valid sequence of characters.
        // returns index of last valid character if lexeme is valid
        // or -1 if lexeme is invalid
        int checkString(string lexeme);


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
                while (!infile.eof()) {
                    getline(infile, line);

                    string token = "";
                    bool valid;
                    int i=0;
                    while (!valid) {
                        token += line[i];
                        if (tokenmap[token] != "") { // if token exists in tokenmap
                            valid = true; // current token is valid
                        } else if (checkId(token) != -1 || checkInt(token) != -1 || checkString(token) != -1) { // check for valid id, int, or string
                            int index;
                            if (checkId(token) != -1) {
                                index = 
                                valid = true;
                            }
                        }
                        else 
                            valid = false // source code has an error
                    } 

                }

                //print to outfile
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