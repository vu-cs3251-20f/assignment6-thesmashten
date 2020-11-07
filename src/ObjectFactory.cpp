// File name: ArrayListIter.cpp
// Author: Nishant Jain
// VUnetID: jainn6
// Email: nishant.jain@vanderbilt.edu
// Class: CS3251
// Assignment Number: 6
// Description: This class implements an ObjectFactory structure for creating different objects for
// the simulation Honor statement: I attest that I understand the honor code for this class and have
// neither given nor received any unauthorized aid on this assignment. Last Changed: 11/7/20

#ifndef OBJECT_FACTORY_CPP
#define OBJECT_FACTORY_CPP
#include "../include/ObjectFactory.h"
#include "../include/Object.h"
#include "../include/Universe.h"
#include "../include/Visitor.h"
#include <iostream>

/**
 *  Creates an object with the provided parameters. Default values of zero
 *  will be assigned to everything except for name.  Also adds the object to
 * the singleton Universe
 */
Object* ObjectFactory ::makeObject(
    std::string name, double mass, const vector2& pos, const vector2& vel)
{
    Object* tmp = new Object(name, mass, pos, vel);
    Universe* insta = Universe::inst;
    insta->addObject(tmp);
    return tmp;
}
#endif
