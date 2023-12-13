#include "Banque.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace pr;

const int NB_THREAD = 10;

void transfertloop(Banque &b){

	for (int k = 0; k<10000;k++){
		int i = std::rand() % 3; //debiteur
		int j;
		while ((j = std::rand() % 3)==i); //crediteur (compte différent du débiteur)
		int m = std::rand() % 99 + 1; //montant
		//cout<<"Début du transfert d'un montant de "<<m<<" de "<<i<<" vers "<<j<<endl;
		b.transfert(i, j, m);
		cout<<"Fin du transfert d'un montant de "<<m<<" de "<<i<<" vers "<<j<<endl;
		// int sleep_time = std::rand() % 20;
		// this_thread::sleep_for(chrono::milliseconds(sleep_time));
	}

}

void comptabiliser2 (Banque &b) {
	for (int k = 0; k<100;k++){
		cout<<"Debut comptabiliser "<<k<<endl;
		b.comptabiliser(100*200);
		cout<<"Fin comptabiliser"<<endl;
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

int main () {

	std::srand(std::time(nullptr));

	vector<thread> threads;
	Banque *b = new Banque(200, 100);

	for (int i = 0; i < NB_THREAD; i++){
		cout<<"Création du thread "<<i<<endl;
		threads.emplace_back(transfertloop, std::ref(*b));
	}


	threads.emplace_back(comptabiliser2, std::ref(*b));

	for (auto & t : threads) {
		t.join();
	}

	cout << "Fini !" << endl;

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}

