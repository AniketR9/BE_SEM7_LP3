#include<bits/stdc++.h>
using namespace std;

struct Item{
    int weight;
    int value;
    int idx;
    double ratio;
    Item(int w, int v, int i){
        weight=w;
        value=v;
        idx=i;
        ratio=static_cast<double>(v)/w;
    }
};

struct Node{
    int level;
    int weight;
    int value;
    double bound;
    vector<int> items;
    Node(int l,int w,int v){
        level=l;
        weight=w;
        value=v;
        bound=0.0;
    }
};

struct Compare{
    bool operator()(Node* a,Node* b)const{
        return a->bound<b->bound;
    }
};

double calculateBound(Node* node,int maxCapacity,vector<Item> items){
    if(node->weight>maxCapacity)return 0;

    int currWeight=node->weight;
    double valBound=node->value;
    int j=node->level+1;

    while(j<items.size() && currWeight+items[j].weight<=maxCapacity){
        currWeight+=items[j].weight;
        valBound+=items[j].value;
        j++;
    }

    if(j<items.size()){
        valBound+=(maxCapacity-currWeight)* items[j].ratio;
    }

    return valBound;
}

void knapsackDP(int W,vector<Item> items){
    int n=items.size();
    vector<vector<int>>dp(n+1,vector<int>(W+1,0));

    for(int i=1;i<=n;i++){
        for(int w=1;w<=W;w++){
            int notTaken=dp[i-1][w];
            int taken=INT_MIN;
            if(items[i-1].weight<=w) taken=dp[i-1][w-items[i-1].weight]+items[i-1].value;
            dp[i][w]=max(taken,notTaken);
        }
    }

    vector<int>it(n,0);
    int i=n,j=W;
    while(i>0 && j>0){
        if(dp[i][j]!=dp[i-1][j]){
            it[i-1]=1;
            j-=items[i-1].weight;
        }
        i--;
    }
    cout<<"Max Profit obtained : "<<dp[n][W]<<endl;
    cout<<"Items selected : ";
    for(int i=0;i<n;i++){
        if(it[i]==1){
            cout<<i+1<<" ";
        }
    }
    cout<<endl;
}

void knapsackBB(int maxCapacity,vector<Item>& items){
    int n=items.size();
    sort(items.begin(),items.end(),[](const Item& a,const Item& b){
        return a.ratio>b.ratio;
    });
    priority_queue<Node*,vector<Node*>,Compare>pq;
    Node* root=new Node(-1,0,0);
    root->bound=calculateBound(root,maxCapacity,items);
    pq.push(root);
    int maxValue=0;
    vector<int> bestItems;

    while(!pq.empty()){
        Node* curr=pq.top();
        pq.pop();

        if(curr->bound<=maxValue){
            delete curr;
            continue;
        }

        int level=curr->level+1;
        if(level>=n){
            delete curr;
            continue;
        }

        int newWeight=curr->weight+items[level].weight;
        if(newWeight<=maxCapacity){
            Node* includeNode=new Node(level,newWeight,curr->value+items[level].value);
            includeNode->items=curr->items;
            includeNode->items.push_back(items[level].idx);
            includeNode->bound=calculateBound(includeNode,maxCapacity,items);

            if(includeNode->value> maxValue){
                maxValue=includeNode->value;
                bestItems=includeNode->items;
            }

            if(includeNode->bound>maxValue){
                pq.push(includeNode);
            }else{
                delete includeNode;
            }
        }

        Node* excludeNode=new Node(level,curr->weight,curr->value);
        excludeNode->items=curr->items;
        excludeNode->bound=calculateBound(excludeNode,maxCapacity,items);
        if(excludeNode->bound>maxValue){
                pq.push(excludeNode);
        }else{
                delete excludeNode;
        }
        delete curr;
    }

    cout<<"MaxProfit obtained : "<<maxValue;
    cout<<"\nItems selected :";
    sort(bestItems.begin(),bestItems.end());
    for(auto x:bestItems){
        cout<<x+1<<" ";
    }
    cout<<endl;
}

int main(){
    cout<<"Enter the no. of items : ";
    int n,W;
    cin>>n;
    cout<<"Enter the knapsack capacity : ";
    cin>>W;
    vector<Item> items;
    for(int i=0;i<n;i++){
        int w,v;
        cout<<"Enter the weight of item "<<i+1<<" : ";
        cin>>w;
        cout<<"Enter the value of item "<<i+1<<" : ";
        cin>>v;
        items.push_back(Item(w,v,i));
    }
    knapsackDP(W,items);
    knapsackBB(W,items);
    return 0;
}