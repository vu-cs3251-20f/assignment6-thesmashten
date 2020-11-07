//
// Created by Nishant Jain on 11/5/20.
//
#ifndef VISITOR_CPP
#define VISITOR_CPP
#include <iostream>
#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include "../include/Visitor.h"

/**
 *  Construct a visitor that prints to the provided ostream.
 */
PrintVisitor :: PrintVisitor(std::ostream& os) : os(os){}

/**
 *  Prints the object's name.
 */
void PrintVisitor :: visit(Object& object){
    os << object.getName();
}

#endif
