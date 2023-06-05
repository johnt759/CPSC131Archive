//
//  ShippingStatus.h
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#ifndef ShippingStatus_h
#define ShippingStatus_h

#pragma once

#include <string>
using namespace std;

class ShippingStatus {
public:
    ShippingStatus();
    ShippingStatus(const string& status, const string& location, const time_t& timeUpdated );

    string m_getStatus();
    string m_getLocation();
    time_t m_getTime();
    
private: 
	string status;
	string location;
	time_t timeUpdated;
	// The following pointers are needed for linked list operations.
	ShippingStatus *next;
	ShippingStatus *prev;
	friend class PackageTracking;	// provide access to PackageTracking
};


#endif /* ShippingStatus_h */

