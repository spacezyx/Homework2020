#include <fstream>
#include <iostream>
#include "Buffer.h"
#include <string>

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {}

Buffer::~Buffer() {}

void Buffer::writeToFile(const string &filename) const {
    ofstream out(filename);
    Node *tmp=list.head->next;
    for(int i=1;i<=list.size;i++){
         out<<tmp->data;
         tmp=tmp->next;
    }
    out.close();
}

void Buffer::showLines(int from, int to)  {
    list.ShowLinkList(from,to);
    currentLineNum=to;
}

void Buffer::deleteLines(int from, int to){
    list.DeleteLinkList(from-1,to-1);
    currentLineNum=from;
}

void Buffer::insertLine(const string &text){
    if(currentLineNum==0)
        currentLineNum=1;
    list.InsertLinkList(text,currentLineNum-1);
    //currentLineNum++;
}

void Buffer::appendLine(const string &text){
    list.InsertLinkList(text,currentLineNum);
    currentLineNum++;
}

string result="";

const string &Buffer::moveToLine(int idx)  {
    if(idx>list.size){
        result="? Line number out of range";
        return result;
    }

    else{
        result=list.moveLine(idx);
        currentLineNum=idx;
        return result;
    }

}
