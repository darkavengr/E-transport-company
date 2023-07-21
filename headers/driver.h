/*
 * driver.h
 *
 *  Created on: 18 Feb 2022
 *      Author: Matthew Boote
 */

#include <string>
#include <sstream>

#include "user.h"
#include "transaction.h"

#ifndef DRIVER_H_
#define DRIVER_H_

#define DATABASE_ENTRY_NINUMBER		11
#define DATABASE_ENTRY_REGISTRATION	12
#define DATABASE_ENTRY_CPC_NUMBER	13

class Driver : public User {			// Driver is based on User
 private:

 public:
  Driver();
  std::vector<int> GetCurrentPosition(void);
  bool SignUpAsDriver(Driver DriverInformation);
  Driver FindNearestDriver(std::string city,std::string province,std::string country);
  bool SignInAsDriver(std::string username,std::string password);
  std::string GetRegistration(void);
  void SetRegistration(std::string reg);
  std::string GetDrivingLicenceID(void);
  int AcceptOrder(int ordernumber);
  int RejectOrder(int ordernumber);
  bool DriverViewTransactionHistory(void);
  bool ValidateCPC(std::string CPCNumber);
  void SetCPC(std::string cpc);
  std::string GetCPC(void);
};

#endif /* DRIVER_H_ */

