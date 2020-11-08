// File name: Visitor.cpp
// Author: Nishant Jain
// VUnetID: jainn6
// Email: nishant.jain@vanderbilt.edu
// Class: CS3251
// Assignment Number: 6
// Description: This class implements a Visitor structure for printing names of different objects
// for the simulation Honor statement: I attest that I understand the honor code for this class and
// have neither given nor received any unauthorized aid on this assignment. Last Changed: 11/7/20

#ifndef VISITOR_CPP
#define VISITOR_CPP
#include "../include/Visitor.h"
#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include <iostream>

/**
 *  Construct a visitor that prints to the provided ostream.
 */
PrintVisitor ::PrintVisitor(std::ostream& os)
    : os(os)
{
}

/**
 *  Prints the object's name.
 */
void PrintVisitor ::visit(Object& object)
{
    os << object.getName();
}

#endif
