#pragma once

#include <string>
#include <iostream>

using std::string;

using namespace std;

class Node{
public:
    string data;
    Node *next;
};

class LinkList{
public:
    Node *head=NULL;
    int size;
    int currentNum=0;
    LinkList(){
        head = new Node;
        head->data = "";
        head->next = NULL;
        size=0;
    }
    ~LinkList(){
        delete head;
    }

    void clear(){
        Node *tmp;
        if(this->head==NULL)
            return;
        while(this->head){
            tmp=head->next;
            free(head);
            head=tmp;
        }
        return;
    }



    void InsertLinkList(string data,int n){
        Node *tmp=new Node;
        tmp=this->head;
        if(n!=0)
            for(int i=0;i<n;i++)
                tmp=tmp->next;
        Node *pnew=new Node;
        pnew->data=data;
        pnew->next=tmp->next;
        tmp->next=pnew;

        this->size++;
        currentNum=n++;
     }

    void DeleteLinkList(int start,int end){
        Node *tmp1;
        Node *tmp2;
        tmp1=this->head;
        for(int i=0;i<start;i++)
            tmp1=tmp1->next;
        tmp2=tmp1;
        for(int i=start;i<=end;i++){
            tmp2=tmp1->next;
            tmp1->next=tmp2->next;
            free(tmp2);
            this->size--;
        }

        currentNum=start;
    }

    void ShowLinkList(int start,int end) {
        Node *tmp=new Node;
        tmp=this->head;
        for(int i=0;i<start;i++)
            tmp=tmp->next;
        for(int i=start;i<=end;i++){
            cout<<i<<'\t'<<tmp->data<<endl;
            tmp=tmp->next;
        }
    }

    string moveLine(int n){
        Node *tmp=new Node;
        tmp=this->head;
        for(int i=0;i<n;i++)
            tmp=tmp->next;
        return tmp->data;
    }

    int getbytes(){
        int num=0;
        Node *tmp=this->head->next;
        for(int i=1;i<=this->size;i++){
            // num+=sizeof(tmp->data);
             num+=(tmp->data.size());
             tmp=tmp->next;
             num++;
        }
        return num;
    }
};

class Buffer {
private:
    //int currentLineNum;
    // TODO: add a List here for storing the input lines

public:
    int currentLineNum=0;
    LinkList list;
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) ;

    void showLines(int from, int to) ;

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
