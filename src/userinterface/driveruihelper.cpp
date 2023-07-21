#include "driveruihelper.h"


#include "user.h"
#include "transaction.h"
#include "transportationcompany.h"
#include "database.h"
#include "DriverUserInterface.h"
#include "MessageInterface.h"
#include "vehicle.h"
#include "file_path.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QString>

DriverUIHelper::DriverUIHelper(Driver* driver)
{
    this->driver = driver;
}

void DriverUIHelper::populateTableView(QTableWidget* tableWidget) {
    tableWidget->clearContents();

    int count = 0;
    std::string filename;
    Database transactiondatabase;
    int display_count=0;
    std::string orderID;
    std::string choice;
    std::string newstatus;

    filename=DATA_FOLDER_PATH + driver->GetUsername()+"_transactions.csv";

    Transaction transaction(filename);

    while(transaction.FindNextTransaction() == true) {
        tableWidget->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(
                                                                boost::uuids::to_string(transaction.GetID()))));

        tableWidget->setItem(count, 1, new QTableWidgetItem(QString::fromStdString(transaction.GetSender())));
        tableWidget->setItem(count, 2, new QTableWidgetItem(QString::fromStdString(transaction.GetFirstname() + " " + transaction.GetSurname() )));
        tableWidget->setItem(count, 3, new QTableWidgetItem(QString::number(transaction.GetTotalCost())));
        tableWidget->setItem(count, 4, new QTableWidgetItem(QString::number(transaction.GetTotalCost()  *  COMISSION_PERCENTAGE_DRIVER_DECIMAL)));
        tableWidget->setItem(count, 5, new QTableWidgetItem(QString::fromStdString(transaction.GetDeliveryAddress())));
        tableWidget->setItem(count, 6, new QTableWidgetItem(QString::fromStdString(transaction.GetPostCode())));
        tableWidget->setItem(count, 7, new QTableWidgetItem(QString::fromStdString(transaction.GetCountry())));
        tableWidget->setItem(count, 8, new QTableWidgetItem(QString::fromStdString(transaction.GetContactPhone())));
        tableWidget->setItem(count, 9, new QTableWidgetItem(QString::fromStdString(transaction.GetContactEmail())));
        tableWidget->setItem(count, 10, new QTableWidgetItem(QString::fromStdString(transaction.GetDescription())));
        tableWidget->setItem(count, 11, new QTableWidgetItem(QString::number(transaction.GetItemWeight() )));
        tableWidget->setItem(count, 12, new QTableWidgetItem(QString::fromStdString(transaction.GetGoodsType())));
        tableWidget->setItem(count, 13, new QTableWidgetItem(QString::fromStdString( transaction.GetComments())));
    }
}
