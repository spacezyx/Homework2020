#include "haniotower.h"

using namespace std;
Termio termio;

//AUTO PLAY MODE
void hanoitower::automove(int n,int A=1,int C=3,int B=2)
{
    if(n==1)
    {
        int ad1=-1;
        int ad=-1;
        std::cout << "Auto moving:"<<A<<"->"<<B<< std::endl;
        for(int i=0;i<5;i++)
            if(tower[A-1][i]!=0)
            {
                ad1=i;
                break;
            }
        for(int i=4;i>=0;i--)
            if(tower[B-1][i]==0)
            {
                ad=i;
                swap(tower[A-1][ad1],tower[B-1][ad]);
                termio.Draw(tower);
                break;
            }
    }
    else
    {
        automove(n-1,A,B,C);
        int ad1=-1;
        int ad=-1;
        cout<< "Auto moving:"<<A<<"->"<<B<< std::endl;

        for(int i=0;i<5;i++)
            if(tower[A-1][i]!=0)
            {
                ad1=i;
                break;
            }
        for(int i=4;i>=0;i--)
            if(tower[B-1][i]==0)
            {
                ad=i;
                swap(tower[A-1][ad1],tower[B-1][ad]);
                termio.Draw(tower);
                break;
            }

        automove(n-1,C,A,B);
    }
}

void hanoitower::moveback(mystack op,int tower[3][5]){
    while(!op.empty()){
        int *p=op.pop();
        int j=p[0];
        int i=p[1];
        cout<< "Auto moving:"<<i<<"->"<<j << std::endl;
        //把盘子归位

        int ad=-1;
        int ad1=-1;
        for(int p=0;p<5;p++)
            if(tower[i-1][p]!=0)
            {
                    ad1=p;
                    break;
            }
        for(int p=4;p>=0;p--){
            if(tower[j-1][p]<=tower[i-1][ad1]&&tower[j-1][p]!=0){
                termio.Draw(tower);
                break;
            }

            if(tower[j-1][p]==0)
            {
                ad=p;
                swap(tower[i-1][ad1],tower[j-1][ad]);
                termio.Draw(tower);
                break;
            }
        }
    }
    return;
}

void hanoitower::normalmode(int n,mystack op){
    for(int i=0;i<3;i++)
        for(int j=0;j<5;j++)
            tower[i][j]=0;
    for(int i=0;i<n;i++){
        tower[0][4-i]=n-i;
    }
    termio.Clear();
    termio.Draw(tower);
    int i,j;
    while(true){
        std::cout << "Move a disk. Format: x y" << std::endl;
        cin>>i>>j;
        if(i==0&&j==0){
            termio.ResetBuffer(tower);
             moveback(op,tower);
             automove(n);
             break;
        }

        if(1<=i&&i<=3&&1<=j&&j<=3){
            //判断输入是否合理并把盘子移位
            int ad=-1;
            int ad1=-1;
            for(int p=0;p<5;p++)
                if(tower[i-1][p]!=0)
                {
                    ad1=p;
                    break;
                }
            for(int p=4;p>=0;p--){
                if(tower[j-1][p]<=tower[i-1][ad1]&&tower[j-1][p]!=0){
                    termio.Clear();
                    termio.Draw(tower);
                    break;
                }

                if(tower[j-1][p]==0)
                {
                    ad=p;
                    swap(tower[i-1][ad1],tower[j-1][ad]);
                    termio.Clear();
                    termio.Draw(tower);
                    op.push(i,j);
                    break;
                }
            }
            if(ifwin())
                break;
            }
        else termio.Draw(tower);
        }
    }
