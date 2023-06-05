#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Registrar.h"

using namespace std;

// default constructor
Registrar::Registrar()
{
	numStudents = 0;	// set numStudents to 0
	head = nullptr;		// set head to nullptr
}

// destructor
Registrar::~Registrar()
{
}

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void Registrar::readTextfile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string courseName;
		string cwid;
		char grade;
		while (myfile >> courseName >> cwid >> grade) {
			cout << cwid << " " << grade << endl;
			addLine(courseName, cwid, grade);
		}
		myfile.close();
	}
	else
		throw invalid_argument("Could not open file " + filename);
}

// return Student object corresponding to a given CWID
// getStudent must throw an exception if cwid is invalid
Student& Registrar::getStudent(string pcwid) const {
	// First, use the bool found to check whether an invalid cwid exists.
	// If it does, then throw an exception with an error message.
	// Otherwise, return the reference and set the bool found to true.
	Student *ptr;
	ptr = head;
	bool found;
	found = false;

	while ((ptr != NULL) && (found == false))
	{
		if (ptr->getCWID() == pcwid)
		{
			found = true;
		}
		else
		{
			ptr = ptr->getNext();
		}
	}
	if (found == true)
	{
		return *ptr;
	}
	else
	{
		throw invalid_argument("Invalid CWID");
		//exit(1);
		return *ptr;
	}
}

// process a line from the text file
void Registrar::addLine(string courseName, string pcwid, char grade) {
	// Use the try/catch block to check if the student does not exist.
	// If it does not, then create a new student object and call the
	// addCourseGrade function. Otherwise, just call the getStudent
	// and the addCourseGrade functions.
	try {
		Student &s = getStudent(pcwid);
		s.addCourseGrade(courseName, grade);
	}
	catch (exception &e)
	{
		Student *s0 = new Student(pcwid);
		s0->setNext(head);
		head = s0;
		numStudents++;
		s0->addCourseGrade(courseName, grade);
	}
}

