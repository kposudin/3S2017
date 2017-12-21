#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

void thr_sort(int m, vector<int> *v){
    sort(v->begin(),v->begin()+m);
}

int main() {
    int n,m;
    cout << "Введите параметры массива" << endl;
    cin >> n >> m;
    vector<vector<int>> v;
    vector<int> line;
    
    //FILLING OUR 2D ARRAY WITH RANDOM NUMBERS FROM 0 TO 14
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            line.push_back(rand() % 15);
        }
        v.push_back(line);
        line.clear();
    }
    
    //PRINTING OUR ARRAY
    cout << "BEFORE SORT" << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cout << v[i][j] << " ";
            
        }
        cout << endl;
    }
    
    //SORT V1
    /*for (int i=0; i<n; i++){
        sort(v[i].begin(), v[i].begin()+m);
    }
    */
    //SORT V2
    /*
    for (int i=0; i<n; i++){
        thr_sort(m,&v[i]);
    }
     */
    
    //SORT V3
    vector<thread> a;
    for (int i=0; i<n; i++){
        a.push_back(thread(thr_sort,m,&v[i]));
    }
    for (int i=0; i<n; i++){
        a[i].join();
     }
    
    
    
    
    //PRINTING OUR ARRAY AFTER SORT
    cout << "AFTER SORT" << endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cout << v[i][j] << " ";
            
        }
        cout << endl;
    }
    
    
    
    return 0;
}
