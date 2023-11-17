#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <semaphore.h>
#include <sys/mman.h>

using namespace std;
using namespace pr;

bool ninterupted = true;

void producteur (Stack<char> * stack) {
	char c ;
	std::cout << "début prod" << std::endl;
	while (cin.get(c)) {
		std::cout << "snifsnif" << std::endl;
		stack->push(c);
	}
}

void consomateur (Stack<char> * stack) {
	while (true) {
		char c = stack->pop();
		cout << c << flush ;
	}
}

int main () {

	int fd;
	Stack<char> * sp;

	/* Creer le segment monshm, ouverture en R/W */
	if ((fd = shm_open("/monshm", O_RDWR | O_CREAT, 0600)) == -1) {
		perror("shm_open");
		exit(1);
	}

	/* Allouer au segment une taille pour stocker un entier */
	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(1);
	}

	/* “mapper” le segment en R/W partagé */
	if ((sp = (Stack<char> *) mmap(NULL, sizeof(Stack<char>), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	Stack<char> * s = new (sp) Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		std::cout << "fin prod" << std::endl;
		return 0;
	}

	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		std::cout << "fin conso" << std::endl;
		return 0;
	}

	wait(0);
	wait(0);

	signal(SIGINT,[](int var){ninterupted = false;});

	while(ninterupted){}
	/* “detacher” le segment */
	std::cout << "interupted detacher le segment" << std::endl;
	munmap(sp, sizeof(int));

	/* detruire le segment */
	std::cout << "detruire le segment" << std::endl;
	shm_unlink("/monshm");

	std::cout << "Appel destructeur" << std::endl;

	sp->~Stack<char>();
	
	return 0;
}

