#include "Problem1.hpp"

// Function to Calculate Moment
double calculateMoment(double weight, double arm) {
    return weight * arm;
}

int main() {
    // Ouput and Input sequence for all necessary values
    cout << "Enter the airplane empty weight (lbs): " << endl; cin >> Empty_W;                              // Empty plane weight
    cout << "Enter the airplane empty-weight moment (lbs-inches): " << endl; cin >> Empty_WM;               // Empty weight moment
    cout << "Enter the number of front seat occupants: " << endl; cin >> num_focc;                          // Number of front seat passengers
    for (int i = 0; i < num_focc; i++) {
        cout << "Enter the weight of front seat occupant: " << i+1 << " (lbs): " << endl; cin >> foccw[i];  // Entering weight of front passengers into a vector 
    }
    cout << "Enter the front seat moment arm (inches): " << endl; cin >> fr_arm;                            // Front seat moment arm
    cout << "Enter the number of rear seat occupants: " << endl; cin >> num_rocc;                           // Number of rear seat passengers
    for (int i = 0; i < num_rocc; i++) {
        cout << "Enter the weight of rear seat occupant " << i+1 << " (lbs): " << endl; cin >> roccw[i];    // Entering weight of rear passengers into a vector
    }
    cout << "Enter the rear seat moment arm (inches): " << endl; cin >> r_arm;                              // Rear seat moment arm
    cout << "Enter the number of gallons of usable fuel: " << endl; cin >> fuel_gal;                        // Amount of fuel onboard in gallons
    cout << "Enter the usable fuel weight per gallon (lbs): " << endl; cin >> fuel_WPG;                     // Fuel gallons per weight conversion factor
    cout << "Enter the fuel tank moment arm (inches): " << endl; cin >> fuel_arm;                           // Fuel tank moment arm
    cout << "Enter the baggage weight (lbs): " << endl; cin >> bag_w;                                       // Total baggage weight
    cout << "Enter the baggage moment arm (inches): " << endl; cin >> bag_arm;                              // Baggage moment arm

    for (int i = 0; i < num_focc; i++) {
        tot_FW += foccw[i];                                                                                 // Adding weight of the two front seat passengers together
    }
    tot_fmom = calculateMoment(tot_FW, fr_arm);                                                             // Calling the moment function to calculate front seat component
    for (int i = 0; i < num_rocc; i++) {
        tot_RW += roccw[i];                                                                                 // Adding weight of the two rear seat passengers together
    }
    tot_rmom = calculateMoment(tot_RW, r_arm);                                                              // Calling the moment function to calculate rear seat component
    tot_FW = fuel_gal * fuel_WPG;                                                                           // Calculating fuel weight by converting gallons to lbs
    double tot_FMom = calculateMoment(tot_FW, fuel_arm);                                                           // Calling moment function to calculate fuel component
    tot_bagmom = calculateMoment(bag_w, bag_arm);                                                           // Calling moment function to calculate baggage component  
    gross_w = Empty_W + tot_FW + tot_RW + tot_FW + bag_w;                                                   // Calculating total weight from aircraft, front/rear seat, fuel, and baggage components
    tot_mom = Empty_WM + tot_fmom + tot_rmom + tot_FMom + tot_bagmom;                                       // Calculating total moment from aicraft, front/rear, fuel, and baggage components
    CG = tot_mom / gross_w;                                                                                 // Calculating center of gravity by dividing total moment by total weight
    // Display gross weight and CG
    cout << fixed << setprecision(2);                                                                       // Specifycing decimal precision of the output
    cout << "Gross Weight = " << gross_w << " lbs." << endl;                                                // Outputting current total weight 
    cout << "Center of Gravity = : " << CG << " in." << endl;                                               // Outputting current center of gravity position

    // Check if gross weight and CG are within limits
    if (gross_w > Max_GW || CG < Forward_CGL || CG > Aft_CGL) {
        cout << "Error: Gross Weight and/or Center of Gravity are out of max allowable design limits!"      // Outputting breach of design limits if weight or center of gravity exceed them
        << endl;
        // Setting variables for loop
        new_fuelgal = fuel_gal;                                                              
        success = false;
        // Loop to adjust fuel to move total weight and center of gravity back within max design limits
        while (new_fuelgal >= 0) {
            tot_FW = new_fuelgal * fuel_WPG;                                                                // Calculating new total fuel weight
            tot_FMom = calculateMoment(tot_FW, fuel_arm);                                                   // Calling moment function to recalculate moment for this iteration
            gross_w = Empty_W + tot_FW + tot_RW + tot_FW + bag_w;                                           // Recalculating total weight from all components
            tot_mom = Empty_WM + tot_fmom + tot_rmom + tot_FMom + tot_bagmom;                               // Recalculating total moment from all components
            CG = tot_mom / gross_w;                                                                         // Recalculating center of gravity
            if (gross_w <= Max_GW && CG >= Forward_CGL && CG <= Aft_CGL) {
                success = true;                                                                             // If statement to check if weight and center of gravity are now within design limits
                break;
            }
            new_fuelgal -= 0.01;                                                                            // Decrement new gallons of fuel to move center of gravity and reduce weight
            if (new_fuelgal < 0)
                new_fuelgal = 0;                                                                            // If statement to set fuel gallons to zero if it goes below zero
        }
        if (success) {
            cout << "Adjusted fuel amount to meet design limits = " << new_fuelgal << " gal." << endl;      // Ouputting new fuel onboard in gallons
            cout << "New Gross Weight = " << gross_w << " lbs." << endl;                                    // Outputting new total weight
            cout << "New Center of Gravity = " << CG << " in." << endl;                                     // Ouputting new center of gravity position
        } 
        else {
            cout << "Unable to adjust fuel to meet gross weight and CG design limits." << endl;             // If fuel is reduced to 0 before meeting design limits, output statement about recalculation failure
        }
    } else {
        cout << "Gross weight and CG are within design limits." << endl;                                    // If recalculation is successful output statement confirming weight and center of gravity within limits
    }
    return 0;
}