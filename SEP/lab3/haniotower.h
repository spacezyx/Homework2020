#ifndef HANIOTOWER_H
#define HANIOTOWER_H

#endif // HANIOTOWER_H

#include "termio.h"
#include "mystack.h"
#include <sstream>

using namespace std;

class hanoitower{
public:
    int tower[3][5];
    hanoitower(){
        for(int i=0;i<3;i++)
            for(int j=0;j<5;j++)
                tower[i][j]=0;
    }
void swap(int &a,int &b){
    int tmp=a;
    a=b;
    b=tmp;
}

bool ifwin(){
    bool flag=true;
    int ad=-1;
    for(int i=0;i<5;i++)
        if(tower[0][i]!=0||tower[2][i]!=0)
            flag=false;
    for(int i=0;i<5;i++)
        if(tower[1][i]==1)
        {
            ad=i;
            break;
        }
    for(int i=ad;i<5;i++)
        if(tower[1][i]!=i-ad+1)
            flag=false;
    return flag;
}

//AUTO PLAY MODE
void automove(int,int,int,int);

void moveback(mystack,int tower[3][5]);

void normalmode(int,mystack);

};
