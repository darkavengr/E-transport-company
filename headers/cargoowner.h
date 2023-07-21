/*
 * cargoowner.h
 *
 *  Created on: 18 Feb 2022
 *      Author: Matthew Boote
 */

#include <string>
#include <sstream>

#ifndef CARGOOWNER_H_
#define CARGOOWNER_H_
#include "user.h"

class CargoOwner : public User {			// CargoOwner is based on User
 private:
  std::string companyname;

 public:
  CargoOwner();
  bool SignUpAsCargoOwner(CargoOwner cargowner);
  bool FindNearestCargoOwner(int distance,CargoOwner cargo);
  std::string GetCompanyName(void);
  void SetCompanyName(std::string cname);
  bool ViewTransactionHistory(void);
};

#endif /* CARGOOWNER_H_ */

