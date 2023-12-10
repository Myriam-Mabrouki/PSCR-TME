//Question 5
#pragma once
#include <vector>
#include <forward_list>
#include <utility>

namespace pr {

    template <typename K, typename V>

    class HashTable {



        public: 
            class Entry {
                public: 
                    const K key;
                    V val;
                
                    Entry (K key, V val):key(key), val(val){}
            };

            std::vector<std::forward_list<Entry>> bucket;
            size_t size_;


            class iterator{

                private:
                //obligé de rajouter typename partout sinon le compilo chouine
                    typename std::vector<std::forward_list<Entry>>::iterator bucketEnd;
                    typename std::vector<std::forward_list<Entry>>::iterator vit;
                    typename std::forward_list<Entry>::iterator lit;

                public:
                    //obliger de rajouter const sinon le compilo chouine ENCORE
                    iterator(const typename std::vector<std::forward_list<Entry>>::iterator & bucketEnd,const typename std::vector<std::forward_list<Entry>>::iterator & vit,const typename std::forward_list<Entry>::iterator & lit):bucketEnd(bucketEnd), vit(vit),lit(lit){}

                    iterator & operator++(){
                        lit++;

                        if(lit == vit->end()){
                            vit++;

                            while ((vit->empty()) && (vit != bucketEnd)) { 
                                vit++;
                            } 

                            if (vit != bucketEnd) { 
                                lit = vit->begin(); 
                            } 
                        } 

                        return *this;
                    }

                    Entry & operator*(){
                        return *lit;
                    }

                    bool operator!=(iterator it) { 
                        return (vit != it.vit || lit != it.lit); 
                    }

            };

        
            HashTable (int size) {
                bucket.reserve(size);
                for(int i = 0;i<size;i++){
                    bucket.push_back(std::forward_list<Entry>());
                }
            }
            ~HashTable () {
                for (size_t i = 0; i < bucket.size(); ++i) {
                    bucket[i].clear();
                }
                bucket.clear();
            }


            V * get (const K & key){
                size_t h = std::hash<K>()(key);
                size_t target = h % bucket.capacity();
                
                for (Entry &ent : bucket[target]){
                    if (ent.key  == key) {
                        return &ent.val;
                    }
                }

                
                return nullptr; //key not found
            }

           

            
            bool put (const K & key, const V & value) {
                
                //Mise à jour d'une valeur déjà existante
                V * val = get (key);
                if (val) {
                    *val = value;
                    return true;
                }

                //

                //Réalisation d'une insertion    
                size_t h = std::hash<K>()(key);
                size_t target = h % bucket.size();
                size_++;

                bucket[target].push_front(Entry(key, value));
                return false;
            }

            size_t size () const {
                return size_;
            }

            /*void grow () {
                HashTable newTable = HashTable(bucket.size()*2);
                size_t size = bucket.size();
                for (size_t i = 0 ; i <size ;i++) {
                    for (auto & entry : bucket[i]) {
                        newTable.put(entry.key, entry.val);
                    }
                }
                bucket = newTable.bucket;
                
            }*/

            std::vector<std::pair<std::string,int>>& vectorize(std::vector<std::pair<std::string,int>>& vec){
                
                int capa = bucket.capacity();
                for(int i = 0 ; i <capa ;i++){
                    if(bucket[i].empty()==false){
                        for(auto it : bucket[i] ){
                            vec.push_back(std::pair<std::string,int>(it.key,it.val));
                        }
                    }
                }
                return vec;
            }



            iterator begin(){

                if(size_==0){
                    return iterator(bucket.end(),bucket.end(),(bucket.front()).end());
                }
                
                //HAHAHA IL FAUT LE TYPENAME ICI AUSSI
                typename std::vector<std::forward_list<Entry>>::iterator vit = bucket.begin();

                while (vit->empty() && vit != bucket.end()){ 
                    vit++; 
                }

                if (vit != bucket.end()) { 
                    
                    return iterator(bucket.end(), vit, vit->begin());
                } else { 
                    
                    return iterator(bucket.end(), bucket.end(), (bucket.front()).end());
                } 

            } 

            iterator end(){                
                return iterator(bucket.end(),bucket.end(),(bucket.front()).end());
            } 
            
            

    };

    //fin du namespace
}

/*
     |/|
     |/|
     |/|
     |/|
     |/|
     |/|
     |/| /¯)
     |/|/\/
     |/|\/
    (¯¯¯)
    (¯¯¯)
    (¯¯¯)
    (¯¯¯)
    (¯¯¯)
    /¯¯/\
   / ,^./\
  / /   \/\
 / /     \/\
( (       )/)
| |       |/|
| |       |/|
| |       |/|
( (       )/)
 \ \     / /
  \ `---' /
   `-----'    
*/