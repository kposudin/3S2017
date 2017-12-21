//
//  main.cpp
//  Depth-first search (threads)
//
//  Created by Посудин Константин Михайлович on 05.10.17.
//  Copyright © 2017 yung blüd. All rights reserved.
//
#include <vector>
#include <iostream>
#include <thread>

using namespace std;
const int n=7;
bool used[n]={0,0,0,0,0,0,0};

/*void DFS(int* GM, int dim, int cur){
 for(int i=cur+1;i<n;i++){
 if (*(GM+n*cur+i)==1 & used[i]==0){
 used[i]=1;
 DFS(GM,n,i);
 }
 }
 cout<<cur+1<<endl;
 }
 int main() {
 int GM[n][n] =
 {
 {0, 1, 1, 0, 0, 0, 0},
 {1, 0, 0, 1, 0, 0, 0},
 {1, 0, 0, 0, 1, 0, 0},
 {0, 1, 0, 0, 0, 1, 1},
 {0, 0, 1, 0, 0, 0, 0},
 {0, 0, 0, 1, 0, 0, 0},
 {0, 0, 0, 1, 0, 0, 0}
 };
 
 thread thr1(DFS, &GM[0][0], n,0);
 thr1.join();
 //DFS(&GM[0][0],n,0);
 
 return 0;
 }*/


void vertex_kids(int*gm,int dim, vector<int> *v_k){
    cout << "VERTEX KIDS:"<< endl;
    for (int i=0; i<dim; i++){
        if (*(gm+i)==1){
            cout << i+1 << endl;
            v_k->push_back(i);
        }
    }
    cout << endl;
}
void DFS(int* GM, int dim, int cur){
    for(int i=cur+1;i<n;i++){
        if (*(GM+n*cur+i)==1 & used[i]==0){
            used[i]=1;
            DFS(GM,n,i);
        }
    }
    cout<<cur+1<<endl;
}
int main() {
    int GM[n][n] =
    {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 1, 1},
        {0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };
    vector<int> v_k;
    vertex_kids(&GM[0][0], n, &v_k);
    cout << "TRY2:"<<endl;
    for (int i=0; i<v_k.size();i++){
        cout<<v_k[i]<<endl;
    }
    cout << endl;
    vector <thread> threads;
    cout << "DFS RESULT:"<<endl;
    
    for (int i=0; i<v_k.size();i++){
        threads.push_back(thread(DFS, &GM[0][0], n,v_k[i]));
    }
    for(auto& thread : threads){
        thread.join();
    }
    cout << "1" << endl;
    
    //thread thr1(DFS, &GM[0][0], n,0);
    //thr1.join();
    //DFS(&GM[0][0],n,0);
    
    return 0;
}

