#include "Problem2.hpp"

int main() {
    // Adding the flight distances to the map container
    flight_dist["PHL"] = 160;  // Flight distance between State College and Philadelphia
    flight_dist["ORD"] = 640;  // Flight distance between State College and Chicago
    flight_dist["EWR"] = 220;  // Flight distance between State College and Newark
    
    // Outputting the flight information
    cout << "Flight distances from University Park Airport (SCE):" << endl;
    for (const auto& flight : flight_dist) {
        // Outputting the flight route (from and to) and distance
        cout << "SCE to " << flight.first << ": " << flight.second << " miles." << endl;        
    }
    return 0;
}