/** @file */ 
#include <string>
#include <sstream>
#include <math.h>

#include "user.h"
#include "transportationcompany.h"
#include "database.h"
#include "file_path.h"

/*!
 *\file transportationcompany.cpp
    * 
    * \class Transportation 
    * @brief Driver class
    * 
    * @author Matthew Boote
    *
    * @details This represents a transportation company.
    *
    */

 /*!
 *\file transportationcompany.cpp
    * 
    * TransportationCompany()
    * @brief TransportationCompany constructor
    * 
    * @author Matthew Boote
    *
    * @details Initializes transportation company object by loading Users database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    */
  
TransportationCompany::TransportationCompany() {
database=new Database();

database->Load( DATA_FOLDER_PATH + "Users.csv");			// load user information
}

/*!
 *\file transportationcompany.cpp
    * 
    * SignUpAsTransportation Company()
    *
    * @brief Signs up as a cargo owner
    * 
    * @author Matthew Boote
    *
    * @details Reads user information from cargo owner object into database
    *
    * @param[in] Transportation Company cargowner		Cargo owner object
    * 
    * @param[out] None
    *
    * @return Boolean true or false
    *
    */
bool TransportationCompany::SignUpAsTransportationCompany(TransportationCompany transportationcompany) {
 std::vector<std::string> transportationcompany_vector;

 transportationcompany_vector=database->Read(transportationcompany.GetUsername());	// check if username already exists
 if(transportationcompany_vector.size() != 0) return(false);		// user exists

 // database uses vector, because it's implementation-agnostic

 transportationcompany_vector.push_back(transportationcompany.GetUsername());
 transportationcompany_vector.push_back(transportationcompany.GetPassword());
 transportationcompany_vector.push_back(transportationcompany.GetCompanyName());
 transportationcompany_vector.push_back(transportationcompany.GetAddress());
 transportationcompany_vector.push_back(transportationcompany.GetCity());
 transportationcompany_vector.push_back(transportationcompany.GetPostcode());
 transportationcompany_vector.push_back(transportationcompany.GetPhone());
 transportationcompany_vector.push_back(transportationcompany.GetEmail());
 transportationcompany_vector.push_back(transportationcompany.GetCountry());
 transportationcompany_vector.push_back("TransportationCompany");		// user type

 if(database->Write(transportationcompany.GetUsername(),transportationcompany_vector) == false) return(false);
 
 return true;
}

/*!
 *\file transportationcompany.cpp
    * 
    * GetCompanyName()
    *
    * @brief Signs up as a transportation company
    * 
    * @author Matthew Boote
    *
    * @details Reads user information from transportation into database. This function is called from the sign up user interface.
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string CompanyName
    *
    */
std::string TransportationCompany::GetCompanyName(void) {
 return CompanyName;
}

/*!
 *\file transportationcompany.cpp
    * 
    * SetCompanyName()
    *
    * @brief Sets the company name
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string companyname
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void TransportationCompany::SetCompanyName(std::string companyname) {
 CompanyName=companyname;
}

/*!
 *\file transportationcompany.cpp
    * 
    * FindNearestTransportationCompany()
    *
    * @brief Finds the nearest transportation company
    * 
    * @author Matthew Boote
    *
    * @details Searches the database for a transportation company that is in the same city,province and country
    *
    * @param[in] std::string city,std::string province,std::string country
    * 
    * @param[out] None
    *
    * @return TransportationCompany object
    *
    */

TransportationCompany *TransportationCompany::FindNearestTransportationCompany(std::string city,std::string province,std::string country) {
    std::vector<std::string> TransportationCompany_city;
    TransportationCompany *temp=new TransportationCompany;

    do {

    TransportationCompany_city=database->Find();		// Get TransportationCompany
    if (TransportationCompany_city.size() == 0) {
        return NULL;
    }

    // If TransportationCompany near

     if( (TransportationCompany_city[DATABASE_ENTRY_CITY].compare(city) == 0) &&
             (TransportationCompany_city[DATABASE_ENTRY_PROVINCE].compare(province) == 0)  &&
             (TransportationCompany_city[DATABASE_ENTRY_COUNTRY].compare(country) == 0) &&
             (TransportationCompany_city[DATABASE_ENTRY_USERTYPE].compare("TransportationCompany") == 0)) {
        // Create TransportationCompany object
           temp->SetUsername(TransportationCompany_city[DATABASE_ENTRY_USERNAME]);
           temp->SetPassword(TransportationCompany_city[DATABASE_ENTRY_PASSWORD]);
           temp->SetFirstname(TransportationCompany_city[DATABASE_ENTRY_FIRSTNAME]);
           temp->SetSurname(TransportationCompany_city[DATABASE_ENTRY_SURNAME]);
           temp->SetAddress(TransportationCompany_city[DATABASE_ENTRY_ADDRESS]);
           temp->SetCity(TransportationCompany_city[DATABASE_ENTRY_CITY]);
           temp->SetProvince(TransportationCompany_city[DATABASE_ENTRY_PROVINCE]);
           temp->SetPostcode(TransportationCompany_city[DATABASE_ENTRY_POSTCODE]);
           temp->SetPhone(TransportationCompany_city[DATABASE_ENTRY_PHONE]);
           temp->SetEmail(TransportationCompany_city[DATABASE_ENTRY_EMAIL]);
           temp->SetCountry(TransportationCompany_city[DATABASE_ENTRY_COUNTRY]);
           temp->SetAccountType(TransportationCompany_city[DATABASE_ENTRY_USERTYPE]);
           return temp;
             }

    } while(TransportationCompany_city.size() > 0);

    return NULL;				// Return null on error
}

/*!
 *\file transportationcompany.cpp
    * 
    * SetGoodsTransportationType()
    *
    * @brief Sets the type of goods the transportation company transports.
    * 
    * @author Matthew Boote
    *
    *
    * @param[in] std::string GoodsType
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void TransportationCompany::SetGoodsTransportationType(std::string GoodsType) {
 goodstype=GoodsType;
}

/*!
 *\file transportationcompany.cpp
    * 
    * GetGoodsTransportationType()
    *
    * @brief Gets the type of goods the transportation company transports.
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string goodstype
    *
    */
std::string TransportationCompany::GetGoodsTransportationType(void) {
 return(goodstype);
}

