#ifndef STUDENT_H_
#define STUDENT_H_



#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Class;



enum Degree {
    undergraduate,
    graduate
};


class Student {
    // TODO: implement class Student.
public:
    const string id;
    const string name;
    const string year;
   vector<Class*> classes ;
   enum Degree degree;

   Student () {}
   Student (string id,string name,string year):id(id),name(name),year(year) {}

    string toString() const;
    virtual double getGrade()=0;
    void addClass (Class*c);
};

// TODO: implement class Graduate.

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const string id;
    // TODO: fix error
    StudentWrapper(const string &id, const Student &student) :student(student),id(id){
    }

    void setScore(double score)
    {
        if (score >= 0 && score <= 100)
            this->score = score;
        else
            cout<<"Wrong Score!\n";

    }

    double getScore() const
    {
        return this->score;
    }

    string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
