//
//  main.cpp
//  HW6 (Atomic template)
//
//  Created by Посудин Константин Михайлович on 24.12.17.
//  Copyright © 2017 tin. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <vector>

using namespace std;

template <class T>
class atomic{
private:
    mutex lock;
    T data;
public:
    atomic(){
        data=T();
    }
    constexpr atomic( T desired ){
        data=desired;
    }
    
    atomic(const atomic <T> &at2)
    {
        data = at2.data;
    }
    
    atomic &operator= (const atomic <T> &at2)
    {
        lock.lock();
        data = at2.data;
        lock.unlock();
        return *this;
    }
    atomic &operator= (atomic <T> &&at2)
    {
        lock.lock();
        data = at2.data;
        lock.unlock();
        return *this;
    }
    
    bool is_lock_free (){
        if(!lock.try_lock()){
            return false;
        }
        return true;
    }
    
    void store(T d)
    {
        lock.lock();
        data = d;
        lock.unlock();
    }
    
    T load ()
    {
        lock.lock();
        T result = data;
        lock.unlock();
        return result;
    }
    
    operator T()
    {
        lock.lock();
        T result = data;
        lock.unlock();
        return result;
    }
   
    T exchange(T d)
    {
        lock.lock();
        T result = data;
        data = d;
        lock.unlock();
        return result;
    }
    
    atomic<T> &operator++()
    {
        lock.lock();
        data++;
        lock.unlock();
        return *this;
    }
    atomic<T> &operator++(int)
    {
        lock.lock();
        atomic<T> result(++data);
        lock.unlock();
        return *this;
    }
    
    atomic<T> &operator--()
    {
        lock.lock();
        data--;
        lock.unlock();
        return *this;
    }
    atomic<T> &operator--(int)
    {
        lock.lock();
        atomic<T> result(--data);
        lock.unlock();
        return *this;
    }
    
    
    ~atomic(){
        
    }
};

int main(int argc, const char * argv[]) {
    return 0;
}
