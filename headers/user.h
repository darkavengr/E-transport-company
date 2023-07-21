/*
 * user.h
 *
 *  Created on: 18 Feb 2022
 *      Author: Matthew Boote
 */

#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

#include "database.h"

#ifndef USER_H_
#define USER_H_

#define DATABASE_ENTRY_USERNAME		0
#define DATABASE_ENTRY_PASSWORD 	1
#define DATABASE_ENTRY_FIRSTNAME	2
#define DATABASE_ENTRY_SURNAME		3
#define DATABASE_ENTRY_ADDRESS		4
#define DATABASE_ENTRY_CITY		5
#define DATABASE_ENTRY_PROVINCE		6
#define DATABASE_ENTRY_POSTCODE		7
#define DATABASE_ENTRY_PHONE		8
#define DATABASE_ENTRY_EMAIL		9
#define DATABASE_ENTRY_COUNTRY		10
#define DATABASE_ENTRY_USERTYPE		11
#define DATABASE_ENTRY_CPC		12
#define DATABASE_ENTRY_NINUMBER		13
#define DATABASE_ENTRY_REGISTRATION	14



#define USER_CARGO_OWNER		0
#define USER_DRIVER			1
#define USER_TRANSPORTATIONCOMPANY	2

class User {
 private:
  friend class Driver;
  friend class CargoOwner;
  friend class TransportationCompany;
  Database *database;
  std::string username;
  std::string password;
  std::string firstname;
  std::string surname;
  std::string address;
  std::string city;
  std::string province;
  std::string postcode;
  std::string phone;
  std::string email;
  std::string country;
  std::string usertype;
  std::string NINumber;
  std::string DrivingLicenceID;
  std::string vehicleregistration;
  std::string CPC;
  std::string goodstype;
  bool IsSignedIn;

public:
  User();
  std::string GetUsername(void);
  std::string GetPassword(void);
  std::string GetFirstname(void);
  std::string GetSurname(void);
  std::string GetAddress(void);
  std::string GetPostcode(void);
  std::string GetPhone(void);
  std::string GetEmail(void);
  std::string GetCountry(void);
  std::string GetCity(void);
  std::string GetProvince(void);
  void SetUsername(std::string user);
  void SetPassword(std::string pass);
  void SetFirstname(std::string fname);
  void SetSurname(std::string sname);
  void SetAddress(std::string addr);
  void SetCity(std::string newcity);
  void SetPostcode(std::string pcode);
  void SetPhone(std::string phonenumber);
  void SetEmail(std::string emailaddress);
  void SetCountry(std::string state);
  std::string GetAccountType(void);
  void SetAccountType(std::string atype);
  void SetProvince(std::string newprovince);
  bool SignIn(const std::string& username,const std::string& password);
  bool SignOut(void);
  std::string HashPassword(const std::string& salt,const std::string& password);
  bool UpdateUserDatabase(std::string db,std::string username,std::vector<std::string> userinformation);
  void SetNINumber(std::string ni);
  std::string GetNINumber(void);
};


#endif /* USER_H_ */

