#include "termio.h"
//#include "mystack.h"
#include "haniotower.h"
#include <sstream>

mystack op;
// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

int main() {
    hanoitower hanoi;
    string input;
    int n=0;
    while(true){
        std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
        cin>>input;
        stringstream ss;
        ss<<input;
        ss>>n;
        if(input=="Q")
            break;

        if(n>=1&&n<=5){
            hanoi.normalmode(n,op);
        }

        else continue;
        bool flag=hanoi.ifwin();
        if(flag)
            std::cout << "Congratulations! You win!" << std::endl;
    }
    return 0;
}
