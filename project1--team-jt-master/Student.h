#pragma once
#include <string>

using namespace std;

class Student {
public:
	Student(); // default constructor
	Student(const string &cwid); // constructor with parameter
	void addCourseGrade(const string &pcourseName, char pgrade); // add course name and grade to student's record
	double getGPA(); // calculate and return GPA
	void printTranscript(); // print transcript - see Student.cpp for the format
	string getCWID(); // return the CWID of this student
	Student *getNext();	// returns the next pointer
	void setNext(Student *pnext);	// needed for linked list
private:
	Student *next;
	string cwid;
	int nCourses;
	string courseName[50];
	char courseGrade[50];
};