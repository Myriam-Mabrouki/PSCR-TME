#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "rsleep.h"

using namespace std;

int vies = 3;

void handler(int sig){
    cout << "Perdre une vie" << endl;
    vies--;

}

void attaque (pid_t adversaire){
    cout<<"Je suis " << getpid() << " et j'attaque !" << endl;
    signal(SIGINT,handler);
    if(kill(adversaire,SIGINT) == -1){
        cout<<"Mon adversaire est tombe !"<<endl;
        exit(0);
    }
    randsleep();
}

void defense(){
    cout<<"Je suis " << getpid() << " et je défends !" << endl;
    signal(SIGINT,SIG_IGN);
    randsleep();
}

void combat(pid_t adversaire){
    while(true){
        defense();
        attaque(adversaire);
        if(vies<=0){
            cout << "J'ai perdu snifsnif" << endl;
            exit(1);
        }
    }
}


int main (){

    pid_t luke;
    int ret = 0;
    sigset_t set;
    sigset_t oldset;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    //sigprocmask(SIG_BLOCK, &set, &oldset);
    signal(SIGINT,SIG_IGN);
    if ((luke = fork())) {
    }
    //sigprocmask(SIG_SETMASK, &oldset, nullptr);
    //Le main qui regarde le duel
    if (luke!=0 ) {
        cout<< "Je suis vador" <<endl;
        sleep(1);
        combat(luke);
    }
    else {
        cout<< "Je suis luke" <<endl;
        
        combat(getppid());
    }

    
    wait(&ret);
    ret = WEXITSTATUS(ret);
    switch(ret){
        case 1:
            cout<<"Je suis ton père"<<endl;
            break;
        case 0:
            cout<<"NOOOOOOOOOOOOOOOOOO"<<endl;
            break;
        default:
            cout<<"WTF?"<<endl;
            break;
    }
}