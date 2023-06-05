//
//  ShippingStatus.cpp
//  Project2
//
//  Created by Han, Wenlin on 2/13/18.
//  Copyright © 2018 Han, Wenlin. All rights reserved.
//

#include "ShippingStatus.h"

ShippingStatus::ShippingStatus() {
	// Set string status and location to null
	// then set time_t timeUpdated to zero.
	status = "null";
	location = "null";
	timeUpdated = 0;
}

ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated) {
	this->status = status;
	this->location = location;
	this->timeUpdated = timeUpdated;
}

string ShippingStatus::m_getStatus(){
	return status;
}

string ShippingStatus::m_getLocation(){
	return location;
}

time_t ShippingStatus::m_getTime() {
	return timeUpdated;
}