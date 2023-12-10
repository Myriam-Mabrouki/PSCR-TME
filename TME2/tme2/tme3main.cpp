#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include "hash_map.h"
#include "Algorithme.h"

using namespace std;
using namespace pr;

int main (){

    ifstream input = ifstream("./WarAndPeace.txt");


	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)

	
	//Question 3
	std::vector<pair<string,int>> vect_pair;

	//Question 6
	HashTable<string, int> hm = HashTable<string, int>(1000); 

    regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
         int * val = hm.get(word);
		if (!val) {
			hm.put(word, 1);
		}
		else {
			hm.put(word, *val  + 1);
		}
		
		

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

    cout << "Found a total of " << nombre_lu << " words." << endl;

    vect_pair = hm.vectorize(vect_pair);
    size_t compte_it = count(vect_pair.begin(),vect_pair.end());
    cout << "Found a total of " << compte_it << " entries with iterators." << endl;


    vector<int> vs;
    vs.push_back(1);
    vs.push_back(1);
    vs.push_back(1);
    vs.push_back(2);
    vs.push_back(3);
    vs.push_back(4);
    compte_it = count(vs.begin(),vs.end(),1);
    cout << "Found a total of " << compte_it << " ones." << endl;



    
}