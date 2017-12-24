//
//  main.cpp
//  HW5 (Thread Mergesort)
//
//  Created by Посудин Константин Михайлович on 24.12.17.
//  Copyright © 2017 tin. All rights reserved.
//

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void mergesort (vector<int> &arr, int thr_amount){
    if (arr.size()==2){
        if(arr[0]>arr[1]){
            int t;
            t=arr[0];
            arr[0]=arr[1];
            arr[1]=t;
        }
    }
    if (arr.size()>2){
        vector<int>left_arr, right_arr;
        int left_size;
        left_size=arr.size()/2;
        for (int i=0; i<left_size; i++){
            left_arr.push_back(arr[i]);
        }
        for (int i=left_size; i<arr.size(); i++){
            right_arr.push_back(arr[i]);
        }
    
        if (thr_amount>1){
            thr_amount--;
            --thr_amount;
            thread leftthread([](vector <int> *a, int m = 0){mergesort(*a, m);}, &left_arr, thr_amount/2);
            thread rightthread([](vector <int> *a, int m = 0){mergesort(*a, m);}, &right_arr, thr_amount-(thr_amount/2));
            leftthread.join();
            rightthread.join();
        }
        if (thr_amount==1){
            thr_amount--;
            thread leftthread([](vector <int> *a, int m = 0){mergesort(*a, m);}, &left_arr, 0);
            mergesort(right_arr, 0);
            leftthread.join();
            
        }
        if (thr_amount==0){
            mergesort(left_arr, 0);
            mergesort(right_arr, 0);
        }
        
        //MERGE
        int left = 0;
        int right = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (left < left_arr.size() && (right >= right_arr.size() || left_arr[left] <= right_arr[right])) {
                arr[i] = left_arr[left];
                ++left;
            } else if (right < right_arr.size()) {
                arr[i] = right_arr[right];
                ++right;
            }
        }
    }
    
}


int main(int argc, const char * argv[]) {
    int thr_amount;
    cout << "input threads amount" <<endl;
    cin >> thr_amount;
    vector<int>arr;
    cout << "array before sort:" << endl;
    for (int i=0; i<1000; i++){
        arr.push_back(rand() %15);
        cout << arr[i] <<" ";
    }
    cout << endl;
    mergesort(arr,thr_amount);
    
    
    cout << "array after sort" << endl;
    
    for (int i=0; i<1000; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
