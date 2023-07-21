#include "UserInterface.h"
#include "cargoowner.h"

#ifndef CARGOOWNER_USERINTERFACE_H_
#define CARGOOWNER_USERINTERFACE_H_

#define SHOW_ORDERS_HISTORY 1
#define SHOW_NEW_ORDERS	2

class CargoOwnerUserInterface : UserInterface {
private:
    CargoOwner cargoowner;

public:
    void MainMenu();
    void CargoOwnerSignUpInterface(void);
    void CargoOwnerPlaceOrderInterface(void);
    int RejectOrder(int ordernumber);
    int AcceptOrder(int ordernumber);
    int TransactionActions(int ordernumber);
    void TransactionInterface(void);
    void TransactionInterfaceUi(CargoOwner cargoOwner_,
                                std::string recipientName,
                                int goodsType,
                                std::string firstName,
                                std::string lastName,
                                std::string address,
                                std::string city,
                                std::string province,
                                std::string postcode,
                                std::string country,
                                std::string phone,
                                int priority,
                                std::string email,
                                double weight,
                                std::string comments,
                                std::string description);
};
#endif


