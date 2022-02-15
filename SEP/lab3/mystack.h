#ifndef MYSTACK_H
#define MYSTACK_H

#endif // MYSTACK_H

#include <iostream>

using namespace std;

class mystack
{
public:
    int count;
    int capacity;
    int array[1000][2];


    mystack(){
        count=0;
        capacity=1000;
        for(int i=0;i<1000;i++)
            for(int j=0;j<2;j++)
                array[i][j]=0;
        }

    int* top(){
        if(count<=0)
            return NULL;
        else return array[count-1];
    }

    void push(int a,int b){
        array[count][0]=a;
        array[count][1]=b;
        count++;
    }

    int* pop(){
        if(count<=0)
            return NULL;
        else return array[--count];
    }

    bool empty(){
        return count==0?true:false;
    }

};
