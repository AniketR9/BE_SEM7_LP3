#include<bits/stdc++.h>
using namespace std;


// time complexity = best case O(1) when num is 0/1, worst case O(2^n) because each function call results in two more recursive calls.
// space complexity = best case O(1) when num is 0/1, worst case O(n) as the recursive stack can go as deep as num in the worst case.
int fib(int n){
    if(n<2)return n;

    return fib(n-1)+fib(n-2);
}

// to print recursive result
void recursive(int n){
    for(int i=0;i<n;i++){
        cout<<fib(i)<<" ";
    }
    cout<<endl;
}

// time complexity = best, average and worst case O(n) as it iterates once from 0 to num, performing a constant amount of work in each iteration.
// space complexity = best, average and worst case O(1) as only a few integer variables (a, b, and c) are used, independent of num.
void iterative(int n){
    int a=0,b=1;
    if(n==1){
        cout<<a<<endl;
        return ;
    }
    if(n==2)
    {
        cout<<a<<" "<<b<<endl;
        return;
    }
    cout<<a<<" "<<b<<" ";
    for(int i=2;i<n;i++){
        int c=a+b;
        cout<<c<<" ";
        a=b;
        b=c;
    }
}

int main(){
    int choice;
    int result;

    while(true) {
        int num;
        cout<<"\n\nEnter the no. of fibonacci digits to print: ";
        cin>>num;

        cout<<"\n1. Recursive\n2. Iterative\n3. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;

        switch(choice) {
            case 1: 
                recursive(num);
                break;
            case 2:
                iterative(num);
                break;
            case 3: 
                exit(0);
                break;
        }
    }
    return 0;
}