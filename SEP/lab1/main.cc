#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Class.h"
#include "Student.h"
#include "studentsupplement.h"

using namespace std;

class AppX {
private:
    vector<Student *> studentVec;
    vector<Class *> classVec;

    void loadFiles();
    void inputScore();
    void printAvgScore();
    void printGpa();

public:
    AppX();
    ~AppX();
    int run();
};

AppX::~AppX()
{
    // You can use the traditional loop, which is more clear.
    for (vector<Class *>::iterator it = classVec.begin();
         it != classVec.end();
         ++it) {
        if (*it) delete (*it);
    }
    // You can use modern and simpler loops only if you know what it is doing.
    for (const auto &s: studentVec) {
        if (s) delete (s);
    }
}

AppX::AppX()
{
    loadFiles();
}

void AppX::loadFiles()
{
    string line;
    size_t pos1, pos2;
    vector<string> bufv;
    Student *st = nullptr;
    string clsname;
    int point;
    int time=0;
    Class *cl = nullptr;
    string stid;

    // Open a file as a input stream.
    ifstream stfile("./Students.txt");

    while (getline(stfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;

        // The bufv vector stores each columnes in the line.
        bufv.clear();
        // Split the line into columes.
        //   pos1: begining the the column.
        //   pos2: end of the column.
        pos1 = 0;
        while (true) {
            pos2 = line.find(';', pos1 + 1);
            if (pos2 == string::npos) { // No more columns.
                // Save the last column (pos1 ~ eol).
                bufv.push_back(line.substr(pos1, string::npos));
                break;
            } else {
                // Save the column (pos1 ~ pos2).
                bufv.push_back(line.substr(pos1, pos2 - pos1));
            }
            pos1 = pos2 + 1;
        }

        // TODO: uncomment next lines after implementing class Undergraduate
        // and Graduate.

        if (bufv[3] == "U")
            st = new Undergraduate(bufv[0], bufv[1], bufv[2]);
        else
            st = new Graduate(bufv[0], bufv[1], bufv[2]);

        studentVec.push_back(st);
    }
    stfile.close();

    // TODO: load data from ./Classes.txt and push objects to the vector.
    // Hint: how is student information read?

    // Open a file as a input stream.
    ifstream clfile("./Classes.txt");

    while (getline(clfile, line)) {
        if (line.empty()) // It's an empty line.
            continue;
        if (line[0] == '#') // It's a comment line.
            continue;


        if(line[0]=='C')
        {
            clsname="";
            int a=6;
            while(line[a])
            {
                clsname.push_back(line[a]);
                a++;
            }
            time++;
        }

        if(line[0]=='P'){
            point=0;
            point=line[7]-48;
            time++;
        }

        if(time==2){
            cl=new Class (clsname,point);
            classVec.push_back(cl);
            time=0;
        }


        if(line[0]=='F'||line[0]=='B'){
             stid="";

             for(int i=0;i<10;i++)
                 stid.push_back(line[i]);

             for (vector<Student *>::iterator it = studentVec.begin();
                  it != studentVec.end();
                  ++it) {
                 if ((*it)->id == stid) {
                     if(st)
                     st = *it;
                     st->addClass(cl);
                     if(cl)
                     cl->addStudent(*st);


                     break;
                 }


         }

        }


    }
    clfile.close();

}

void AppX::inputScore()
{
    // TODO: implement inputScore.
    // Hint: Take a look at printAvgScore().

    string sbuf;
    Class *cl;
    string input;
    Student *st;
    double score;
    bool flag=true;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!\n" << endl;
            continue;
        }

    while (true) {
        cout<<"Please input the student id(or input q to quit):";
        cin>>input;
        if (input == "q")
            break;
        flag=true;

        st=nullptr;
        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             ++it) {
            if ((*it)->id == input) {
                st = *it;
                break;
            }
        }
        if (st == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }

        for(int i=0;i<signed(st->classes.size());i++){

            if((*(st->classes[i])).name==sbuf){
                cout<<(st->toString());
                cout<<"Please input the score:";
                flag=false;
                break;
            }
        }


        if(flag==true){
            cout << "No match student!" << endl;
            continue;
        }


        cin>>score;

           cl->getStudentWrapper(input).setScore(score);

    }
   }
}

void AppX::printAvgScore()
{
    string sbuf;
    Class *cl;
    double avg;

    while (true) {
        cout << "Please input the class name (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        cl = nullptr;
        for (vector<Class *>::iterator it = classVec.begin();
             it != classVec.end();
             ++it) {
            if ((*it)->name == sbuf) {
                cl = *it;
                break;
            }
        }
        if (cl == nullptr) {
            cout << "No match class!" << endl;
            continue;
        }

        avg = cl->getAvgScore();
        cout << "The average score is: " <<fixed <<setprecision(2)<<avg << endl;
    }
}

void AppX::printGpa()
{
    // TODO: implement printGpa.
    // Hint: Take a look at printAvgScore().
    string sbuf;
    Student *st;
    double gpa=0.0;

    while (true) {
        cout << "Please input the student id (or input q to quit): ";
        cin >> sbuf;
        if (sbuf == "q")
            break;

        st = nullptr;
        for (vector<Student *>::iterator it = studentVec.begin();
             it != studentVec.end();
             ++it) {
            if ((*it)->id == sbuf) {
                st = *it;
                break;
            }
        }
        if (st == nullptr) {
            cout << "No match student!" << endl;
            continue;
        }

        gpa = st->getGrade();
        cout<<(st->toString());
        cout << "GPA = " <<fixed <<setprecision(2)<<gpa << endl;
    }
}

int AppX::run()
{
    char cmd;
    while (true) {
        cout << "Command menu:\n"
            << "\ti: Input score\n"
            << "\ta: Compute average score of a class\n"
            << "\tg: Compute grade of a student\n"
            << "\tq: Quit\n"
            << "Please input the command: ";
        cin >> cmd;
        if (cmd == 'i') {
            inputScore();
        } else if (cmd == 'a') {
            printAvgScore();
        } else if (cmd == 'g') {
            printGpa();
        } else if (cmd == 'q') {
            break;
        } else {
            cout << "Invalid command!\n" << endl;
        }
    }
    return 0;
}

int main()
{
    AppX app;
    return app.run();
}
