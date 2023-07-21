#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlineedit.h"
#include <QMainWindow>

#include <transportationcompany.h>
#include <driver.h>
#include <cargoowner.h>
#include <driveruihelper.h>
#include <transportcompanyuihelper.h>
#include <cargoowneruihelper.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    const int welcomeScreen = 0;
    const int loginOrRegister = 1;
    const int customerRegistrationScreen = 2;
    const int driverRegistrationScreen = 3;
    const int transportRegistrationScreen = 4;
    const int loginScreen = 5;
    const int customerProfileScreen = 6;
    const int driverProfileScreen = 7;
    const int transportProfileScreen = 8;
    const int placeOrderScreen = 9;
    const int driverDisplayOrder = 10;
    const int driverOrderHistory = 11;
    const int transportDisplayOrder = 12;
    const int customerViewOrderScreen = 13;
    const int sendMessageScreen = 14;
    const int replyMessageScreen = 15;
    const int viewMessageScreen = 16;

    enum USER_TYPE {
        NONE,
        CUSTOMER,
        DRIVER,
        TRANSPORT_COMPANY
    };

    USER_TYPE selected_user_type = NONE;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectCustomer_clicked();

    void on_selectDriver_clicked();

    void on_selectTransport_clicked();

    void on_loginPageBackButtton_clicked();

    void on_loginButton_clicked();

    void on_backFromLoginButton_clicked();

    void on_driverRegistrationConfirm_clicked();

    void on_driverRegistrationBack_clicked();

    void on_customerRegistrationConfirm_clicked();

    void on_customerRegistrationBack_clicked();

    void on_transportRegistrationBackButton_clicked();

    void on_transportRegistrationConfirmationButton_clicked();

    void on_loginChosenButton_clicked();

    void on_registerButton_clicked();

    void on_placeOrderBackButton_clicked();

    void on_placeOrderConfirmButton_clicked();

    void on_customerProfilePlaceOrder_clicked();

    void on_customerSignOut_clicked();

    void on_driverSignOutButton_clicked();

    void on_transportProfileSIgnOut_clicked();

    void on_driverCurrentOrders_clicked();

    void on_driverOrderHistory_clicked();

    void on_driverDisplayOrderChangeStatus_clicked();

    void on_driverDisplayOrderBack_clicked();

    void on_driverOrderHistoryBackButton_clicked();

    void on_transportDisplayOrderBackButton_clicked();

    void on_transportCancelOrder_clicked();

    void on_transportDispatchOrder_clicked();

    void on_transportProfileDisplayOrders_clicked();

    void on_customerProfileOrderHistory_clicked();


    void on_customerViewOrdersBakc_clicked();

    void on_pushButton_clicked();

    void on_sendMessageBackButton_clicked();

    void on_sendMessageButton_clicked();

    void on_viewMessageBackButton_clicked();

    void on_replyMessageBack_clicked();

    void on_customerProfileViewMsg_clicked();

    void on_customerProfileSendMsg_clicked();

    void on_driverViewMessages_clicked();

    void on_driverSendMessage_clicked();

    void on_transportProfileViewMsg_clicked();

    void on_transportProfileSendMsg_clicked();

    void on_viewMessageReply_clicked();

private:
    Ui::MainWindow *ui;

    TransportationCompany transportationcompany;
    CargoOwner cargoowner;
    Driver driver;
    DriverUIHelper driverUIHelper;
    TransportCompanyUIHelper transportUIHelper;
    CargoOwnerUIHelper cargoOwnerUIHelper;

    void initialize();
    User* getUser();

    bool registerCustomer();
    bool registerTransportCompany();
    bool registerDriver();

    void showProfilePage();

    bool isNotEmpty(const QLineEdit* lineEdit,
                    const std::string& fieldName);
    bool areFieldsEqual(const QLineEdit* lineEdit1, const QLineEdit* lineEdit2,
                        const std::string& errorMessage);
};
#endif // MAINWINDOW_H
