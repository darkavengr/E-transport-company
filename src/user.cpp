/*
 * user.c
 *
 * Methods and attributes common to both User, CargoOwner and Driver
 *
 * Matthew Boote and Adeeb Sait 
*/

/** @file */ 

#include <iostream>
#include <cstring>
#include <string>
#include "user.h"
#include "crypt.h"
#include "exception.h"
#include <stdio.h>

/*!
 *\file user.cpp
    * 
    * \class User
    * @brief User base class
    * 
    * @author Matthew Boote
    *
    * @details This represents a single user of the system.
    *
    */
 /*!
 *\file user.cpp
    * 
    * User()
    *
    * @brief User constructor
    * 
    * @author Matthew Boote
    *
    * @details Creates new database object
    *
    * @param[in] std::string cname		Company name
    * 
    * @param[out] None
    *
    * @return None
    *
    */
User::User() {
database=new Database();
}

 /*!
 *\file user.cpp
    * 
    * GetUsername()
    *
    * @brief Gets username
    * 
    * @author Matthew Boote
    *
    * @details Gets username attribute
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string company name
    *
    */
std::string User::GetUsername(void) {
 return(username);
}

 /*!
 *\file user.cpp
    * 
    * GetPassword()
    *
    * @brief Gets password 
    * 
    * @author Matthew Boote
    *
    * @details Gets password from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string password
    *
    */
std::string User::GetPassword(void) {
 return(password);
}

 /*!
 *\file user.cpp
    * 
    * GetFirstname()
    *
    * @brief Gets first name of user
    * 
    * @author Matthew Boote
    *
    * @details Gets first name from object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string firstname
    *
    */
std::string User::GetFirstname(void) {
 return(firstname);
}

 /*!
 *\file user.cpp
    * 
    * GetSurname()
    *
    * @brief Gets surname
    * 
    * @author Matthew Boote
    *
    * @details Gets surname from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string surname
    *
    */
std::string User::GetSurname(void) {
 return(surname);
}

 /*!
 *\file user.cpp
    * 
    * GetAddress()
    *
    * @brief Gets address
    * 
    * @author Matthew Boote
    *
    * @details Gets address from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string address
    *
    */
std::string User::GetAddress(void) {
 return(address);
}

 /*!
 *\file user.cpp
    * 
    * GetCity()
    *
    * @brief Gets city
    * 
    * @author Matthew Boote
    *
    * @details Gets city from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string city
    *
    */
std::string User::GetCity(void) {
 return(city);
}

 /*!
 *\file user.cpp
    * 
    * GetProvince()
    *
    * @brief Gets province
    * 
    * @author Matthew Boote
    *
    * @details Gets province from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string province
    *
    */
std::string User::GetProvince(void) {
 return(province);
}

 /*!
 *\file user.cpp
    * 
    * GetPostcode()
    *
    * @brief Gets postcode
    * 
    * @author Matthew Boote
    *
    * @details Gets postcode from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string postcode
    *
    */
std::string User::GetPostcode(void) {
 return(postcode);
}

 /*!
 *\file user.cpp
    * 
    * GetProvince()
    *
    * @brief Gets phone number
    * 
    * @author Matthew Boote
    *
    * @details Gets phone number from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string phonenumber
    *
    */
std::string User::GetPhone(void) {
 return(phone);
}

 /*!
 *\file user.cpp
    * 
    * GetEmail()
    *
    * @brief Gets email address
    * 
    * @author Matthew Boote
    *
    * @details Gets email address from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string email
    *
    */

std::string User::GetEmail(void) {
 return(email);
}

 /*!
 *\file user.cpp
    * 
    * GetCountry()
    *
    * @brief Gets user's country
    * 
    * @author Matthew Boote
    *
    * @details Gets country from user object
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string country
    *
    */
std::string User::GetCountry(void) {
 return(country);
}

 /*!
 *\file user.cpp
    * 
    * GetProvince()
    *
    * @brief Gets the type of account
    * 
    * @author Matthew Boote
    *
    * @details Gets the type of user (CargoOwner, Driver or TransportationCompany)
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string usertype
    *
    */
