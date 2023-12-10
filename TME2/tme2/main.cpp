#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
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

	//Question 2
	size_t nb_mots_differents = 0;
	std::vector<string> vect;
	
	//Question 3
	std::vector<pair<string,int>> vect_pair;

	//Question 6
	HashTable<string, int> hm = HashTable<string, int>(1000); 

	//Question 7
	

	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		
		//Question 2
		//On cherche s'il existe un mot différent
		/*bool found = false;
		for (size_t i=0; i<vect.size(); ++i){
			if (!word.compare(vect[i])){
				found = true;
				break;
			}
		}

		//S'il n'en existe pas, on l'ajoute
		if (!found){
			vect.push_back(word);
			nb_mots_differents++;
		}

		//Question 3
		bool found2 = false;
		for (size_t i=0; i<vect_pair.size(); ++i){
			if (!word.compare(vect_pair[i].first)){
				vect_pair[i].second++;
				found2 =true;
				break;
			}
		}

		if (!found2){
			vect_pair.push_back(pair<string,int>(word,1));
		}
		*/
		//Question 6
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

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;
	cout << "Found a total of " << nb_mots_differents << " different words." << endl;

	//Question 3
	bool found_war = false, found_peace = false, found_toto = false;
	for (size_t i=0; i<vect_pair.size(); i++){
		if (!(new string("war"))->compare(vect_pair[i].first)){
			cout << "Found a total of " << vect_pair[i].second << " war." << endl;
			found_war = true;
		}
		if (!(new string("peace"))->compare(vect_pair[i].first)){
			cout << "Found a total of " << vect_pair[i].second << " peace." << endl;
			found_peace = true;
		}
		if (!(new string("toto"))->compare(vect_pair[i].first)){
			cout << "Found a total of " << vect_pair[i].second << " toto." << endl;
			found_toto = true;
		}
	}

	if (!found_war) {
		cout << "Found a total of 0 war." << endl;
	}
	if (!found_peace) {
		cout << "Found a total of 0 peace." << endl;
	}
	if (!found_toto) {
		cout << "Found a total of 0 toto." << endl;
	}

	//Question 6
	 int * nb = hm.get("war");
	if (nb) {
		cout << "Found a total of " << *nb << " war in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 war in hashmap" << endl;
	}
	nb = hm.get("peace");
	if (nb) {
		cout << "Found a total of " << *nb << " peace in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 peace in hashmap" << endl;
	}
	nb = hm.get("toto");
	if (nb) {
		cout << "Found a total of " << *nb << " toto in hashmap" << endl;
	}
	else {
		cout << "Found a total of 0 toto in hashmap" << endl;
	} 


	cout << "\n\n\nMaking a vector out of the hashmap and sorting it"<< endl;
	vect_pair = hm.vectorize(vect_pair);

	cout << "\nSorting Vector"<<endl;
	std::sort(vect_pair.begin(),vect_pair.end(),[](pair<string,int> a, pair<string,int> b){ return a.second > b.second;});

	cout << "\n10 Most used words in the book\n" << endl;
	for (int i = 0 ; i<10; ++i){
		cout << i+1<<" : "<< vect_pair[i].first << " is here " <<vect_pair[i].second<< " times"<<endl;
	}

	cout << "\n\n\n###TME 3###\n" << endl;

	std::vector<pair<string,int>> vecQ5;
	for(auto it = hm.begin() ;it!=hm.end() ;++it){
		vecQ5.push_back(std::pair<std::string,int>((*it).key,(*it).val));
	}

	cout << "\n10 Most used words in the book\n" << endl;
	std::sort(vecQ5.begin(),vecQ5.end(),[](pair<string,int> a, pair<string,int> b){ return a.second > b.second;});
	for (int i = 0 ; i<10; ++i){
		cout << i+1<<" : "<< vecQ5[i].first << " is here " <<vecQ5[i].second<< " times"<<endl;
	}



    return 0;
}


