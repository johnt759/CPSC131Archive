#pragma once
#include <string>
#include <stdexcept>
#include "Student.h"

using namespace std;

class Registrar {
public:
	Registrar();	// empty constructor
	~Registrar();	// destructor
	void readTextfile(string filename); // Load information from a text file with the given filename: THIS IS COMPLETE
	void addLine(string courseName, string cwid, char grade); // process a line from the text file
	Student& getStudent(string pcwid) const; // return the Student object corresponding to a given CWID
	// getStudent must throw an exception if cwid is invalid
	// add constructors, destructors, assignment operators if needed

private:
	int numStudents;
	Student *head;
};
