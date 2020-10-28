# CS 3251: Intermediate Software Design
## Programming Assignment 6

## Overview

Design patterns are essential in developing anything larger than a trivial program. This assignment requires you to start implementing the meaningful portions of the Gravitational Simulation project using some of the simpler patterns.

This assignment provides a number of header files and requires the implementation of the corresponding *.cpp files using appropriate patterns. A few basic physics principles are required to code the actual simulation.  While this may seem overwhelming at first glance, thanks to the Vector class, the actual math will be very easy to implement.

Do not change any of the header files (with the exception of ```tests/testHelper.h``` for the graduate students). Please start early and ask questions as they arise. One of the tests simulates every second of the Earth’s journey around the sun for a year, the final binary may take up to a few minutes to execute. It is crucial that your approach to developing the application does not rely upon frequent executions.

## Classes

* Universe – A class responsible for keeping track of all the objects in your simulation. Since no more than one such environment should exist, it makes sense to make this class a Singleton. For this assignment you are to assume that the first object registered with the Universe is a “sun” and it should not be affected by any forces.

* Object – The base class of the class hierarchy designed to outline the interface for objects to be used in the simulation. We can imagine that certain objects may be composed of other bodies so this class could eventually exhibit the Composite pattern. Correct handling of different types of objects requires this class provide an access point for a Visitor. Finally, to make all force applications appear simultaneously, a “snapshot” method will be available via the Prototype.

* ObjectFactory – An Abstract Factory implementation that provides an easy way of creating celestial Objects based on a string argument.

* Visitor – A Visitor abstract base class will be defined as well as a concrete subclass, the PrintVisitor. The latter will be responsible for testing the Visitor/Iterator framework via simple print tests.

## Physics Concepts Required for this Assignment: 

* The Law of Universal Gravitation: the magnitude of the force due to gravity between two objects is equal to G times the mass of the first times the mass of the second divided by the square of the distance between the two. 

* The Second Law of Motion: the net force acting on an object is equal to its mass times its acceleration.

* The net force acting on upon an object is also equal to the sum of all the forces acting upon it.

* The acceleration of an object equals the change in its velocity divided by the corresponding change in time.

* The velocity of an object equals the change in its position divided by the corresponding change in time.

Acceleration, force, position, and velocity are all vector quantities. 

## Hints

* The overall simulation breaks time into small steps.  Look at the heart of the UMC test.  There is a loop that goes through an entire year, with a step size of 1 second.  Use the state information for each object in the Universe to calculate state for the next step - make sure to keep the state in the current step completely unchanged until you have fully calculated the state in the next step.

* Start with the two easier tests first - Inertia and Visitor. Once these are working as expected, then move on to the UMC test.

## Undergraduate Students:

As always, do not change the CMakeList.txt or any of the build-related files.  Concentrate all of your effort and changes into the *.cpp files in the ./src directory.  I have provided a solution to the Vector class - you should not need to change this.

Undergraduates are to use the test drivers, and test data files provided in the repository.  By default GRADUATE is not defined in ```tests/testHelper.h```. The undergraduates are not required to fully implement Parser for this assignment. You must implement enough of it to compile and pass the undergraduate tests.  Undergraduates who would like to complete the graduate student requirements for their assignment may do so if they choose.


## Graduate Students: 

Graduate students are to use test drivers and test data files provided in the repository, but must #define GRADUATE in ```tests/testHelper.h```. The graduate students are required to fully implement Parser for this assignment. 

* Parser – The parser is to be capable of processing simple scripts that will set up the Universe. This will reduce the amount of driver code necessary to run your simulations. Each line of the script file represents one object as follows.

```{name, mass, [positionX positionY], [velocityX velocityY]}.``` 

Name will be a string while all other quantities will be doubles.

```
Example:
{earth, 5.9742e24,  [149597870700 0], [0 29788.4676]}
```

Hint: ```std::strtok()``` is going to be your friend.

## Reminders

* Ensure that your name, vunetid, email address, and the honor code appear in the header comments of all files that you have altered.

* Do not alter any of the project files!  Work only on those files specified above.  You must use the supplied `CMakeLists.txt` file as is.

* All students are required to abide by the CS 3251 coding standard, [available on the course web page](https://vuse-cs3251.github.io/style-guidelines/) and provided to you on the first day of class. Points will be deducted for not following the coding standard.

* For full credit, your program must compile with a recent version of `clang` or `gcc` and run successfully with the CI platform.
  * The CI build *will* fail if your code is not properly formatted. **This is by design.** If your code is compiling and running successfully, but the build is failing, then your build is most likely failing because your code is not passing the linter. This can be confirmed by checking if a command involving `linter` or `clang-format` in the CI build output log has an exit code of 1.

* Your program(s) should always have an exit code of 0.  A non-zero exit code (generally indicative of a segmentation fault or some other system error) is reason to worry and must be corrected for full points.
  
* When submitting the assignment, all files that are provided to you, plus your solution files have been submitted. All files necessary to compile and run your program must reside in the GitHub.com repository. 
