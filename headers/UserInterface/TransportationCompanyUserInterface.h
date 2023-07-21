#include "transportationcompany.h"
#include "UserInterface.h"

class TransportationCompanyUserInterface : UserInterface {

private:
 TransportationCompany transportationcompany;

public:
 void MainMenu();
 void SignInInterface(void);
 void SignUpInterface(void);
 void DisplayOrders(void);
 int DispatchOrder(Database database,std::string ordernumber);
 int CancelOrder(Database database,std::string ordernumber);
 int TransactionActions(Database database,std::string ordernumber);

 
};
