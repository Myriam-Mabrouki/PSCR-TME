#include "Barrier.h"

using namespace std;

namespace pr {
    
    Barrier::Barrier(int goal):goal(goal),cpt(0){}
        
    void Barrier::done(){
        unique_lock<mutex> l(m);
        cpt++;
        if (cpt==goal) cond.notify_all();
    }

    void Barrier::waitFor(){
        unique_lock<mutex> l(m);
        while (cpt!=goal){
            cond.wait(l);
        }
    }

    Barrier::~Barrier(){}

}