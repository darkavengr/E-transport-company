#ifndef DRIVERUIHELPER_H
#define DRIVERUIHELPER_H

#include <driver.h>

class QTableWidget;

class DriverUIHelper
{
private:
 Driver* driver;

public:
    DriverUIHelper(Driver* driver);

    void populateTableView(QTableWidget* tableWidget);
};

#endif // DRIVERUIHELPER_H
