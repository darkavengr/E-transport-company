/*
/* cargoowner.cpp
/*
/* Author: Adeeb Sait and Matthew Boote
*/

/** @file */ 
#include <iostream>

#include "cargoowner.h"
#include "database.h"
#include "file_path.h"


/*!
 *\file vehicle.cppfile cargoowner.cpp
    * 
    * \class CargoOwner
    * @brief CargoOwner class
    * 
    * @author Matthew Boote
    *
    * @details This represents a cargo owner.
    *
    */

  /*!
 *\file vehicle.cppfile cargoowner.cpp
    * 
    * CargoOwner()
    * @brief CargoOwner constructor
    * 
    * @author Matthew Boote
    *
    * @details Initializes cargo owner object by loading Users database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    * @throw General exception  
    */
  
std::string encrypt(std::string pw, std::string salt);

// Constructor
CargoOwner::CargoOwner() {

database->Load(DATA_FOLDER_PATH + "Users.csv");			// load user information

}

 /*!
 *\file vehicle.cppfile cargoowner.cpp
    * 
    * SignUpAsCargoOwner()
    *
    * @brief Signs up as a cargo owner
    * 
    * @author Matthew Boote
    *
    * @details Reads user information from cargo owner object into database
    *
    * @param[in] CargoOwner cargowner		Cargo owner object
    * 
    * @param[out] None
    *
    * @return Boolean true or false
    *
    */
bool CargoOwner::SignUpAsCargoOwner(CargoOwner cargoowner) {
 std::vector<std::string> CargoOwner_vector;

 CargoOwner_vector=database->Read(cargoowner.GetUsername());		// check if username already exists
 if(CargoOwner_vector.size() != 0) return(false);		// user exists

 // database uses vector, because it's implementation-agnostic
 CargoOwner_vector.push_back(cargoowner.GetUsername());
 CargoOwner_vector.push_back(cargoowner.GetPassword());
 CargoOwner_vector.push_back(cargoowner.GetFirstname());
 CargoOwner_vector.push_back(cargoowner.GetSurname());
 CargoOwner_vector.push_back(cargoowner.GetAddress());
 CargoOwner_vector.push_back(cargoowner.GetCity());
 CargoOwner_vector.push_back(cargoowner.GetProvince());
 CargoOwner_vector.push_back(cargoowner.GetPostcode());
 CargoOwner_vector.push_back(cargoowner.GetPhone());
 CargoOwner_vector.push_back(cargoowner.GetEmail());
 CargoOwner_vector.push_back(cargoowner.GetCountry());
 CargoOwner_vector.push_back("Cargo Owner");		// user type

// Add to CargoOwner database

 if(database->Write(cargoowner.GetUsername(),CargoOwner_vector) == false) return(false);
 
 return true;
}

 /*!
 *\file vehicle.cppfile cargoowner.cpp
    * 
    * GetCompanyName()
    *
    * @brief Gets company name
    * 
    * @author Matthew Boote
    *
    * @details Returns company name
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return Company name
    *
    */
std::string CargoOwner::GetCompanyName(void) {
 return(companyname);
}

 /*!
 *\file vehicle.cppfile cargoowner.cpp
    * 
    * SetCompanyName()
    *
    * @brief Sets company name
    * 
    * @author Matthew Boote
    *
    * @details Sets company name attribute
    *
    * @param[in] std::string cname		Company name
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void CargoOwner::SetCompanyName(std::string cname) {
 companyname=cname;
}


