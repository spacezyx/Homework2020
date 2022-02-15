#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>
#include <algorithm>
#define INF 2000

using namespace std;

class Shortest{
public:
  int num;
  vector<vector<int>> array;
  vector<vector<int>> path;

  //初始化
  Shortest(int num,vector<vector<int>> side):array(num, vector<int>(num,INF)),path(num, vector<int>(num)){
    this->num=num;

    for(int i=0;i<num;i++)
      array[i][i]=0;

    for(int i=0;i<num;i++)
      for(int j=0;j<num;j++)
        path[i][j]=j;

    int start=0;
    int end=0;
    int weight=0;
    int size=side.size();

    for(int i=0;i<size;i++){
        start=side[i][0];
        end=side[i][1];
        weight=side[i][2];
        array[start][end] = weight;
        array[end][start] = weight;
      }
  }

  //Floyd
  void Floyd(){
    for(int u=0; u<num;u++)
      for(int v=0;v<num;v++)
        for(int w=0;w<num;w++)
          if(array[v][u]+array[u][w]<array[v][w]){				//比较两种方案，取更小的
              array[v][w]=array[v][u]+array[u][w];
              path[v][w]=path[v][u];									//更新Path矩阵
            }
  }

  void Floyd_4(){
    for(int u=0; u<num;u++)
      for(int v=0;v<num;v++)
        for(int w=v;w<num;w++)
          if(array[v][u]+array[u][w]<array[v][w]){				//比较两种方案，取更小的
              array[v][w]=array[v][u]+array[u][w];
              array[w][v]=array[v][w];
              path[v][w]=path[v][u];									//更新Path矩阵
            }
  }


  //亲近中心度
  int closeindex;
  vector<int> shortlen;

  double Closeness(){
    closeindex=0;
    double closeness=1000000;
    for(int i=0;i<num;i++){
        int tmp=accumulate(array[i].begin(),array[i].end(),0);
        if(tmp<closeness){
            closeness=tmp;
            closeindex=i;
          }
      }
    double result=0;
    result=(num-1)/closeness;
    return result;
  }

  //中介中心度
  int betweenness=0;
  int betweennessidex;
  int Betweenness(){
    int temp=0;
    vector<int> tmp(num);
    for(int i=0;i<num;i++)
      tmp[i]=0;
    for(int i=0;i<num;i++){
        for(int j=i+1;j<num;j++){
            if(array[i][j]>0&&path[i][j]!=j){
                int m=path[i][j];
                tmp[m]++;
              }
            temp=path[i][j];
            while(temp!=j){
                temp=path[temp][j];
                if(temp!=j)
                  tmp[temp]++;
              }
          }
      }
    betweennessidex=num-1;
    betweenness=tmp[num-1];
    for(int i=num-1;i>=0;i--){
        if(tmp[i]>=betweenness){
            betweenness=tmp[i];
            betweennessidex=i;
          }
      }
    return (betweenness);
  }

};

int main(int argc,char *argv[])
{
  ifstream infile;
      infile.open(argv[1]);
  //    infile.open("../test.txt");
//  infile.open("../1.txt");

  int num=0;
  infile>>num;

  //读文件
  vector<vector<int>> side;
  string line;
  while(getline(infile,line)){
      if(line!=""){
          stringstream ss(line);
          string tmp;
          vector<int> v;
          while(getline(ss,tmp,',')){
              v.push_back(stoi(tmp));
            }
          side.push_back(v);
        }
    }
  infile.close();   //关闭文件


  auto new_end = unique(side.begin(), side.end());//"删除"相邻的重复元素
  side.erase(new_end, side.end());//删除(真正的删除)重复的元素

  Shortest input=Shortest(num,side);

  vector<int> degree;
  degree.resize(num);
  for(int i=0;i<num;i++){
      degree[i]=0;
    }
  int s=side.size();
  for(int i=0;i<s;i++){
      int i1=side[i][0];
      int i2=side[i][1];
      degree[i1]++;
      degree[i2]++;
    }
  int high=degree[0];
  int result1=0;
  for(int i=1;i<num;i++){
      if(high<degree[i]){
          high=degree[i];
          result1=i;
        }
    }
  cout<<result1<<" "<<high<<endl;

  if(num<500){
      input.Floyd();
      double result2=input.Closeness();
      int closeindex=input.closeindex;
      cout<<closeindex<<" "<<result2<<endl;

      int result3=input.Betweenness();
      int betweennessindex=input.betweennessidex;
      cout<<betweennessindex<<" "<<result3<<endl;
    }
  else{
      input.Floyd_4();
      double result2=input.Closeness();
      int closeindex=input.closeindex;
      cout<<closeindex<<" "<<result2<<endl;

      int result3=input.Betweenness();
      int betweennessindex=input.betweennessidex;
      cout<<betweennessindex<<" "<<result3<<endl;
    }
  return 0;
}
