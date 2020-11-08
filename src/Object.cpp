// File name: Object.cpp
// Author: Nishant Jain
// VUnetID: jainn6
// Email: nishant.jain@vanderbilt.edu
// Class: CS3251
// Assignment Number: 6
// Description: This class implements an Object structure for creating different objects for the
// simulation Honor statement: I attest that I understand the honor code for this class and have
// neither given nor received any unauthorized aid on this assignment. Last Changed: 11/7/20

#ifndef OBJECT_CPP
#define OBJECT_CPP
#include "../include/Object.h"
#include "../include/ObjectFactory.h"
#include "../include/Universe.h"
#include "../include/Visitor.h"
#include <iterator>
#include <string>

/**
 *  Initializes an object with the provided properties - really only called by
 * the ObjectFactory
 */
Object ::Object(const std::string& name, double mass, const vector2& pos, const vector2& vel)
    : name(name)
    , mass(mass)
    , position(pos)
    , velocity(vel)
{
}

/**
 *  An entry point for a visitor.
 */
void Object ::accept(Visitor& visitor)
{
    return visitor.visit(*this);
}

/**
 *  Implementation of the prototype. Returns a dynamically allocated deep
 *  copy of this object.
 */
Object* Object ::clone() const
{
    Object* obj = new Object(name, mass, velocity, position);
    return obj;
}

/**
 *  Returns the mass.
 */
double Object ::getMass() const noexcept
{
    return mass;
}

/**
 *  Returns the name.
 */
std::string Object ::getName() const noexcept
{
    return name;
}

/**
 *  Returns the position vector.
 */
vector2 Object ::getPosition() const noexcept
{
    return position;
}

/**
 *  Returns the velocity vector.
 */
//* The velocity of an object equals the change in its position divided by the corresponding change
// in time.
vector2 Object ::getVelocity() const noexcept
{
    return velocity;
}

/**
 *  Calculates the force vector between lhs and rhs. The direction of the
 *  result is as experienced by lhs. Negate the result to obtain force
 *  experienced by rhs.
 *  the magnitude of the force vector due to gravity between two objects is equal to
 *  G times the mass of the first times the mass of the second
 *  divided by the square of the distance between the two.
 */
vector2 Object ::getForce(const Object& rhs) const noexcept
{
    double numerator = ((Universe::G)*mass * rhs.mass);
    double denominator = (rhs.position - position).normSq();
    double fMag = numerator / denominator;
    vector2 direction = (rhs.position - position).normalize();
    return direction.scale(fMag);
}

/**
 *  Sets the position vector.
 */
void Object ::setPosition(const vector2& pos)
{
    position = pos;
}

/**
 *  Sets the velocity vector.
 */
void Object ::setVelocity(const vector2& vel)
{
    velocity = vel;
}

/**
 *  Returns true if this object is member-wise equal to rhs.
 */
bool Object ::operator==(const Object& rhs) const
{
    if (position == rhs.position)
        if (velocity == rhs.velocity)
            if (abs(mass - rhs.mass) < 0.001)
                if (name == rhs.name)
                    return true;
    return false;
}

/**
 *  Returns !(*this == rhs).
 */
bool Object ::operator!=(const Object& rhs) const
{
    return !(*this == rhs);
}

#endif
// comment
