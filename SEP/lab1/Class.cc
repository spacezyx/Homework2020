#include "Class.h"
#include <string>
#include "Student.h"


void Class::addStudent(Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId)
            return *it;
    }
    throw "No matching student!\n";
}

double Class::getAvgScore()
{
    double sum=0;
    double avg=0;
    for(int i=0;i<students.size();i++){
        sum+=students[i].getScore();
    }

    avg=sum/(students.size());
    return avg;
}
