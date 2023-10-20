#pragma once 

#include <mutex>
#include <cstdlib>
#include <condition_variable>

namespace pr {
    
    class Barrier {
        mutable std::mutex m;
        std::condition_variable cond;
        int cpt;
        const int goal;

        public:
            Barrier(int goal);
            void done();
            void waitFor();
            ~Barrier();
    };
};