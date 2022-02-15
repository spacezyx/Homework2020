#pragma once
/* some code from Libconio 1.0 (C) 2004 FSL A.C. */

#ifdef _WIN32
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static void clrscr()
{
    system("cls");
}
#else
#include <termios.h>
#include <stdio.h>
#define ESC 033 /* Escape char */

static int getch()
{
    struct termios t;
    int c;

    tcgetattr(0, &t);
    t.c_lflag &= ~ECHO + ~ICANON;
    tcsetattr(0, TCSANOW, &t);
    fflush(stdout);
    c = getchar();
    t.c_lflag |= ICANON + ECHO;
    tcsetattr(0, TCSANOW, &t);
    return c;
}

static void clrscr()
{
    printf("%c[2J", ESC);
    printf("%c[%d;%dH", ESC, 0, 0);
}
#endif

#include <iostream>
#include <cstring>
using namespace std;

class Termio
{
public:
    // donot change the width and height
    static const int CANVAS_WIDTH = 41;
    static const int CANVAS_HEIGHT = 11;
    static char buffer[CANVAS_HEIGHT][CANVAS_WIDTH + 1];
    int tmp[3][5];

    static char GetChar() {
        return getch();
    }

    static void Clear() {
        clrscr();
    }

    static void Draw(int tower[3][5]) {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
        {
            for(int j = 0; j < CANVAS_WIDTH; j++)
            {
                 buffer[i][j]=' ';
            }
        }

        for (int i = 0; i < 11; i++) {
            buffer[i][5] = '|';
            buffer[i][20] = '|';
            buffer[i][35] = '|';
        }

        for(int i=0;i<3;i++)
            for(int j=0;j<5;j++){
                if(tower[i][j]!=0){
                    int num=2*j+1;
                    for(int p=15*i+5-tower[i][j];p<tower[i][j]+15*i+6;p++)
                        buffer[num][p] = '*';
                }
        }

        for (int i = 0; i < 5; i++) {
            buffer[10][i] = '-';
        }
        for (int i = 6; i < 20; i++) {
            buffer[10][i] = '-';
        }
        for (int i = 21; i < 35; i++) {
            buffer[10][i] = '-';
        }
        for (int i = 36; i < 41; i++) {
            buffer[10][i] = '-';
        }
        for (int i = 0; i < CANVAS_HEIGHT; i++)
        {
            for(int j = 0; j < CANVAS_WIDTH; j++)
            {
                cout << buffer[i][j];
            }
            cout<<endl;

        }
    }

     void ResetBuffer(int tower[3][5]) {
        for (int i = 0; i < CANVAS_HEIGHT; i++)
            memset(buffer[i], ' ', CANVAS_WIDTH);
        for(int i=0;i<3;i++)
            for(int j=0;j<5;j++)
                tmp[i][j]=tower[i][j];
    }
};
