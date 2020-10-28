/* @author G. Hemingway, copyright 2020 - All rights reserved */
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include "Vector.h"

// Forward declaration.
class Object;

/**
 *  A factory class used to make Object creation easier.
 */
class ObjectFactory {
public:
    /*
     * Deny access to the default constructor - must be used as static factory
     */
    ObjectFactory() = delete;

    /**
     *  Creates an object with the provided parameters. Default values of zero
     *  will be assigned to everything except for name.  Also adds the object to
     * the singleton Universe
     */
    static Object* makeObject(std::string name, double mass = 0, const vector2& pos = vector2(),
        const vector2& vel = vector2());
};

#endif // OBJECT_FACTORY_H
