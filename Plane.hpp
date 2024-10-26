#ifndef PLANE_HPP // #include guards mandated 
#define PLANE_HPP
#include <iostream>
#include <string>
#include <algorithm> // For swap
#include <map>
using namespace std;

// The plane class of Problem 3 & 4 is defined here
class Plane 
{
private:
    double dist;                    // Dist - Distance 
    double pos;                     // Pos - Position
    double vel;                     // Vel - velocity
    bool at_SCE;                    // At SCE?
    string origin;                  // Origin
    string destination;             // Destination
    map<string, int> flight_dist;   // Pasted map container from problem 2.

    // Method to try and find the distance value between two airports
    double calcDist(const string& from, const string& to) 
    {   
        // Assume either starting at SCE or ending at SCE
        if (from == "SCE")                                      // Start at SCE
        {
            if (flight_dist.find(to) != flight_dist.end())      // Use the map to check if the "to" value exists
            {
                return flight_dist[to];
            } 
            else 
            {
                return 0.0;
            }
        } else if (to == "SCE")                                 // End at SCE
        {
            if (flight_dist.find(from) != flight_dist.end())    // Use the map to check if the "from" value exists
            {
                return flight_dist[from];
            } 
            else 
            {
                return 0.0;
            }
        } else {
            return 0.0; // No distance available
        }
    }

public:
    // Constructor
    Plane(const string& from, const string& to)
        : origin(from), destination(to), pos(0), vel(0), at_SCE(false) 
    {
        // Adding the flight distances to the map container in the constructor to initialize the flight map
        flight_dist["PHL"] = 160;  // Flight distance between State College and Philadelphia
        flight_dist["ORD"] = 640;  // Flight distance between State College and Chicago
        flight_dist["EWR"] = 220;  // Flight distance between State College and Newark

        dist = calcDist(origin, destination);
        cout << "Plane created with with a tail number at: " << this << endl;
    }

    // Deconstructor
    ~Plane() 
    {
        cout << "Plane should get destroyed ... now!" << endl;
        cout << "Plane Destroyed." << endl;
    }

    // Getter functions
    string getOrigin() const { return origin; }
    string getDest() const { return destination; }
    double getDist() const { return dist; }
    double getPos() const { return pos; }
    double getVel() const { return vel; }
    bool getAtSCE() const { return at_SCE; }
    // Setter functions
    void setPos(double position) { pos = position >= 0 ? position : 0; } // Position cannot be negative
    void setVel(double velocity) { vel = velocity >= 0 ? velocity : abs(velocity); } // Velocity magnitude used
    void setAtSCE(bool value) { at_SCE = value; }

    // Operate function (Problem 4)
    void operate(double dt) {
        dt = (dt < 0) ? 0 : dt;                                         // Time cannot be negative
        if (pos < dist) 
        {
            pos += vel * dt;
            pos = (pos > dist) ? dist : pos;                            // Cap position at distance
            at_SCE = false;
        } 
        else 
        {
            cout << "Navigation from " << origin << " to " << destination
                << " has been completed. On to the next leg!" << endl;
            at_SCE = (destination == "SCE") ? true : at_SCE;            // Set at_SCE accordingly
            swap(origin, destination);                                  // Swap origin and destination
            dist = calcDist(origin, destination);                       // Recalculate distance after swapping
            pos = 0.0;
        }
    }
};

#endif // PLANE_HPP