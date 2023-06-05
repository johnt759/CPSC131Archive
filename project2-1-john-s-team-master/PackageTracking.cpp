//
//  PackageTracking.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "PackageTracking.h"

PackageTracking::PackageTracking(const string& strnum) {
	trackingNumber = strnum;	// Set the tracking number to strnum
	numUpdates = 0;			// Set the numUpdates to 0
	// Allocate new memory for the header and trailer.
	// Point the sentinel nodes next to trailer
	// and prev to the header.
	header = new ShippingStatus;
	trailer = new ShippingStatus;
	header->next = trailer;
	trailer->prev = header;
	// Set current to nullptr.
	current = nullptr;
}

// add a new update
void PackageTracking::m_addUpdate(const string& status, const string& location, const time_t& timeUpdated){
	// Search from the header and compare the timeUpdated with the input value
	// until it reaches nullptr or timeUpdated is greater than the input value.
	ShippingStatus *ptr = header->next;
	bool flagFound = false;	// needed for boolean check
	while (ptr != trailer)	// While ptr is not pointing to trailer...
	{
		if (ptr->m_getTime() >= timeUpdated)
		{
			// The time updated is found, so break loop.
			flagFound = true;
			break;
		}
		else
		{
			ptr = ptr->next;	// Move the ptr ahead.
		}
	}

	// Create the new ShippingStatus object called ss initialized with constructor.
	ShippingStatus *ss = new ShippingStatus(status, location, timeUpdated);

	// Insert the new node after the ptr.
	(ptr->prev)->next = ss;
	ss->next = ptr;
	ss->prev = ptr->prev;
	ptr->prev = ss;

	// Increment the numUpdates by 1.
	numUpdates++;
	// Assign current to new ShippingStatus
	current = ss;
}

bool PackageTracking::m_moveBackward()//move iterator one step earlier in time
{
	// Check if current->prev is pointing to header.
	// If it is, display exception and return false.
	// Otherwise, move iterator one step back and return true.
	if (current->prev == header)
	{
		cout << "Already at the beginning of ShippingStatus.\n";
		return false;
	}
	else
	{
		current = current->prev;
		return true;
	}
}

bool PackageTracking::m_moveForward()//move iterator one step forward in time
{
	// Check if current->next is pointing to trailer.
	// If it is, display exception and return false.
	// Otherwise, move iterator one step front and return true.
	if (current->next == trailer)
	{
		cout << "Already at the end of ShippingStatus.\n";
		return false;
	}
	else
	{
		current = current->next;
		return true;
	}
}

string PackageTracking::m_getLocation( )//return the location of the current update
{
	// Check if the current location exists or not.
	if (current == nullptr)
	{
		cout << "Cannot return the location.\n";
	}
	else
	{
		return current->m_getLocation(); // Call the function from ShippingStatus.cpp
	}
}

time_t PackageTracking::m_getTime( )//return the time of the current update
{
	// Check if the current time exists or not.
	if (current == nullptr)
	{
		cout << "Cannot return the time updated.\n";
	}
	else
	{
		return current->m_getTime(); // Call the function from ShippingStatus.cpp
	}
}

string PackageTracking::m_getStatus( )//return the status of the current update
{
	// Check if the current status exists or not.
	if (current == nullptr)
	{
		cout << "Cannot return the status.\n";
	}
	else
	{
		return current->m_getStatus(); // Call the function from ShippingStatus.cpp
	}
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
	return numUpdates;
}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to (but not including) the current update you are viewing (may not be the most recent update)
{	
	ShippingStatus *current_org = current;
	current = header->next;
	
	while (current != current_org)
	{
		cout << "Status: " << m_getStatus() << endl;
		cout << "Location: " << m_getLocation() << endl;
		cout << "TimeUpdated: " << m_getTime() << endl;
		current = current->next;
	}
	current = current_org;
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
	ShippingStatus *current_org = current;
	current = current->next;

	while (current != trailer)
	{
		cout << "Status: " << m_getStatus() << endl;
		cout << "Location: " << m_getLocation() << endl;
		cout << "TimeUpdated: " << m_getTime() << endl;
		current = current->next;
	}
	current = current_org;
}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
	// Call the printPreviousUpdates() and the printFollowingUpdates() functions
	m_printPreviousUpdates();
	m_printFollowingUpdates();
}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated)//set current status to the given timeUpdated.
{
	// Search from header and compare timeUpdated with the input.
	// If it is found, then set current to position found and return true.
	// Otherwise, display error and return false.

	// Search from the header and compare the timeUpdated with the input value
	// until it reaches nullptr or timeUpdated is greater than the input value.
	ShippingStatus *ptr = header->next;
	bool flagFound = false;	// needed for boolean check
	while (ptr != trailer)	// While ptr is not pointing to trailer...
	{
		if (ptr->m_getTime() >= timeUpdated)
		{
			// The time updated is found, so break loop.
			flagFound = true;
			break;
		}
		else
		{
			ptr = ptr->next;	// Move the ptr ahead.
		}
	}
	// If the timeUpdated is found, then set current pointer.
	if (flagFound)
	{
		current = ptr;
	}
	return flagFound;
}


bool PackageTracking::m_readTrackingFile(string fileName) {
	// Check whether the text file exists.
	// If it does, perform operations and return true.
	// Otherwise, display error message and return false.
	ifstream myfile(fileName);
	string line;
	if (myfile.is_open()) {
		cout << "Successfully opened file " << fileName << endl;
		
		while (!myfile.eof())
		{
			getline(myfile, line);
			if (line == "new")
			{
				getline(myfile, line, '\n');
				int npos1, npos2;	// Needed to parse the strings
				npos1 = line.find(";");
				npos2 = line.find(";", npos1 + 1);
				//cout << "Adding new shipping status: " << line << endl;
				//cout << "The first semicolon is found at position " << npos1 << endl;
				//cout << "The second semicolon is found at position " << npos2 << endl;
				string status = line.substr(0, npos1);
				string location = line.substr(npos1+1, npos2 - npos1 - 1);
				string time_s = line.substr(npos2+1);
				//cout << "Status = " << status << endl;
				//cout << "Location = " << location << endl;
				//cout << "Time = " << time_s << endl;
				m_addUpdate(status, location, stoi(time_s));
			}
			if (line == "back")
			{
				cout << "Moving backwards." << endl;
				m_moveBackward();
			}
			if (line == "forward")
			{
				cout << "Moving forward." << endl;
				m_moveForward();
			}
		}
		myfile.close();
		return true;
	}
	else
	{
		return false;
	}
}