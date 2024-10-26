#include "Plane.hpp"
// No need for anything else since all includes are defined in plane

// Problem 6 - Implemented in old C/C++ Style using a raw pointer
class Pilot 
{
private:
    string name; // Name of pilot
public:
    // Raw pointer to an object of the Plane class
    Plane* myPlane;
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
    string getName() const { return name; }
};

// Problem 8 - Implemented in old C/C++ Style using a raw pointer
int main() 
{
    double vel = 450.0;                 // Flight Speed between 400 and 500 mph
    int dt = 50;                        // Timestep between 10 and 100 seconds
    int iter = 1010;                    // Maximum Iterations between 1000 and 2000

    // Allocate memory for the Plane using malloc
    void* planeMemory = malloc(sizeof(Plane));
    // Error if memory allocation fails
    if (!planeMemory) 
    {
        cerr << "Failed to allocate memory for Plane." << endl; 
        return -1;
    }
    // Assign a nullptr for the plane for now, 
    // since we will need to refer to it in this scope again later to destroy the plane and free the memory at the end
    Plane* plane = nullptr;
    {                                               // Narrow scoping for Pilot objects
    // Create two Pilot objects
    Pilot pilot1("Captain Sernberger");             // Stack allocated pilot objects do not require 
    Pilot pilot2("First Officer Demirel");          // delete commands to deconstruct
    // Place the new plane into the location of the planeMemory
    plane = new (planeMemory) Plane("SCE", "EWR");
    plane->setVel(vel);
    // Assign the plane to the first pilot's myPlane
    pilot1.myPlane = plane;
    pilot2.myPlane = nullptr;
    // (Initial) Print current pilot's information
    cout << "Pilot " << pilot1.getName() 
        << " with certificate number " << &pilot1
        << " is controlling plate at " << pilot1.myPlane << endl;
    cout << "Pilot " << pilot2.getName() 
        << " with certificate number " << &pilot2
        << " is controlling plate at " << pilot2.myPlane << endl << endl;
    // Loop through iterations
    for (int i = 0; i < iter; i++) 
    {
        // Check if plane is at SCE
        if (plane->getAtSCE()) 
        {
            // Output location of plane
            cout << "The plane " << plane << " is at SCE." << endl;
            // Swap control of the plane between pilots
            swap(pilot1.myPlane, pilot2.myPlane);
            // Print current pilot's information
            cout << "Pilot " << pilot1.getName() 
                << " with certificate number " << &pilot1
                << " is controlling plate at " << pilot1.myPlane << endl;
            cout << "Pilot " << pilot2.getName() 
                << " with certificate number " << &pilot2
                << " is controlling plate at " << pilot2.myPlane << endl << endl;        
        }
        // Operate the plane
        plane->operate(dt);
    }
    } // End scoping to delete pilots before the plane
    plane->~Plane();        // Explicitly call the deconstructor
    free(planeMemory);      // Free the raw memory
    return 0;
}


