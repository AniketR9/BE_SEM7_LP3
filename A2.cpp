#include<bits/stdc++.h>
using namespace std;

struct HuffmanNode{
    char data;
    int frequency;
    HuffmanNode *left,*right;

    HuffmanNode(char d,int f){
        left=right=NULL;
        data=d;
        frequency=f;
    }
};

struct Compare{
    bool operator()(HuffmanNode* a,HuffmanNode* b){
        return a->frequency>b->frequency;
    }
};

void printCodes(HuffmanNode* root,string code,unordered_map<char,string>& HuffmanCodes){
    if(!root)return;

    if(!root->left & !root->right){
        HuffmanCodes[root->data]=code;
        cout<<root->data<<" : "<<code<<endl;
        return;
    }

    printCodes(root->left,code+"0",HuffmanCodes);
    printCodes(root->right,code+"1",HuffmanCodes);
}

void buildHuffmanTree(string text){
    unordered_map<char,int> freq;
    for(char c:text){
        freq[c]++;
    }
    priority_queue<HuffmanNode*,vector<HuffmanNode*>,Compare>pq;
    for(auto pairs:freq){
        pq.push(new HuffmanNode(pairs.first,pairs.second));
    }

    while(pq.size()>1){
        HuffmanNode* left=pq.top();
        pq.pop();
        HuffmanNode* right=pq.top();
        pq.pop();

        HuffmanNode* newNode=new HuffmanNode('\0',left->frequency+right->frequency);
        newNode->left=left;
        newNode->right=right;

        pq.push(newNode);
    }

    HuffmanNode* root=pq.top();

    unordered_map<char,string>HuffmanCodes;
    cout<<"Character : Huffman Code"<<endl;
    printCodes(root,"",HuffmanCodes); 
    cout<<"Encoded String : ";
    for(char x:text){
        cout<<HuffmanCodes[x];
    }
}

int main(){
    string text;
    cout<<"Enter the text to be encoded : ";
    getline(cin,text);
    buildHuffmanTree(text);

    return 0; 
}