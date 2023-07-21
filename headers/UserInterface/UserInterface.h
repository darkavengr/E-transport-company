#include <vector>

#define VECTOR_USERNAME	0
#define VECTOR_PASSWORD	1

#define MAX_ORDER_DISPLAY_COUNT 10
#define SHOW_ORDERS_HISTORY 1
#define SHOW_NEW_ORDERS 2

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

class UserInterface {
private:
  friend class DriverUserInterface;
  friend class CargoOwnerUserInterface;
  friend class TransportationCompanyUserInterface;

  std::string invalidcredentials="Invalid username or password";
  std::vector<std::string> goodstype = {"","Animals","Vehicles","Heavy equipment","Freight" };

public:
 UserInterface();
 std::vector<std::string> SignInUserInterface(void);
 std::string GetPassword(void);
 void DisplayTransactionHistory(std::string username);
};
#endif

