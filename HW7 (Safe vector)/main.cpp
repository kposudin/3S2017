//
//  main.cpp
//  HW7 (Safe vector)
//
//  Created by Посудин Константин Михайлович on 24.12.17.
//  Copyright © 2017 tin. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

class safe_vector{
private:
    int cap;
    int v_size;
    int* first;
    recursive_mutex lock;
public:
    //constructor and destructor
    safe_vector()
    {
        v_size = 0;
        first = nullptr;
    }
    safe_vector(int c)
    {
        v_size=0;
        cap = c;
        first = new int[c];
    }
    safe_vector (const safe_vector &v_2)
    {
        v_size = v_2.v_size;
        cap = v_2.cap;
        first = new int[cap];
        for (int i=0; i<v_size; i++) {
            first[i] = v_2.first[i];
        }
    }
    safe_vector (safe_vector &&v_2)
    {
        swap(*this, v_2);
    }
    
    
    ~safe_vector()
    {
        if (first!=nullptr) {
            delete[] first;
        }
    }
    
    
    //iterators
    int* begin(){
        return(first);
    }
    int* end(){
        if (first==NULL){
            return NULL;
        }
        return (first+v_size);
    }
    
    
    //vector info
    int size(){
        return (v_size);
    }
    
    bool empty(){
        if (v_size==0){
            return true;
        }
        return false;
    }
    int capacity ()
    {
        return cap;
    }
    
    
    //work with elements
    void push_back(int data)
    {
        lock.lock();
        first[v_size] = data;
        ++v_size;
        lock.unlock();
    }
    
    void clear(){
        first=nullptr;
        v_size=0;
    }
    int pop(int num)
    {
        lock.lock();
        if (num >= v_size) {
            lock.unlock();
            throw out_of_array();
        }
        int result = first[num];
        for (int i = num; i<v_size; i++) {
            first[i] = first[i + 1];
        }
        v_size--;
        lock.unlock();
        return result;
    }
    int pop_back()
    {
        return pop(v_size-1);
    }
    
    void fill (int data)
    {
        lock.lock();
        for (int i = 0; i < cap; i++) {
            first[i] = data;
        }
        v_size = cap;
        lock.unlock();
    }
    
    //capacity work
    void resize (int _cap)
    {
        lock.lock();
        if (_cap == cap) {
            lock.unlock();
            return;
        }
        safe_vector new_v(_cap);
        for (int i = 0; i < _cap && i < v_size; i++) {
            new_v[i] = first[i];
        }
        swap(*this, new_v);
        lock.unlock();
    }
    void reserve (int s_res)
    {
        lock.lock();
        resize(cap+s_res);
        lock.unlock();
    }
    void shrink_to_fit ()
    {
        lock.lock();
        resize(v_size);
        lock.unlock();
    }
    
    
    //get element operators
    int &operator[] (int num)
    {
        lock.lock();
        if (first == nullptr) {
            lock.unlock();
            throw null_vector();
        }
        lock.unlock();
        return first[num];
    }
    int &at (int num)
    {
        lock.lock();
        if (first == nullptr) {
            lock.unlock();
            throw null_vector();
        }
        if (num >= v_size) {
            lock.unlock();
            throw out_of_array();
        }
        lock.unlock();
        return first[num];
    }
    
    //= operators
    safe_vector operator= (const safe_vector &v_2)
    {
        lock.lock();
        safe_vector v2(v_2);
        swap(*this, v2);
        lock.unlock();
        return *this;
    }
    safe_vector operator= (safe_vector &&v_2)
    {
        lock.lock();
        if (first!=nullptr) {
            delete [] first;
        }
        swap(*this, v_2);
        lock.unlock();
        return *this;
    }
    
    
    
    // errors
    class null_vector : std::exception
    {
        const char* what ()
        {
            return "err_null_vector";
        }
    };
    class out_of_array : std::exception
    {
        const char* what ()
        {
            return "err_out_of_array";
        }
    };
    
    void swap (safe_vector &v_1, safe_vector &v_2)
    {
        v_1.lock.lock();
        
        int v_1_size = v_1.v_size;
        int v_1_cap = v_1.cap;
        int* v_1_first = v_1.first;
        
        v_2.lock.lock();
        
        v_1.v_size = v_2.v_size;
        v_1.cap = v_2.cap;
        v_1.first = v_2.first;
        
        v_1.lock.unlock();
        
        v_2.v_size = v_1_size;
        v_2.cap = v_1_cap;
        v_2.first = v_1_first;
        
        v_2.lock.unlock();
    }
    
};


int main(int argc, const char * argv[]) {
    
    return 0;
}
