#include<bits/stdc++.h>
using namespace std;

class A {
public:
    int* p;
    A(int x){
        p = new int(x);
    }
    A(const A& a){
        p = new int(*a.p);
    }
    void setP(int x){
        *p = x;
    }
    A& operator=(const A& a){
        if(this == &a){
            return *this;
        }
        delete p;
        p = new int(*a.p);
        return *this;
    }
    ~A(){
        cout<<"Destructor called"<<endl;
        delete p;
        p = nullptr;
    }
};

int main(){
    A* a = new A(10);
    A* b = new A(*a);
    a->setP(20);
    cout<<*b->p<<endl;
    delete a;
    delete b;
    return 0;
}