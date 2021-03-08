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
            // post: returns index where the valid id ends
            string word = "";
            bool valid = true;
            int i = index;

            while (i < line.length() && valid) {
                char c = line[i]; // current character

                if (isalnum(c)) {// if character is a letter or number
                    word += c;
                    i++;
                }
                else 
                   valid = false;           
            }
            
            return i; // return where valid id ends
        };
        
        int checkInt(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where the valid int ends
            string integer = "";
            bool valid = true;
            int i = index;

            while (i < line.length() && valid) {
                char c = line[i]; // current character
                 
                if (isdigit(c)) { // if character is a letter
                    integer += c;
                    i++;
                }
                else // if not a letter
                   valid = false;           
            }
            
            return i; // return where valid id ends
        };
        int checkString(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where the valid string ends
            string str = "";
            bool valid = true;
            int i = index + 1;              

            while (i < line.length() && valid) {
                char c = line[i]; // current character

                if  (c == '\"') // end of string
                    valid = false;
                else 
                    str += c;

                i++;
            }

            return i; // return where valid id ends
        };
        int checkSymbol(string line, int index) {
            // pre: current line that is being scanned and index to start scanning from
            // post: returns index where valid symbol ends or -1 if lexeme is not a valid symbol
            if (index < line.length()-1 && tokenmap[line.substr(index, 2)] != "") { // valid symbol of length two 
                return index + 2;
            } else if (tokenmap[line.substr(index, 1)] != "") { // valid symbol of length one
                return index + 1;
            } else // not a valid symbol
                return -1;
        };
        string stringRange(string line, int begin, int end) {
            // pre: line of code
            // post: string starting at begin index and ending at end index
            int len = end - begin;
            return line.substr(begin, len);
        }
        string trimLeading(string line) { 
            // pre: line that may contain spaces
            // post: return line without leading spaces
            int i=0;
            while (i<line.length() && line[i] == ' ') {
                i++;
            }

            int len = line.length() - i + 1;


            return line.substr(i, len); // return remaining string
        }

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
            string errorMsg;
            bool valid = true;
            
            int lineCount = 1;
            while (!infile.eof() && valid) {
                getline(infile, line);
                line = trimLeading(line);
                
                int i=0;
                while (i < line.length() && valid) {
                    char c = line[i];
                    
                    if (c == ' ') 
                        i++;
                    else if (isalpha(c)) {
                        int alphaResult = checkAlpha(line, i);
                        string word = stringRange(line, i, alphaResult);

                        if (tokenmap[word] != "") { // valid keyword
                            lexemes.push_back(word);
                            tokens.push_back(tokenmap[word]);
                            
                        }
                        else { // valid id
                            lexemes.push_back(word);
                            tokens.push_back("t_id");
                        }

                        i = alphaResult; // index where vaild word ends
                    }
                    else if (isdigit(c)) {
                        int intResult = checkInt(line, i);
                        string integer = stringRange(line, i, intResult);

                        if (intResult == line.length() || (intResult != line.length() && !isalpha(line[intResult]))) { // next character is not a letter
                                lexemes.push_back(integer);
                                tokens.push_back("t_int");
                                i = intResult; // index where vaild word ends
                        }
                        else {
                            errorMsg = "Error parsing int: '" + integer + "' in line " + to_string(lineCount) + ":\n\t" + line;
                            valid = false;
                        }
                    }
                    else if (c == '\"') {
                        int stringResult = checkString(line, i);
                        string str = stringRange(line, i+1, stringResult-1);

                        if (line[i] == '\"' && line[stringResult-1] == '\"') { // starts and ends with quotes
                            lexemes.push_back(str);
                            tokens.push_back("t_str");
                            i = stringResult; // index where vaild word ends
                        } 
                        else {
                            str = stringRange(line, i, stringResult);
                            errorMsg = "Error parsing string: '" + str + "' in line " + to_string(lineCount) + ":\n\t" + line;
                            valid = false;
                        }
                    }
                    else {
                        int symbolResult = checkSymbol(line, i);
                        string symbol;

                        if (symbolResult != -1) {
                            symbol = stringRange(line, i, symbolResult);

                            if (symbol.length() == 2) {
                                lexemes.push_back(symbol);
                                tokens.push_back(tokenmap[symbol]);
                            } else if (symbol.length() == 1) {
                                lexemes.push_back(symbol);
                                tokens.push_back(tokenmap[symbol]);
                            }

                            i = symbolResult; // index where vaild word ends
                        } 
                        else {
                            if (i < line.length() -1 && !isalnum(line[i+1]))
                                symbol = stringRange(line, i, i+2);
                            else 
                                symbol = stringRange(line, i, i+1);

                            errorMsg = "Error parsing symbol '" + symbol + "' in line " + to_string(lineCount) + ":\n\t" + line;
                            valid = false;
                        }
                    } 
                }

                lineCount++;
            }

            if (valid) {
                outfile << "Source code file was scanned completely." <<"\n\n";
                cout <<  "Source code file was scanned completely." << endl;
            }
            else {
                outfile << "Error - Source code file was not scanned completely. " << errorMsg << "\n\n";
                cout << "Error - Source code file was not scanned completely. " << errorMsg << endl;
            }

            // print to output file
            for (int i=0; i<lexemes.size(); i++) {
                outfile << tokens[i] << " : " << lexemes[i] << endl;
            }
        }
};

int main() {
    string datafilename, inputfilename, outputfilename;

    cout << "Enter data file name: ";
    cin >> datafilename;
    cout << "Enter input file name: ";
    cin >> inputfilename;
    cout << "Enter output file name: ";
    cin >> outputfilename;
    cout << endl;

    ifstream datafile(datafilename);
    ifstream infile(inputfilename);
    ofstream outfile(outputfilename);

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