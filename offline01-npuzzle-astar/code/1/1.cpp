#include<bits/stdc++.h>
using namespace std;

class A {
public:
    int** a;
    int x;
    A(int y){
        x = y;
        a = new int*[x];
        for(int i=0;i<x;i++){
            a[i] = new int[x];
        }

        for(int i=0;i<x;i++){
            for(int j=0;j<x;j++){
                a[i][j] = 0;
            }
        }
    }
    A(const A& b){
        x = b.x;
        a = new int*[x];
        for(int i=0;i<x;i++){
            a[i] = new int[x];
        }

        for(int i=0;i<x;i++){
            for(int j=0;j<x;j++){
                a[i][j] = b.a[i][j];
            }
        }
    }
    void print(){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    ~A(){
        cout<<"Destructor called"<<endl;
        for(int i=0;i<x;i++){
            delete[] a[i];
        }
        delete[] a;
        a = nullptr;
    }
};

int main(){

    A* a= new A(5);
    a->print();
    A* b = new A(*a);
    delete a;
    delete b;
    return 0;
}