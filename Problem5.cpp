#include "Plane.hpp"
// No need for anything else since all includes and namespace are defined in plane

// Problem 5 main function
int main() 
{
    double vel = 450;                   // Choose Flight Speed between 400 and 500 mph
    int dt = 50;                        // Choose Timestep between 10 and 100 seconds
    int iter = 1010;                    // Choose Maximum Iterations between 1000 and 2000
    Plane plane("SCE", "PHL");          // Instantiate a Plane object
    plane.setVel(vel/3600.0);           // Set the speed of the plane

    // BEGIN ITERATIONS
    int t = 0;
    for (int i = 0; i < iter; i++)      // Iterate, calling the operate function
    {
        // Print the current time and position
        cout << "Time: " << t << " seconds, Position: " << plane.getPos() << " miles" << endl;
        plane.operate(dt);              // Operate the plane for this timestep
        t += dt;                        // Increment the time by timestep
    }
    return 0; 
}