#include "Banque.h"

#include <iostream>
#include <unistd.h>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	// unique_lock<mutex> l(m);
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	if (deb > cred ) {
		crediteur.lock();
		debiteur.lock();
	}
	else {
		debiteur.lock();
		crediteur.lock();
	}


	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	
	if (deb > cred) {
		crediteur.unlock();
		debiteur.unlock();
	}
	else {
		debiteur.unlock();
		crediteur.unlock();
	}
	
	
}
size_t Banque::size() const {
	// unique_lock<mutex> l(m);
	return comptes.size();
}

bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	// unique_lock<mutex> l(m);
	for (const auto & compte : comptes) {
		compte.lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	else {
		cout << "Le bilan est bon !" << endl;
	}
	
	for (const auto & compte : comptes) {
		compte.unlock();
	}

	return bilan == attendu;
	
	
}
}
