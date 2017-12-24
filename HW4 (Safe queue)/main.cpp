//
//  main.cpp
//  HW4 (Safe queue)
//
//  Created by Посудин Константин Михайлович on 24.12.17.
//  Copyright © 2017 tin. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std;

class safe_queue {
private:
    mutex lock;
    queue<int> data;
public:
    safe_queue(){
    }
    safe_queue(int n){
        lock.lock();
        data.push(n);
        lock.unlock();
    }
    void push(int n){
        lock.lock();
        data.push(n);
        lock.unlock();
    }
    void pop(){
        
        if (!data.empty()){
            cout << data.front() << endl;
            data.pop();
        }
    }
    void flprint(){
        if (!data.empty()){
            cout << data.back() << endl << data.front() << endl;
        }
    }
    int back(){
        return data.back();
    }
        
    
    
};

void thread_queue_push (safe_queue &queue){
    queue.push(rand() %15);
    cout << queue.back();
}

int main(int argc, const char * argv[]) {
    
    safe_queue q1;
    
    thread a [10];
    for (int i=0; i<10; i++){
        a[i]=thread(thread_queue_push, &q1);
    }
    for (int i=0; i<10; i++){
        a[i].join();
    }
    
    return 0;
}
