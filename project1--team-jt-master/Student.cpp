#include "Student.h"

#include <iostream>

Student::Student() {
	cwid = " "; // Initialize string cwid as blank
	nCourses = 0; // Set int nCourses to 0
	next = nullptr;	// Set next to nullptr
}

Student::Student(const string &pcwid) {
	cwid = pcwid; // Initialize student name
	nCourses = 0; // Set int nCourses to 0
	next = nullptr;	// Set next to nullptr
}

string Student::getCWID() {
	return cwid;
}

void Student::addCourseGrade (const string &pcourseName, char pgrade) {
	// Allocate new memory for the courseName and courseGrade
	courseName[nCourses] = pcourseName;
	courseGrade[nCourses] = pgrade;
	nCourses++; // Increment the number of courses by 1
}

double Student::getGPA() {
	// Calculate the GPA by doing the following:
	// 1. Perform a switch statement to check grade by number of credits worth.
	// 2. Assign the credits value by the numeric grade.
	// 3. Add all the numbers to get the total sum.
	// 4. Divide the sum by number of classes taken to get the GPA.
	double gpa;
	double sum = 0.0;
	char grade = '0';
	double credits = 0.0;

	for (int i = 0; i < nCourses; i++)
	{
		grade = courseGrade[i];

		switch (grade)
		{
		case 'A':
		case 'a':
			credits = 4.0;
			break;
		case 'B':
		case 'b':
			credits = 3.0;
			break;
		case 'C':
		case 'c':
			credits = 2.0;
			break;
		case 'D':
		case 'd':
			credits = 1.0;
			break;
		case 'F':
		case 'f':
			credits = 0.0;
			break;
		default:
			credits = 0.0;
		}
		sum = sum + credits;
	}

	gpa = sum / nCourses;
	return gpa;
}

// print transcript in this (sample) format:
// TRANSCRIPT FOR CWID=279750343
// CS 121		C
// CS 253		B
// CS 131		B
// GPA = 2.6667
void Student::printTranscript() {
	// Display the student's transcript containing the
	// courses taken, the grade, and the GPA.
	cout << "TRANSCRIPT FOR CWID=" << cwid;
	for (int j = 0; j < nCourses; j++)
	{
		cout << courseName[j] << "   " << courseGrade[j] << endl;
	}
	cout << "GPA = " << getGPA() << endl;
}

Student *Student::getNext()
{
	return next;
}

void Student::setNext(Student *pnext)
{
	next = pnext;
}