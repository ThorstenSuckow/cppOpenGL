module;

#include <iostream>
#include <fstream>
#include <string>

export module IOUtil;

using namespace std;

export namespace IOUtil {



    string getContents(string filename) {

        ifstream infile {filename};

        if (!infile) {
            cerr << "Cannot open " << filename << endl;
        }
        string line;
        string fileContents = "";
        while (getline(infile, line)) {
            fileContents += line + "\n";
        }

        return fileContents;
    }

    void readInto(string filename, string& contents) {

        ifstream infile{ filename };

        if (!infile) {
            cerr << "Cannot open " << filename << endl;
        }
        string line;
        string fileContents = "";
        while (getline(infile, line)) {
            fileContents += line + "\n";
        }

        contents = fileContents;
    }


}