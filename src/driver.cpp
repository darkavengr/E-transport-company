/*
 * driver.cpp
 *
 * Author: Adeeb Sait and Matthew Boote
 *
 */

/** @file */ 

#include <iostream>

#include "driver.h"
#include "database.h"
#include "user.h"
#include "transaction.h"
#include "file_path.h"

std::string encrypt(std::string pw, std::string salt);

/*!
 *\file driver.cpp
    * 
    * \class Driver
    * @brief Driver class
    * 
    * @author Matthew Boote
    *
    * @details This represents a driver.
    *
    */


 /*!
 *\file driver.cpp
    * 
    * Driver()
    *
    * @brief Driver construction
    * 
    * @author Matthew Boote
    *
    * @details Loads user database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    */
Driver::Driver() {
database=new Database();

database->Load(DATA_FOLDER_PATH + "Users.csv");			// load user information
}

 /*!
 *\file driver.cpp
    * 
    * FindNearestDriver()
    *
    * @brief Finds the nearest driver
    * 
    * @author Matthew Boote
    *
    * @details The function uses the driver database to find a driver in the same city, province and country.
    *
    * @param[in] std::string city,std::string province,std::string country
    * 
    * @param[out] None
    *
    * @return Driver object containing information about the driver
    *
    */
Driver Driver::FindNearestDriver(std::string city,std::string province,std::string country) {
std::vector<std::string> city_entry;
std::vector<std::string> driver_city;
Driver temp;

// Loop through drivers

do {

driver_city=database->Find();		// Get driver
// If driver near

 if( (driver_city[DATABASE_ENTRY_CITY].compare(city) == 0) && (driver_city[DATABASE_ENTRY_PROVINCE].compare(province) == 0)  && (driver_city[DATABASE_ENTRY_COUNTRY].compare(country) == 0) && (driver_city[DATABASE_ENTRY_USERTYPE].compare("Driver") == 0)) {
	// Create driver object
	   temp.SetUsername(driver_city[DATABASE_ENTRY_USERNAME]);
	   temp.SetPassword(driver_city[DATABASE_ENTRY_PASSWORD]);
	   temp.SetFirstname(driver_city[DATABASE_ENTRY_FIRSTNAME]);
	   temp.SetSurname(driver_city[DATABASE_ENTRY_SURNAME]);
	   temp.SetAddress(driver_city[DATABASE_ENTRY_ADDRESS]);
	   temp.SetCity(driver_city[DATABASE_ENTRY_CITY]);
	   temp.SetProvince(driver_city[DATABASE_ENTRY_PROVINCE]);
	   temp.SetPostcode(driver_city[DATABASE_ENTRY_POSTCODE]);
	   temp.SetPhone(driver_city[DATABASE_ENTRY_PHONE]);
	   temp.SetEmail(driver_city[DATABASE_ENTRY_EMAIL]);
	   temp.SetCountry(driver_city[DATABASE_ENTRY_COUNTRY]);
	   temp.SetRegistration(driver_city[DATABASE_ENTRY_REGISTRATION]);
	   temp.SetAccountType(driver_city[DATABASE_ENTRY_USERTYPE]);
	   temp.SetCPC(driver_city[DATABASE_ENTRY_CPC_NUMBER]);
	   temp.SetNINumber(driver_city[DATABASE_ENTRY_NINUMBER]);
	   return temp;
         } 

} while(driver_city.size() > 0);

return {};				// Return null on error
}

/*!
 *\file driver.cpp
    * 
    * SignUpAsDriver()
    *
    * @brief Signs up user as a driver
    * 
    * @authorzz Matthew Boote
    *
    * @details Reads user information from cargo owner object into database
    *
    * @param[in] Driver driver
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
bool Driver::SignUpAsDriver(Driver driver) {
 std::vector<std::string> driver_vector;

// driver_vector=database->Read(driver.GetUsername());	// check if username already exists
// if(driver_vector.size() != 0) return(false);		// user exists

 // database uses vector, because it's implementation-agnostic

 driver_vector.push_back(driver.GetUsername());
 driver_vector.push_back(driver.GetPassword());
 driver_vector.push_back(driver.GetFirstname());
 driver_vector.push_back(driver.GetSurname());
 driver_vector.push_back(driver.GetAddress());
 driver_vector.push_back(driver.GetCity());
 driver_vector.push_back(driver.GetProvince());
 driver_vector.push_back(driver.GetPostcode());
 driver_vector.push_back(driver.GetPhone());
 driver_vector.push_back(driver.GetEmail());
 driver_vector.push_back(driver.GetCountry());
 driver_vector.push_back("Driver");		// user type
 driver_vector.push_back(driver.GetRegistration());		// The registration of the vehicle associated with
 driver_vector.push_back(driver.GetNINumber());
 driver_vector.push_back(driver.DrivingLicenceID);
 driver_vector.push_back(driver.CPC);

// Add to driver database

 if(database->Write(driver.GetUsername(),driver_vector) == false) return(false);
 
 return true;
}

/*!
 *\file driver.cpp
    * 
    * GetRegistration()
    *
    * @brief Gets the vehicle registration
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string vehicleregistration
    *
    */
std::string Driver::GetRegistration(void) {
 return(vehicleregistration);
}

/*!
 *\file driver.cpp
    * 
    * SetRegistration()
    *
    * @brief Sets the vehicle registration
    * 
    * @author Matthew Boote
    *
    * @param[in] Driver driver
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
void Driver::SetRegistration(std::string reg) {
 vehicleregistration=reg;
}

/*!
 *\file driver.cpp
    * 
    * GetDrivingLicenceID()
    *
    * @brief Gets the driver's driving licence ID number
    * 
    * @author Matthew Boote
    *
    * @param[in] Driver driver
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
std::string Driver::GetDrivingLicenceID(void) {
 return(DrivingLicenceID);
}

/*!
 *\file driver.cpp
    * 
    * ValidateCPC()
    *
    * @brief Validates a driver's CPC number
    * 
    * @author Matthew Boote
    *
    * @details Checks the CPC format and looks up the number in the CPC database
    *
    * @param[in] Driver driver
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
bool Driver::ValidateCPC(std::string CPCNumber) {
int count=0;
Database CPCNumberDatabase;
std::vector<std::string> cpc_entry;
	
// https://www.ukdrivercpccourses.co.uk/Driver-Qualification-Card

// CPC number is in the format AANNNNNNNN
// where AA are two uppecase letters and NNNNNNNN are eight digits

 if(CPCNumber.length() < 10) return false;		// must be 10 characters long

 if((isupper(CPCNumber[0]) == 0) || (isupper(CPCNumber[1]) == 0)) return false;		// must have two uppercase digits at the start

// Must have eight dights following

 for(count=2;count<CPCNumber.length();count++) {
  if(isdigit(CPCNumber[count]) == 0) return false;			// invalid format
 }

// Search database for CPC number

 if(CPCNumberDatabase.Load(DATA_FOLDER_PATH + "CPCNumbers.csv") == false) return false;	// can't load database

 cpc_entry=CPCNumberDatabase.Read(CPCNumber);		// Find CPC number

 if(cpc_entry.size() == 0) return false;		// no entry found

 return true; 
}

/*!
 *\file driver.cpp
    * 
    * SetCPC()
    *
    * @brief Sets the driver's CPC number
    * 
    * @author Matthew Boote
    *  
    *
    * @param[in] Driver driver
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */
void Driver::SetCPC(std::string cpc) {
CPC=cpc;
}

std::string Driver::GetCPC(void) {
 return(CPC);
}

