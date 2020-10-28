/* @author G. Hemingway, copyright 2020 - All rights reserved */
#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <Vector.h>
#include <vector>

// Forward declaration
class Object;
class ObjectFactory;

/**
 *  A singleton class representing the Universe. For this assignment, the first
 *  object added to the Universe will be considered unmovable and so its
 *  position should not be changed.
 */
class Universe {
public:
    // Iterator typedefs
    typedef std::vector<Object*>::iterator iterator;
    typedef std::vector<Object*>::const_iterator const_iterator;

    static constexpr double G = 6.67428e-11;

    /**
     *  Returns the only instance of the Universe
     */
    static Universe* instance();

    /**
     *  Releases all the dynamic objects still registered with the Universe.
     */
    ~Universe();

    /**
     *  Returns the begin iterator to the actual Objects. The order of itetarion
     *  will be the same as that over getSnapshot()'s result as long as no new
     *  objects are added to either of the containers.
     */
    iterator begin();

    /**
     *  Returns the begin iterator to the actual Objects. The order of itetarion
     *  will be the same as that over getSnapshot()'s result as long as no new
     *  objects are added to either of the containers.
     */
    const_iterator begin() const;

    /**
     *  Returns the end iterator to the actual Objects. The order of itetarion
     *  will be the same as that over getSnapshot()'s result as long as no new
     *  objects are added to either of the containers.
     */
    iterator end();

    /**
     *  Returns the end iterator to the actual Objects. The order of itetarion
     *  will be the same as that over getSnapshot()'s result as long as no new
     *  objects are added to either of the containers.
     */
    const_iterator end() const;

    /**
     *  Returns a container of copies of all the Objects registered with the
     *  Universe. This should be used as the source of data for computing the
     *  next step in the simulation
     */
    std::vector<Object*> getSnapshot() const;

    /**
     *  Advances the simulation by the provided time step. For this assignment,
     *  you must assume that the first registered object is a "sun" and its
     *  position should not be affected by any of the other objects.
     */
    void stepSimulation(const double& timeSec);

    /**
     *  Swaps the contents of the provided container with the Universe's Object
     *  store and releases the old Objects.
     */
    void swap(std::vector<Object*>& snapshot);

private:
    /**
     *  Private constructor. Ensures access control.
     */
    Universe() = default;

    /**
     *  Registers an Object with the universe. The Universe will clean up this
     *  object when it deems necessary.
     */
    Object* addObject(Object* ptr);
    friend class ObjectFactory;

    /**
     *  Calls delete on each pointer and removes it from the container.
     */
    void release(std::vector<Object*>& objects);

    /**
     *  Container for pointers to the registered Objects.
     */
    std::vector<Object*> objects;

    /**
     *  Static pointer that ensures only a single instance of this class exists.
     */
    static Universe* inst;
};

#endif // UNIVERSE_H
