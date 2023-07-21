/*
 * transaction.h
 *
 *  Created on: 18 Feb 2022
 *      Author: Matthew Boote
 */

#include <string>
#include <sstream>
#include <vector>

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include "database.h"
#include "driver.h"

using namespace boost::uuids;

#define TRANSACTION_VECTOR_ID			0
#define TRANSACTION_VECTOR_SENDER_USERNAME	1
#define TRANSACTION_VECTOR_RECIPIENT_USERNAME	2
#define TRANSACTION_VECTOR_FIRSTNAME		3
#define TRANSACTION_VECTOR_SURNAME		4
#define TRANSACTION_VECTOR_DELIVERYADDRESS	5
#define TRANSACTION_VECTOR_CITY			6
#define TRANSACTION_VECTOR_PROVINCE		7
#define TRANSACTION_VECTOR_POSTCODE		8
#define TRANSACTION_VECTOR_COUNTRY		9
#define TRANSACTION_VECTOR_PHONE		10
#define TRANSACTION_VECTOR_EMAIL		11
#define TRANSACTION_VECTOR_PRIORITY		12
#define TRANSACTION_VECTOR_TOTALCOST		13
#define TRANSACTION_VECTOR_WEIGHT		14
#define TRANSACTION_VECTOR_DESCRIPTION		15
#define TRANSACTION_VECTOR_COMMENTS		16
#define TRANSACTION_VECTOR_GOODSTYPE		17
#define TRANSACTION_VECTOR_STATUS		18

#define CITY_CITY	0
#define	CITY_LATITUDE	2
#define	CITY_LONGITUDE	3
#define CITY_PROVINCE   7
#define CITY_COUNTRY	4


#define COST_PER_DISTANCE	1.10
#define COST_PER_GRAM		1.40

#define COMISSION_PERCENTAGE_DECIMAL 0.10
#define COMISSION_PERCENTAGE_DRIVER_DECIMAL 0.70
#define COMISSION_PERCENTAGE_TRANSPORTATON_COMPANY_DECIMAL 0.30

class Transaction {
 private:
  Database *TransactionDatabase;

  uuid ID;
  std::string Firstname;
  std::string Surname;
  std::string DeliveryAddress;
  std::string City;
  std::string Province;
  std::string PostCode;
  std::string Country;
  std::string ContactPhone;
  std::string ContactEmail;
  std::string ItemDescription;
  std::string GoodsType;
  double ItemWeight;		
  int priority;
  double TotalCost;
  std::string sender;
  std::string Comments;
  std::string RecipientUsername;
  std::string Status;
  std::string DriverName;
 public:
  Transaction(std::string transactionfilename);
  uuid GetID(void);
  std::string GetUsername(void);
  std::string GetFirstname(void);
  std::string GetSurname(void);
  std::string GetDeliveryAddress(void);
  std::string GetPostCode(void);
  std::string GetContactPhone(void);
  std::string GetContactEmail(void);
  std::string GetRecipientUsername(void);
  std::string GetProvince(void);
  std::string GetCity(void);
  std::string GetComments(void);	
  std::string GetCountry(void);
  std::string GetSender(void);
  std::string GetDescription(void);
  std::string GetGoodsType(void);
  
  int GetPriority(void);
  double GetTotalCost(void);
  double GetWeight(void);
  std::string GetItemDescription(void);
  void SetID(uuid id);
  void GenerateID(void);
  void SetSender(std::string uname);
  void SetFirstname(std::string firstname);
  void SetSurname(std::string surname);
  void SetDeliveryAddress(std::string address);
  void SetPostCode(std::string pcode);
  void SetContactPhone(std::string pnumber);
  void SetContactEmail(std::string email);
  void SetPriority(int pri);
  double GetItemWeight(void);
  void SetTotalCost(double cost);
  void SetWeight(double w);
  void SetDescription(std::string desc);
  void SetComments(std::string comments);
  void SetGoodsType(std::string type);
  bool CancelTransaction(uuid orderid);
  bool Pay(int PIN,int SortCode);
  bool PlaceOrder(std::string senderusername,std::string sendercity,std::string senderprovince,std::string sendercountry);
  void SetRecipientUsername(std::string username);
  void GetProvince(std::string province);
  void SetProvince(std::string province);
  void SetCity(std::string city);
  void SetCountry(std::string country);
  bool ChangeStatus(uuid orderid,std::string status);
  bool FindNextTransaction(void);
  double CalculateShippingRates();
  double CalculateCostOfDelivery();
  std::vector<double> GetLocation(void);
 double CalculateCommission();	
 void SetDriverName(std::string drivername);
 std::string GetDriverName(void);
};

#endif /* TRANSACTION_H_ */

