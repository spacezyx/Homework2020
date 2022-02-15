#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "lexicon.h"

using namespace std;

int n=0;
vector <string> playerList;
vector <string> machineList;
vector <string> removeList;
bool tmp;

//函数声明
void machineRound(Lexicon lex,vector <string> playerList,string* board);
void output(string* board);

bool exist(vector <string> &machineList,string input){
    for(int i=0;i<input.size();i++)
        input[i]=toupper(input[i]);

    tmp=find(removeList.begin(),removeList.end(),input)!=removeList.end();
     if(tmp)
         return true;

    vector<string>::iterator iter=find(machineList.begin(),machineList.end(),input);
    bool flag=(iter!=machineList.end());
    if(flag)
        machineList.erase(iter);
    return flag;
}

//递归找单词
void findWord(string* board,Lexicon &lex,int i,int j,string now,vector <string> &machineList){
    char temp = board[i][j];
    string current="";
    current=now;
    current.push_back(temp);

    if(!lex.containsPrefix(current)){
        return;
    }
    if(lex.contains(current)){
        machineList.push_back(current);
        //return;
    }
    for(int dx=-1;dx<=1;dx++){
        for(int dy=-1;dy<=1;dy++){
            if(i+dx>=0&&i+dx<n&&j+dy>=0&&j+dy<n&&board[i+dx][j+dy]!='\0'&&!(dx==0&&dy==0)){
                board[i][j]='\0';
                findWord(board,lex,i+dx,j+dy,current,machineList);
                board[i][j]=temp;
            }
        }
    }
}

//计算机回合
void machineRound(Lexicon lex,string* board,vector <string> &machineList){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            string now="";
            findWord(board,lex,i,j,now,machineList);
        }
    }
}

//输出棋盘
void output(string* board){
    for(int i=0;i<n;i++){
        cout<<board[i]<<endl;
    }
}


int main()
{
    Lexicon lex("./EnglishWords.txt");
    cin>>n;

    string board[n];

    //输入棋盘
    for(int i=0;i<n;i++)
        cin>>board[i];


    machineRound(lex,board,machineList);
    string input="";
    int score=0;
    int computerScore=0;

    sort(machineList.begin(),machineList.end());
    machineList.erase(unique(machineList.begin(),machineList.end()),machineList.end());
    while(input!="???"){
        output(board);
        cout<<"Your Score: "<<score<<endl;
        cout<<"Your Words: ";
        for(int i=0;i<playerList.size();i++)
            cout<<playerList[i]<<" ";
        cout<<endl;

        cin>>input;
        if(input=="???")
            break;
        //判断违规情况
        if(input.size()<4){
            cout<<input<<" is too short."<<endl;
            continue;
        }
        if(!lex.contains(input)){
            cout<<input<<" is not a word."<<endl;
            continue;
        }
        if(!exist(machineList,input)){
            cout<<input<<" is not on board."<<endl;
            continue;
        }
        if(tmp){
            cout<<input<<" is already found."<<endl;
            continue;
        }
        else{
            score+=input.size()-3;
            for(int i=0;i<input.size();i++)
                 input[i]=tolower(input[i]);
            playerList.push_back(input);
            for(int i=0;i<input.size();i++)
                 input[i]=toupper(input[i]);
            removeList.push_back(input);
        }
    }

    for(int i=machineList.size()-1;i>=0;i--){
        if(machineList[i].size()>=4)
            computerScore+=machineList[i].size()-3;
        if(machineList[i].size()<4)
            machineList.erase(machineList.begin()+i);
    }

    //computerScore=computerScore-score;
    cout<<"Computer Score: "<<computerScore<<endl;

    cout<<"Computer Words: ";
    for(int i=0;i<machineList.size();i++)
        cout<<machineList[i]<<" ";

    return 0;
}
