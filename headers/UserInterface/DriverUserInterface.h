#include "UserInterface.h"
#include "driver.h"

class DriverUserInterface : UserInterface {
 private:
  Driver driver;

 public:
  void MainMenu();
  void DriverSignUpInterface(void);
  bool AcceptOrder(Database database,uuid ordernumber);
  bool RejectOrder(Database database,uuid ordernumber);
  int TransactionActions(int ordernumber);
  void DisplayTransactions(void);
};

