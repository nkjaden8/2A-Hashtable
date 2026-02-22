/*
 * main.cpp
 *
 * Includes the main() function for the hashtable project.
 *
 * This code is included in the default build target.  It
 * produces the program run-main.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <utility>

#include "hashtable.h"
#include "hash_functions.h"
#include "random220.h"

using namespace std;


pair<int, double> experiment(int m) { //m is 
    // read the entire dictionary.txt
    ifstream inputfile("/Users/jaden/Desktop/CSCI220_Data_Structures/CSCI220_Data_Structures/Programing Projects/2A-Hashtable/dictionary.txt");
    hashtable<string, hash3> table;
    string str;

    double p = (2.0 * m) / 172823;
    
    vector<string> words;

    while( inputfile >> str ) {
    // should we use it for the experiment?
        if( bernoulli(p) ) {
        /** save str for testing, maybe in a container named words? **/
            words.push_back(str);
            // cout << str << endl;
            // should it go into the table?
            if( bernoulli(0.5) ) {
                table.insert(str);
            }
        }
    }

    inputfile.close();

    double tests = 0;
    double comparisons = 0;
    /** for every word in the experiment (not every word in dictionary.txt!) **/
    for( string str: words ) {
        // should we use it for testing?
        if( bernoulli( 1000.0/words.size() ) ) {
            tests++;
            comparisons += table.compares(str);
        }
    }
    // cout << table.size() << " " << comparisons/tests << endl;
    // pair<int, double> data = make_pair(table.size(), comparisons/tests);
    return {table.size(), comparisons/tests};

}




int main() {
    // You can use this main() to run your own analysis or testing code.
    cout << "If you are seeing this, you have successfully run main!" << endl;

    ofstream finalFile("/Users/jaden/Desktop/CSCI220_Data_Structures/CSCI220_Data_Structures/Programing Projects/2A-Hashtable/2A-Results_Hash3.csv");
    seed_now();

    for (size_t i = 0; i < 100; i++)
    {
        //2000 + (850 * i)
        auto results = experiment(equalikely(2000, 172823/2));

        finalFile << results.first << "," << results.second << endl;
    }
    
    finalFile.close();




    // // ==================================================================
    // // The code below this point is relevant for the analysis part of the
    // // hashtable project.  You do not need it for the programming part.
    // // ==================================================================

    // // The code below illustrates how to use the provided hash function 
    // // "functional" objects, and lets you see the different hash values 
    // // produced by each.
    // hash0 h0;
    // hash1 h1;
    // hash2 h2;
    // hash3 h3;
    // hash4 h4;

    // string s("Hello");
    // cout << h0(s) << endl;
    // cout << h1(s) << endl;
    // cout << h2(s) << endl;
    // cout << h3(s) << endl;
    // cout << h4(s) << endl;

    // // Here's how you create a hashtable to use a particular hash function:
    // hashtable<string, hash1> ht;
    // ht.insert(s);
}

