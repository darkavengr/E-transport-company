#include <iostream>
#include "vehicle.h"
#include "database.h"
#include "file_path.h"

Database *VehicleDatabase;

/** @file */ 
/*!
 *\file vehicle.cpp
    * 
    * \class Vehicle
    * @brief Vehicle class
    * 
    * @author Matthew Boote
    *
    * @details This represents a vehicle
    *
    */
 /*!
 *\file vehicle.cpp
    * 
    * Vehicle()
    *
    * @brief Vehicle constructor
    * 
    * @author Matthew Boote
    *
    * @details Creates a vehicle object. Loads the vehicle database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    */
Vehicle::Vehicle() {
VehicleDatabase=new Database();

VehicleDatabase->Load( DATA_FOLDER_PATH + "Vehicles.csv");			// load Vehicle information
}

 /*!
 *\file vehicle.cpp
    * 
    * AddVehicle()
    *
    * @brief Adds a vehicle to the vehicle database
    * 
    * @author Matthew Boote
    *  
    * @param[in] Vehicle vehicle
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
bool Vehicle::AddVehicle(Vehicle vehicle) {
 std::vector<std::string> vehiclevector;

 // database uses vector, because it's implementation-agnostic

 vehiclevector.push_back(vehicle.GetRegistration());
 vehiclevector.push_back(vehicle.GetVehicleType());
 vehiclevector.push_back(std::to_string(vehicle.GetWeight()));
 vehiclevector.push_back(std::to_string(vehicle.GetHeight()));

 VehicleDatabase->Save(DATA_FOLDER_PATH + "Vehicles.csv");
 
 return true;
}

 /*!
 *\file vehicle.cpp
    * 
    * GetRegistration()
    *
    * @brief Gets the vehicle registration number
    * 
    * @author Matthew Boote
    * 
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Vehicle::GetRegistration() {
 return(registration);
}

 /*!
 *\file vehicle.cpp
    * 
    * GetVehicleType()
    *
    * @brief Gets the vehicle type
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string cname		Company name
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Vehicle::GetVehicleType() {
 return(vehicletype);
}

 /*!
 *\file vehicle.cpp
    * 
    * GetWeight()
    *
    * @brief Get vehicle weight
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return double
    *
    */
double Vehicle::GetWeight() {
 return(weight);
}

 /*!
 *\file vehicle.cpp
    * 
    * User()
    *
    * @brief GetHeight
    * 
    * @author Matthew Boote
    *
    * @details Gets the vehicle height
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return double
    *
    */
double Vehicle::GetHeight() {
 return(height);
}

 /*!
 *\file vehicle.cpp
    * 
    * SetRegistration()
    *
    * @brief Sets the vehicle registration
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string reg
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Vehicle::SetRegistration(std::string reg) {
 registration=reg;
}

 /*!
 *\file vehicle.cpp
    * 
    * SetVehicleType()
    *
    * @brief Sets the vehicle type
    * 
    * @author Matthew Boote
    *
    * @desc The vehicle could be LGV, HGV or van
    *
    * @param[in] std::string vt
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Vehicle::SetVehicleType(std::string vt) {
 vehicletype=vt;
}

 /*!
 *\file vehicle.cpp
    * 
    * SetWeight()
    *
    * @brief Sets the vehicle weight
    * 
    * @author Matthew Boote
    *
    * @param[in] int wt
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Vehicle::SetWeight(int wt) {
 weight=wt;
}

 /*!
 *\file vehicle.cpp
    * 
    * SetHeight()
    *
    * @brief Sets the vehicle height
    * 
    * @author Matthew Boote
    *
    * @param[in] int ht
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Vehicle::SetHeight(int ht) {
 height=ht;
 }

 /*!
 *\file vehicle.cpp
    * 
    * ValidateRegistration()
    *
    * @brief Validates vehicle registration
    * 
    * @author Matthew Boote
    *
    * @desc The registration format is checked; the format should be in form AANNNAAA where A is a letter and N is a number.
    *
    * @param[in] std::string regnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */

bool Vehicle::ValidateRegistration(std::string regnumber) {
int count=0;
Database CPCNumberDatabase;
std::vector<std::string> cpc_entry;
	
// registration number is in the format AANNNAAA

 if(regnumber.length() < 8) return false;		// must be 8 characters long

 for(count=0;count < 2;count++) {
  if(isupper(regnumber[count]) == 0) return false;			// invalid format
 }

// Must have three digits following

 for(count=2;count<4;count++) {
  if(isdigit(regnumber[count]) == 0) return false;			// invalid format
 }

 for(count=5;count<8;count++) {
  if(isupper(regnumber[count]) == 0) return false;			// invalid format
 }

 return true; 
}
