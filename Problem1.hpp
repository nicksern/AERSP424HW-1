#ifndef PROBLEM1_HPP // #include guards mandated 
#define PROBLEM1_HPP

#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
// All necessary include statements

// Declaring variables for calculations
double Empty_W, Empty_WM;
int num_focc;
int num_rocc;
double fr_arm, r_arm;
double fuel_WPG, fuel_arm;
double bag_w, bag_arm;
double fuel_gal;
double tot_FW = 0.0;
double tot_RW = 0.0;
double tot_fmom;
double tot_rmom;
double tot_bagmom;
double gross_w;
double tot_mom;
double CG;
double new_fuelgal;
bool success;

// Defining max allowed design limits
const double Max_GW = 2950.0;
const double Forward_CGL = 82.1;
const double Aft_CGL = 84.7;

// Setting up vectors for passengers weights by row
vector<double> foccw(num_focc);
vector<double> roccw(num_rocc);

#endif