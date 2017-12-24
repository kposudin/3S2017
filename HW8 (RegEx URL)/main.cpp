//
//  main.cpp
//  HW8 (RexEx URL)
//
//  Created by Посудин Константин Михайлович on 25.12.17.
//  Copyright © 2017 tin. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;
int main(int argc, const char * argv[]) {
    string path;
    cout <<"Input file path" << endl;
    cin >> path;
    ifstream fin;
    fin.open(path);
    ofstream fout;
    fout.open("output.txt");
    regex rx(R"(^(https?|ftp|telnet:\/\/)?(www\.)?([\w\.]+)\.([a-z]{2,6}\.?)(\/[\w\.]*)*\/?$)");
    string line;
    while (fin>>line){
        if (regex_match(line, rx)) {
            fout << line << endl;
        }
    }
    return 0;
}
