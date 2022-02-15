#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"
#include <vector>

using namespace std;

std::string Student::toString() const
{


    // TODO: uncomment the following code after implementing class Student.
    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
    return "";
}

// TODO: implement functions which are declared in Student.h.

void Student::addClass (Class*c)
{
    classes.push_back(c);
}

