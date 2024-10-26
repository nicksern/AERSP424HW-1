#include "Plane.hpp"
#include <memory> // For shared_ptr
// No need for anything else since all includes and namespace are defined in plane

// Problem 6 - Implemented in Modern C++ Style using a shared pointer
class Pilot 
{
private:
    string name; // Name of pilot
public:
    // Shared modern pointer to an object of the Plane class
    shared_ptr<Plane> myPlane; // We use a shared pointer to allow both pilots to access the pointer until it is deleted
    // Constructor
    Pilot(const string& pilotN) : name(pilotN), myPlane(nullptr) 
    {
        // Output pilot's name, memory address, and that they are ready to board
        cout << "Pilot " << name << " with certification number " << this 
        << " is at the gate, ready to board the plane." << endl;        
    }
    // Destructor
    ~Pilot() 
    {
        // Outputting that the pilot is off the plane
        cout << "Pilot " << name << " is out of the plane." << endl;                
    }
    // Getter function for pilot name
    string getName() const { return name;}
};

// Problem 7 - Implemented in modern C++ Style
int main() 
{
    double vel = 450.0;                 // Flight Speed between 400 and 500 mph
    int dt = 50;                        // Timestep between 10 and 100 seconds
    int iter = 1010;                    // Maximum Iterations between 1000 and 2000
    // We initialize the plane pointer outside the scope of the pilots
    // so that the plane isn't destroyed before the pilots leave.
    shared_ptr<Plane> plane; 
    { // Scoping with brackets allows pilots to leave before the plane is destroyed
    // Create two Pilot objects
    // No reason to use pointers here because there are only 2 statically allocated pilots
    Pilot pilot1("Captain Demirel");                // Stack allocated pilot objects do not require 
    Pilot pilot2("First Officer Sernberger");       // delete commands to deconstruct
    // Fill in the plane pointer
    plane = make_shared<Plane>("SCE", "EWR");          
    plane->setVel(vel / 3600.0); // Set speed in miles per second (use -> instead of . because pointer
    // Initial assignment of the plane to the first pilot
    pilot1.myPlane = plane;
    pilot2.myPlane = nullptr;
    // (Initial) Print current pilot's information
    cout << "Pilot " << pilot1.getName() 
        << " with certificate number " << &pilot1
        << " is controlling plate at " << pilot1.myPlane.get() << endl;
    cout << "Pilot " << pilot2.getName() 
        << " with certificate number " << &pilot2
        << " is controlling plate at " << pilot2.myPlane.get() << endl << endl;
    // Loop through iterations
    for (int i = 0; i < iter; i++) 
    {
        // Check if plane is at SCE
        if (plane->getAtSCE()) 
        {
            // Output location of plane
            cout << "The plane " << plane.get() << " is at SCE." << endl;
            // Swap control of the plane between pilots
            swap(pilot1.myPlane, pilot2.myPlane);
            // Print current pilot's information
            cout << "Pilot " << pilot1.getName() 
                << " with certificate number " << &pilot1
                << " is controlling plate at " << pilot1.myPlane.get() << endl;
            cout << "Pilot " << pilot2.getName() 
                << " with certificate number " << &pilot2
                << " is controlling plate at " << pilot2.myPlane.get() << endl << endl;        
        }
        // Operate the plane
        plane->operate(dt);
    }
    }
    return 0;
}
