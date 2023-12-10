#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <unordered_map>
#include "hash_map.h"

int main () {
	using namespace std;
	using namespace std::chrono;
	using namespace pr;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)

	std::vector<string> vect;
	
	std::vector<pair<string,int>> vect_pair;

	
	unordered_map<string, int> map; 


	

	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		//TME 3
		auto val = map.find(word);
		if (val == map.end()) {
			map.insert(std::pair<std::string,int>(word,1));
		}
		else {
			val->second++;
		}

		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;


	auto nb = map.find("war");
	if (nb != map.end()) {
		cout << "Found a total of " << nb->second << " war in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 war in hashmap" << endl;
	}
	nb = map.find("peace");
	if (nb != map.end()) {
		cout << "Found a total of " << nb->second << " peace in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 peace in hashmap" << endl;
	}
	nb = map.find("toto");
	if (nb != map.end()) {
		cout << "Found a total of " << nb->second << " toto in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 toto in hashmap" << endl;
	} 


	cout << "\n\n\nMaking a vector out of the hashmap and sorting it"<< endl;

	std::vector<pair<string,int>> vecQ5;
	for(auto it = map.begin() ;it!=map.end() ;++it){
		vecQ5.push_back(std::pair<std::string,int>((*it).first,(*it).second));
	}

	cout << "\n10 Most used words in the book\n" << endl;
	std::sort(vecQ5.begin(),vecQ5.end(),[](pair<string,int> a, pair<string,int> b){ return a.second > b.second;});
	for (int i = 0 ; i<10; ++i){
		cout << i+1<<" : "<< vecQ5[i].first << " is here " <<vecQ5[i].second<< " times"<<endl;
	}


     //Question 8
    cout << "\nMaking a reverse map\n" << endl;
   
    unordered_map<int,forward_list<string>> reverse;

    for(auto it = map.begin() ;it!=map.end() ;++it){
        reverse[(*it).second].push_front((*it).first);
	}

    int n = 34562;

    cout << "\nShowing words here " <<n<<" times:\n"<< endl;
    for(auto it = (*reverse.find(n)).second.begin() ;it!=(*reverse.find(n)).second.end() ;++it){
       cout<<*it<<"\n"<<endl; 
	}

    return 0;
}


