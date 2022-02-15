#include <iostream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode{
    unsigned long val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    TreeNode() : val(0), left(nullptr),right(nullptr),parent(nullptr) {}
    TreeNode(unsigned long x) : val(x), left(nullptr),right(nullptr),parent(nullptr) {}
    TreeNode(unsigned long x,TreeNode* parent) : val(x), left(nullptr),right(nullptr),parent(parent) {}
    TreeNode(unsigned long x, TreeNode *left,TreeNode*right,TreeNode* parent) : val(x), left(left),right(right),parent(parent) {}
};

unsigned long hash64shift(unsigned long key){
    key = (~key) + (key << 21); // key = (key << 21) - key - 1;
    key = key ^ (key >> 24);
    key = (key + (key << 3)) + (key << 8); // key * 265
    key = key ^ (key >> 14);
    key = (key + (key << 2)) + (key << 4); // key * 21
    key = key ^ (key >> 28);
    key = key + (key << 31);
    return key;
}

class Merkle_Tree{
public:
    TreeNode* Root;
    vector<TreeNode*> hashlist;

vector<unsigned long> getProof(unsigned long hash_value){

    int size=hashlist.size();
    TreeNode* tmp=nullptr;
    TreeNode* par=nullptr;
    int i=0;
    vector<unsigned long> result;
    if(hash_value==0)
        return result;
    if(size==0)
        return result;
    while(i<size){
        if(hashlist[i]->val==hash_value){
            tmp=hashlist[i];
            if(!tmp->parent)
                return result;
            else
                par=tmp->parent;
            if(tmp==par->right)
                result.push_back(par->left->val);
            else if(tmp==par->left)
                result.push_back(par->right->val);
            break;
        }
        else
            i++;
    }
    if(i==size){
        return result;
    }
    while(par&&par!=Root){
        tmp=par;
        par=par->parent;
        if(tmp==par->right&&par->left)
            result.push_back(par->left->val);
        else if(tmp==par->left&&par->right)
            result.push_back(par->right->val);
    }
    //result.push_back(Root->val);
    return result;
}



Merkle_Tree(){
    Root=new TreeNode;
}

void destory(TreeNode* root){
    if(root!=nullptr&&(root->left||root->right)){
        destory(root->left);
        destory(root->right);
        delete root;
    }
}

~Merkle_Tree(){
    destory(Root);
    hashlist.clear();
}

Merkle_Tree(vector<unsigned long> input){
    int size=input.size();
    queue<TreeNode*> tmpque;
    for(int i=0;i<size;i++){
        TreeNode* tmpnode=new TreeNode(input[i]);
        hashlist.push_back(tmpnode);
        tmpque.push(tmpnode);
    }
    if(tmpque.size()==0){
        Root=new TreeNode;
        return;
    }
    if(tmpque.size()==1){
        TreeNode* p=new TreeNode;
        TreeNode* t=tmpque.front();
        tmpque.pop();
        p->left=t;
        t->parent=p;
        Root=p;
        p->val=t->val;
        p->right=new TreeNode;
        return;
    }

    while(tmpque.size()>1){
        int vecsize=tmpque.size();
        for(int i=0;i<vecsize;i+=2){
            TreeNode* p=new TreeNode;
            TreeNode* l=tmpque.front();
            tmpque.pop();
            p->left=l;
            l->parent=p;
            if(i<(vecsize-1)){
                TreeNode* r=tmpque.front();
                tmpque.pop();
                p->right=r;
                r->parent=p;
            }
            else{
                p->right=new TreeNode;
            }
            if(p->right->val!=0){
                unsigned long tmpval=p->left->val+p->right->val;
                unsigned long tmpvalforleaf=hash64shift(tmpval);
                p->val=tmpvalforleaf;
            }

            else if(p->right->val==0)
                p->val=p->left->val;
            tmpque.push(p);
        }
    }
    Root=tmpque.front();
    tmpque.pop();
}

void addTransaction(unsigned long key){
    destory(Root);
    TreeNode* tmpnode=new TreeNode(key);
    hashlist.push_back(tmpnode);
    int size=hashlist.size();
    queue<TreeNode*> tmpque;
    for(int i=0;i<size;i++){
        tmpque.push(hashlist[i]);
    }

    if(tmpque.size()==0){
        Root=new TreeNode;
        return;
    }

    if(tmpque.size()==1){
        TreeNode* p=new TreeNode;
        TreeNode* t=tmpque.front();
        tmpque.pop();
        p->left=t;
        t->parent=p;
        p->val=t->val;
        p->right=new TreeNode;
        Root=p;
        return;
    }

    while(tmpque.size()>1){
        int vecsize=tmpque.size();
        for(int i=0;i<vecsize;i+=2){
            TreeNode* p=new TreeNode;
            TreeNode* l=tmpque.front();
            p->left=l;
            l->parent=p;
            tmpque.pop();
            if(i<(vecsize-1)){
                TreeNode* r=tmpque.front();
                p->right=tmpque.front();
                r->parent=p;
                tmpque.pop();
            }
            else
                p->right=new TreeNode;
            if(p->right->val!=0){
                unsigned long tmpval=p->left->val+p->right->val;
                tmpval=hash64shift(tmpval);
                p->val=tmpval;
            }
            else if(p->right->val==0)
                p->val=p->left->val;
            tmpque.push(p);
        }
    }
    Root=tmpque.front();
    tmpque.pop();
}

unsigned long getRootHash(){
    return Root->val;
}

};
