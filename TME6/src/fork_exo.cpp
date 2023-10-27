#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	pid_t new_father = 0;
	int cpt_in = 0;
	int i,j;
	for ( i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		std::cout << " i:j " << i << ":" << j << std::endl;
		cpt_in =0;

		new_father = getpid();		
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}
			else {
				cpt_in++;
			}
		}
		if (getpid() == new_father) {
			for (int cpt = 0; cpt < cpt_in; cpt++) {
				wait(nullptr);
			}
		}
	}

	if (i<=N && j==N){
		wait(nullptr);
	}
	
	return 0;
}