std::string User::GetAccountType(void) {
 return(usertype);
}

 /*!
 *\file user.cpp
    * 
    * SetUsername()
    *
    * @brief Sets the username
    * 
    * @author Matthew Boote
    *
    * @details Sets the username in the object
    *
    * @param[in] std::string username
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void User::SetUsername(std::string user) {
 username=user;
}

 /*!
 *\file user.cpp
    * 
    * SetPassword()
    *
    * @brief Sets the password
    * 
    * @author Matthew Boote
    *
    * @details Sets the password in the object
    *
    * @param[in] std::string password
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void User::SetPassword(std::string pass) {
 password=HashPassword(GetUsername(),pass);
}

 /*!
 *\file user.cpp
    * 
    * SetFirstname()
    *
    * @brief Sets the first name of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the first name in the object
    *
    * @param[in] std::string user
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetFirstname(std::string fname) {
 firstname=fname;
}

 /*!
 *\file user.cpp
    * 
    * SetSurname()
    *
    * @brief Sets the first name of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the first name in the object/
    *
    * @param[in] std::string sname
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetSurname(std::string sname) {
 surname=sname;
}

 /*!
 *\file user.cpp
    * 
    * SetAddress()
    *
    * @brief Sets the address of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the address in the object
    *
    * @param[in] std::string user
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void User::SetAddress(std::string addr) {
 address=addr;
}

 /*!
 *\file user.cpp
    * 
    * SetFirstname()
    *
    * @brief Sets the first name of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the first name in the object/
    *
    * @param[in] std::string user
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetPostcode(std::string pcode) {
 postcode=pcode;
}

 /*!
 *\file user.cpp
    * 
    * SetFirstname()
    *
    * @brief Sets the phone number of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the phone number in the object/
    *
    * @param[in] std::string phonenumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetPhone(std::string phonenumber) {
 phone=phonenumber;
}

 /*!
 *\file user.cpp
    * 
    * SetEmail()
    *
    * @brief Sets the email address of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the email address in the object/
    *
    * @param[in] std::string emailaddress
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetEmail(std::string emailaddress) {
 email=emailaddress;
}

 /*!
 *\file user.cpp
    * 
    * SetCity()
    *
    * @brief Sets the city of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the city in the object
    *
    * @param[in] std::string newcity
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetCity(std::string newcity) {
city=newcity;
}

 /*!
 *\file user.cpp
    * 
    * SetProvince()
    *
    * @brief Sets the province of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the province in the object
    *
    * @param[in] std::string newprovince
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetProvince(std::string newprovince) {
province=newprovince;
}

 /*!
 *\file user.cpp
    * 
    * SetCountry()
    *
    * @brief Sets the country of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the country in the object
    *
    * @param[in] std::string state
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetCountry(std::string state) {
 country=state;
}

 /*!
 *\file user.cpp
    * 
    * SetAccountType()
    *
    * @brief Sets the account type of the user
    * 
    * @author Matthew Boote
    *
    * @details Sets the account type (CargoOwner, Driver, TransportationCompany)
    *
    * @param[in] std::string atype
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetAccountType(std::string atype) {
 usertype=atype;
}

<<<<<<< HEAD
 /*!
 *\file user.cpp
    * 
    * SignIn()
    *
    * @brief Signs in a user
    * 
    * @author Matthew Boote
    *
    * @details SignIn user reads the user account details from the user database, and compares them to the username and password. If the username and password match, it loads the information into the object.
    *
    * @param[in] std::string user
    * 
    * @param[out] None
    *
    * @return true or false
    *
    */

bool User::SignIn(std::string user,std::string password) {
 std::vector<std::string> User_vector;
 std::string encryptedpassword;
 
 User_vector=database->Read(user);

 if(User_vector.size() == 0) return(false);
 
 encryptedpassword=HashPassword(user,pass);			// hash password

 if(User_vector[DATABASE_ENTRY_PASSWORD].compare(encryptedpassword) != 0) return(false);		// check password

// Get information from vector into object

  username=User_vector[DATABASE_ENTRY_USERNAME];
  password = User_vector[DATABASE_ENTRY_PASSWORD];
  firstname=User_vector[DATABASE_ENTRY_FIRSTNAME];
  surname=User_vector[DATABASE_ENTRY_SURNAME];
  address=User_vector[DATABASE_ENTRY_ADDRESS];
  city=User_vector[DATABASE_ENTRY_CITY];
  province=User_vector[DATABASE_ENTRY_PROVINCE];
  postcode=User_vector[DATABASE_ENTRY_POSTCODE];
  phone=User_vector[DATABASE_ENTRY_PHONE];
  email=User_vector[DATABASE_ENTRY_EMAIL];
  country=User_vector.size() > DATABASE_ENTRY_COUNTRY ? User_vector[DATABASE_ENTRY_COUNTRY] : "";
  usertype=User_vector.size() > DATABASE_ENTRY_USERTYPE ?User_vector[DATABASE_ENTRY_USERTYPE] : "";
  CPC=User_vector.size() > DATABASE_ENTRY_CPC ? User_vector[DATABASE_ENTRY_CPC] : "";
  NINumber=User_vector.size() > DATABASE_ENTRY_NINUMBER ? User_vector[DATABASE_ENTRY_NINUMBER] : "";
  vehicleregistration=User_vector.size() > DATABASE_ENTRY_REGISTRATION ? User_vector[DATABASE_ENTRY_REGISTRATION] : "";

 return(true);
}

 /*!
 *\file user.cpp
    * 
    * SignOut()
    *
    * @brief Signs the user out
    * 
    * @author Matthew Boote
    *
    * @details Signs the user out
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return boolean
    *
    */

bool User::SignOut(void) {
 if(IsSignedIn == false) return(false);		// not signed in

 IsSignedIn=false;

 return(true);
}

 /*!
 *\file user.cpp
    * 
    * HashPassword
    *
    * @brief Hashes the password
    * 
    * @author Matthew Boote
    *
    * @details The function hash the password with the UNIX crypt() function using the username as the salt. It converts the salt and password to char *, hashes the password and converts it back
    *
    * @param[in] std::string salt,std::string password
    * 
    * @param[out] None
    *
    * @return None
    *
    */

std::string User::HashPassword(const std::string& salt,const std::string& password) {
 char result[255];
 std::string strr;

 std::string user=salt.substr(0,2);

 strcpy(result,crypt(password.c_str(),user.c_str()));

 strr=std::string(result);
 return strr;
}

 /*!
 *\file user.cpp
    * 
    * SetNINumber()
    *
    * @brief Sets the National Insurance number of the user
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string ni
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void User::SetNINumber(std::string ni) {
 NINumber=ni;
}
 /*!
 *\file user.cpp
    * 
    * GetNINumber()
    *
    * @brief Sets the National Insurance number
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string user
    * 
    * @param[out] None
    *
    * @return None
    *
    */


std::string User::GetNINumber(void) {
 return(NINumber);
}


