//
// Created by Nishant Jain on 11/4/20.
//

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
