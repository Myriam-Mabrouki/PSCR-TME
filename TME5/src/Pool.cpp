#include "Pool.h"

namespace pr {

    Pool::Pool(int qsize):queue(qsize){}

    void poolWorker(Queue<Job> & qj) {
        while (true){
            Job * j = qj.pop();
            if(j==nullptr) return;
            j->run();
            delete j;
        }
    }

    void Pool::start (int nbthread) {
        for (int i = 0; i < nbthread; i++){
            threads.emplace_back([&](){ poolWorker(queue); });
        }
    }

	void Pool::submit (Job * j){
        queue.push(j);
    }

	void Pool::stop() {
        queue.setBlockuing(false);
        for (auto &t : threads){
            t.join();
        }
        threads.clear();
    }

}