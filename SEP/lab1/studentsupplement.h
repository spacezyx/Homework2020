#ifndef STUDENTSUPPLEMENT_H
#define STUDENTSUPPLEMENT_H

#endif // STUDENTSUPPLEMENT_H
#include "Student.h"
#include <string>
#include <vector>
#include "Class.h"
using namespace std;

Class*_other;

// TODO: implement class Graduate.
class Graduate : public Student {
public:
    Graduate(string id,string name,string year,Degree degree=graduate):Student (id,name,year)
        {}


    double getGrade() {
        double gpa=0;
        double score=0;
        int point=0;
        int a=0;
        int point_sum=0;
        double gpa_sum=0;
        double result=0;

        for(int i=0;i<classes.size();i++){
            score=0;
            point=0;
            gpa=0;
            _other=classes[i];
            point=_other->point;
            score=classes[i]->getStudentWrapper(id).getScore();
            point_sum=point_sum+point;
            a=score/10;
            switch(a){
                case 10:{gpa=4.0;break;}
                case 9: {gpa=4.0;break;}
                case 8: {gpa=3.5;break;}
                case 7: {gpa=3.0;break;}
                case 6: {gpa=2.5;break;}
                default:{gpa=2.0;}
            }
            gpa_sum+=point*gpa;
        }


        result=gpa_sum/point_sum;
        return result;
    }

};



// TODO: implement class Undergraduate.
class Undergraduate : public Student {
public:

     Undergraduate(string id,string name,string year,Degree degree=undergraduate):Student (id,name,year)
        {}

     double getGrade() {
         double score=0.0;
         int point=0;
         int point_sum=0;
         double gpa_sum=0.0;
         double result=0.0;
         for(int i=0;i<classes.size();i++){
             score=0;
             point=0;
             _other=classes[i];
             point=_other->point;
             point_sum+=point;
             score=classes[i]->getStudentWrapper(id).getScore();
             gpa_sum+=(score/20.0)*point;
         }
             result=gpa_sum/point_sum;
         return result;
     }

};
