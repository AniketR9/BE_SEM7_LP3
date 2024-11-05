#include<bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr,int low,int high,int& nswaps,int &ncomp){
    int pivot=arr[low];
    int left=low+1;
    int right=high;

    while(true){
        
        while(left<=right && arr[left]<=pivot){
            left++;ncomp++;
        }
        while(left<=right && arr[right]>=pivot){
            right--;ncomp++;
        }

        if(left>right)break;
        swap(arr[left],arr[right]);nswaps++;
    }
    swap(arr[low],arr[right]);nswaps++;
    return right;
}

void dquicksort(vector<int>& arr, int low,int high, int & nswaps,int &ncomp){
    if(low<high){
        int pivot=partition(arr,low,high,nswaps,ncomp);
        dquicksort(arr,low,pivot-1,nswaps,ncomp);
        dquicksort(arr,pivot+1,high,nswaps,ncomp);
    }
}

void rquicksort(vector<int>& arr2,int low,int high,int &swaps,int &comp){
    if(low<high){
        int pivot=low+rand()%(high-low+1);
        swap(arr2[pivot],arr2[low]);
        int ind=partition(arr2,low,high,swaps,comp);
        rquicksort(arr2,low,ind-1,swaps,comp);
        rquicksort(arr2,pivot+1,high,swaps,comp);
    }
}

int main(){
    cout<<"Enter the total no. of elements in the array : ";
    int n;
    cin>>n;
    vector<int>arr;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr.push_back(x);
    }
    vector<int> arr2=arr;

    cout<<"Deterministic QuickSort"<<endl;
    int nswaps=0,ncomp=0;
    dquicksort(arr,0,n-1,nswaps,ncomp);
    cout<<"Sorted Array:"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl<<"Total no. of comparisons : "<<ncomp<<endl;
    cout<<"Total no. of swaps : "<<nswaps<<endl;

    cout<<"Randomized QuickSort"<<endl;
    int swaps=0,comp=0;
    rquicksort(arr2,0,n-1,swaps,comp);
    cout<<"Sorted Array:"<<endl;
    for(int i=0;i<n;i++){
        cout<<arr2[i]<<" ";
    }
    cout<<endl<<"Total no. of comparisons : "<<comp<<endl;
    cout<<"Total no. of swaps : "<<swaps<<endl;
    return 0;
}

// PS D:\ANIKET_BE\Sem 7\PICT_CourseWork_BE_2024-25\LP-IIIprac> ./temp
// Enter the total no. of elements in the array : 10
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10
// Deterministic QuickSort
// Sorted Array:
// 1 2 3 4 5 6 7 8 9 10
// Total no. of comparisons : 45
// Total no. of swaps : 9
// Randomized QuickSort
// Sorted Array:
// 1 2 3 4 5 6 7 8 9 10
// Total no. of comparisons : 24
// Total no. of swaps : 6