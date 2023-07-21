
#include <string>
#define SHOW_ORDERS_HISTORY 1
#define SHOW_NEW_ORDERS     2

#define MAX_ORDER_DISPLAY_COUNT  10

void SignUpInterface(void);
void SignInInterface(void);
void MainMenu(void);
void TransactionInterface(int type);
void DisplayTransactions(int type);
int TransactionActions(int ordernumber);
int AcceptOrder(int ordernumber);
int RejectOrder(int ordernumber);
void exception_handler(std::string message);

