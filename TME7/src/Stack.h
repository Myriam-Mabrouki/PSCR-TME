#pragma once
#include <fcntl.h> 
#include <cstring> // size_t,memset
#include <semaphore.h>
#include <iostream>

namespace pr {

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	sem_t prod;
	sem_t cons;
	sem_t mt_sz;
public :
	Stack () : sz(0) { 
		memset(tab,0,sizeof tab);
		sem_init(&prod, 1, STACKSIZE);
		sem_init(&cons, 1, 0);
		sem_init(&mt_sz, 1, 1);
	}

	~Stack(){
		sem_destroy(&prod);
		sem_destroy(&cons);
		sem_destroy(&mt_sz);
	}

	T pop () {
		// bloquer si vide
		sem_wait(&cons);
		sem_wait(&mt_sz);
		T toret = tab[--sz];
		sem_post(&mt_sz);
		sem_post(&prod);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		sem_wait(&prod);
		sem_wait(&mt_sz);
		tab[sz++] = elt;
		sem_post(&mt_sz);
		sem_post(&cons);
	}
};

}
