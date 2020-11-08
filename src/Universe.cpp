// File name: Universe.cpp
// Author: Nishant Jain
// VUnetID: jainn6
// Email: nishant.jain@vanderbilt.edu
// Class: CS3251
// Assignment Number: 6
// Description: This class implements a Universe structure for different objects for the simulation
// Honor statement: I attest that I understand the honor code for this class and have neither given
// nor received any unauthorized aid on this assignment.
// Last Changed: 11/7/20

#ifndef UNIVERSE_CPP
#define UNIVERSE_CPP
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include "../include/Universe.h"
#include "../include/Visitor.h"

/**
 *  Returns the only instance of the Universe
 */
Universe* Universe::inst = nullptr;
;
Universe* Universe ::instance()
{
    if (inst == nullptr) {
        inst = new Universe();
    }
    return inst;
}

/**
 *  Releases all the dynamic objects still registered with the Universe.
 */
Universe ::~Universe()
{
    release(objects);
    inst = nullptr;
}

/**
 *  Returns the begin iterator to the actual Objects. The order of iteration
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::iterator Universe::begin()
{
    return objects.begin();
}

/**
 *  Returns the end iterator to the actual Objects. The order of iteration
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::iterator Universe::end()
{
    return objects.end();
}

/**
 *  Returns the end iterator to the actual Objects. The order of itetarion
 *  will be the same as that over getSnapshot()'s result as long as no new
 *  objects are added to either of the containers.
 */
Universe::const_iterator Universe::end() const
{
    return objects.end();
}

/**
 *  Returns a container of copies of all the Objects registered with the
 *  Universe. This should be used as the source of data for computing the
 *  next step in the simulation
 */
std::vector<Object*> Universe ::getSnapshot() const
{
    std::vector<Object*> ret;
    for (Object* obj : objects) {
        ret.push_back(obj->clone());
    }
    return ret;
}

/**
 *  Advances the simulation by the provided time step. For this assignment,
 *  you must assume that the first registered object is a "sun" and its
 *  position should not be affected by any of the other objects.
 *
 */
void Universe ::stepSimulation(const double& timeSec)
{
    std::vector<Object*> thisObj = getSnapshot();
    for (uint32_t i = 1; i < thisObj.size(); ++i) {
        vector2 forces = vector2();
        for (uint32_t j = 0; j < thisObj.size(); ++j) {
            if (i != j) {
                forces += objects[i]->getForce(*objects[j]);
            }
        }
        vector2 acceleration = forces / objects[i]->getMass();
        vector2 velocity = objects[i]->getVelocity() + acceleration * timeSec;
        vector2 position = objects[i]->getPosition() + (objects[i]->getVelocity() * timeSec);
        thisObj[i]->setVelocity(velocity);
        thisObj[i]->setPosition(position);
    }
    swap(thisObj);
}

/**
 *  Swaps the contents of the provided container with the Universe's Object
 *  store and releases the old Objects.
 */
void Universe ::swap(std::vector<Object*>& snapshot)
{
    objects.swap(snapshot);
    release(snapshot);
}

/**
 *  Registers an Object with the universe. The Universe will clean up this
 *  object when it deems necessary.
 */
Object* Universe::addObject(Object* ptr)
{
    objects.push_back(ptr);
    return ptr;
}

/**
 *  Calls delete on each pointer and removes it from the container.
 */
void Universe ::release(std::vector<Object*>& object)
{
    for (uint32_t i = 0; i < object.size(); ++i) {
        delete object[i];
    }
    object.clear();
}

#endif
// comment