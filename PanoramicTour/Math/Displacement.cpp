/*
 * Displacement.cpp
 *
 *  Created on: 28 juil. 2013
 *      Author: hallison
 */

#include "Displacement.h"

Displacement::Displacement() {

}



Displacement::~Displacement() {
	// TODO Auto-generated destructor stub
	//no memory to deallocate
}

Displacement::Displacement(float x, float y, float z) {
	this->x = x;	this->y = y;	this->z = z;
}