#pragma once

namespace pr{

    template<typename iterator> 

    size_t count (iterator begin, iterator end){ 
        size_t count = 0;

        while (begin != end){ 
            begin++; 
            count++; 
        } 
        return count; 
    }

    template<typename T,typename iterator> 
    size_t count_if_equal (iterator begin, iterator end, const T & val){
        size_t count = 0;

        while (begin != end){ 
            if(*begin==val) count++;
            begin++;
        }
        return count; 
    }

}