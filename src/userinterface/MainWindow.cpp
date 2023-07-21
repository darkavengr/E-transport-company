#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <vehicle.h>

#include <QMessageBox>

#include <CargoOwnerUserInterface.h>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , driverUIHelper(&driver)
    , transportUIHelper(&transportationcompany)
    , cargoOwnerUIHelper(&cargoowner)
{
    ui->setupUi(this);

    ui->driverVehicleHeight->setValidator(new QDoubleValidator(ui->driverVehicleHeight));
    ui->driverVehicleWeight->setValidator(new QDoubleValidator(ui->driverVehicleWeight));
    ui->placeOrderWeight->setValidator(new QDoubleValidator(ui->placeOrderWeight));
    initialize();
}

void MainWindow::initialize() {
    ui->stackedWidget->setCurrentIndex(welcomeScreen);
    selected_user_type = NONE;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectCustomer_clicked()
{
    selected_user_type = CUSTOMER;
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}


void MainWindow::on_selectDriver_clicked()
{
    selected_user_type = DRIVER;
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}


void MainWindow::on_selectTransport_clicked()
{
    selected_user_type = TRANSPORT_COMPANY;
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}

void MainWindow::on_loginPageBackButtton_clicked()
{
    ui->stackedWidget->setCurrentIndex(welcomeScreen);
}

void MainWindow::on_loginButton_clicked()
{
    qInfo() <<"Logging in";

    User* user = getUser();
    if (user->SignIn(ui->loginUsername->text().toStdString(),
                     ui->loginPassword->text().toStdString()) == false) {
        QMessageBox::critical(this, "Login Error", "Invalid username or password");

    } else {
        showProfilePage();
        ui->loginPassword->clear();
        ui->loginUsername->clear();
    }

    return;
}

void MainWindow::showProfilePage() {
    switch (selected_user_type) {
            case CUSTOMER:
                ui->stackedWidget->setCurrentIndex(customerProfileScreen);
                //cargoowner.SetUsername(ui->loginUsername->text().toStdString());
                break;
            case TRANSPORT_COMPANY:
                ui->stackedWidget->setCurrentIndex(transportProfileScreen);
                //transportationcompany.SetUsername(ui->loginUsername->text().toStdString());
                break;
            case DRIVER:
                ui->stackedWidget->setCurrentIndex(driverProfileScreen);
                //driver.SetUsername(ui->loginUsername->text().toStdString());
                break;
            default:
                break;
            }
}


void MainWindow::on_backFromLoginButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}

void MainWindow::on_customerRegistrationConfirm_clicked()
{
    qInfo() << "Customer User Registered" ;
    if (registerCustomer()) {
        ui->stackedWidget->setCurrentIndex(loginOrRegister);
    }
}


void MainWindow::on_customerRegistrationBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}

void MainWindow::on_driverRegistrationConfirm_clicked()
{
    qInfo() << "Driver User Registered" ;
    if (registerDriver()) {
        ui->stackedWidget->setCurrentIndex(loginOrRegister);
    }
}


void MainWindow::on_driverRegistrationBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}

void MainWindow::on_transportRegistrationBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginOrRegister);
}


void MainWindow::on_transportRegistrationConfirmationButton_clicked()
{
    qInfo() << "Transport User Registered" ;
    if (registerTransportCompany()) {
        ui->stackedWidget->setCurrentIndex(loginOrRegister);
    }
}


void MainWindow::on_loginChosenButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(loginScreen);
}


void MainWindow::on_registerButton_clicked()
{
    switch (selected_user_type) {
    case CUSTOMER:
        ui->stackedWidget->setCurrentIndex(customerRegistrationScreen);
        break;
    case TRANSPORT_COMPANY:
        ui->stackedWidget->setCurrentIndex(transportRegistrationScreen);
        break;
    case DRIVER:
        ui->stackedWidget->setCurrentIndex(driverRegistrationScreen);
        break;
    default:
        break;
    }

}


void MainWindow::on_placeOrderBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(customerProfileScreen);
}


void MainWindow::on_placeOrderConfirmButton_clicked()
{
    qInfo() << "Customer placed an order";
    CargoOwnerUserInterface cIface;

    bool ok;
    double itemWeight = ui->placeOrderWeight->text().toDouble(&ok);
    std::string recipientName = ui->placeOrderRecipientName->text().toStdString();

    /*cIface.TransactionInterfaceUi(cargoowner, "GKName",
                                  1,
                                  "GKName", "GKName",
                                  "MyAddress",
                                  "Nottingham",
                                  "Nottingham",
                                  "55555",
                                  "United Kingdom",
                                  "1234",
                                  1,
                                  "mytest@gmail.com",
                                  1.0,
                                  "MyComment",
                                  "MyComment");*/

    cIface.TransactionInterfaceUi(cargoowner, recipientName,
                                  ui->placeOrderTypeOfGoods->currentIndex(),
                                  recipientName, recipientName,
                                  ui->placeOrderRecipientAddress->text().toStdString(),
                                  ui->placeOrderCity->text().toStdString(),
                                  ui->placeOrderProvince->text().toStdString(),
                                  ui->placeOrderPostCode->text().toStdString(),
                                  ui->placeOrderCountry->text().toStdString(),
                                  ui->placeOrderPhoneNumber->text().toStdString(),
                                  ui->placeOrderShippingPriority->currentIndex(),
                                  ui->placeOrderEmail->text().toStdString(),
                                  itemWeight,
                                  ui->placeOrderAdditionalComments->text().toStdString(),
                                  ui->placeOrderAdditionalComments->text().toStdString());
    QMessageBox::information(this, "Order", "Order Placed successfully");
}


void MainWindow::on_customerProfilePlaceOrder_clicked()
{
    ui->stackedWidget->setCurrentIndex(placeOrderScreen);
}


void MainWindow::on_customerSignOut_clicked()
{
    initialize();
}

User* MainWindow::getUser() {
    switch (selected_user_type) {
    case CUSTOMER:
        return &cargoowner;
    case TRANSPORT_COMPANY:
        return &transportationcompany;
    case DRIVER:
        return &driver;
    default:
        return 0;
    }
}


void MainWindow::on_driverSignOutButton_clicked()
{
    initialize();
}


void MainWindow::on_transportProfileSIgnOut_clicked()
{
    initialize();
}


bool MainWindow::registerCustomer() {
    if (isNotEmpty(ui->customerFirstName, "first name") &&
            isNotEmpty(ui->customerLastName, "last name") &&
            isNotEmpty(ui->customerUserName, "user name") &&
            isNotEmpty(ui->customerAddress, "address") &&
            isNotEmpty(ui->customerCityField, "city") &&
            isNotEmpty(ui->customerProvince, "province") &&
            isNotEmpty(ui->customerCountry, "country") &&
            isNotEmpty(ui->customerPostCode, "postcode") &&
            isNotEmpty(ui->customerPhone, "phone") &&
            isNotEmpty(ui->customerEmail, "email") &&
            isNotEmpty(ui->customerPassword, "password") &&
            areFieldsEqual(ui->customerPassword, ui->customerPasswordConfirmation, "Passwords do not match")) {
        cargoowner.SetFirstname(ui->customerFirstName->text().toStdString());
        cargoowner.SetSurname(ui->customerLastName->text().toStdString());
        cargoowner.SetAddress(ui->customerAddress->text().toStdString());
        cargoowner.SetCity(ui->customerCityField->text().toStdString());
        cargoowner.SetProvince(ui->customerProvince->text().toStdString());
        cargoowner.SetCountry(ui->customerCountry->text().toStdString());
        cargoowner.SetPostcode(ui->customerPostCode->text().toStdString());
        cargoowner.SetPhone(ui->customerPhone->text().toStdString());

        cargoowner.SetEmail(ui->customerEmail->text().toStdString());
        cargoowner.SetUsername(ui->customerUserName->text().toStdString());
        cargoowner.SetPassword(ui->customerPassword->text().toStdString());

        if(cargoowner.SignUpAsCargoOwner(cargoowner) == true) {
            QMessageBox::information(this, "Registration", "Registered successfully");
            return true;
        }

    }
    return false;
}

bool MainWindow::registerTransportCompany() {
    if (isNotEmpty(ui->transportEmail, "email") &&
            isNotEmpty(ui->transportPassword, "password") &&
            isNotEmpty(ui->transportCompanyName, "company name") &&
            isNotEmpty(ui->transportAddress, "address") &&
            isNotEmpty(ui->transportCity, "city") &&
            isNotEmpty(ui->transportCountry, "country") &&
            isNotEmpty(ui->transportPostcode, "postcode") &&
            isNotEmpty(ui->transportPhone, "phone") &&
            areFieldsEqual(ui->transportPassword, ui->transportPasswordConfirmation, "Passwords do not match")) {
        transportationcompany.SetEmail(ui->transportEmail->text().toStdString());
        transportationcompany.SetUsername(ui->transportEmail->text().toStdString());
        transportationcompany.SetPassword(ui->transportPassword->text().toStdString());
        transportationcompany.SetFirstname(ui->transportCompanyName->text().toStdString());
        transportationcompany.SetSurname(ui->transportCompanyName->text().toStdString());
        transportationcompany.SetCompanyName(ui->transportCompanyName->text().toStdString());
        transportationcompany.SetAddress(ui->transportAddress->text().toStdString());
        transportationcompany.SetCity(ui->transportCity->text().toStdString());
        transportationcompany.SetProvince(ui->transportCity->text().toStdString());

        transportationcompany.SetCountry(ui->transportCountry->text().toStdString());
        transportationcompany.SetPostcode(ui->transportPostcode->text().toStdString());
        transportationcompany.SetPhone(ui->transportPhone->text().toStdString());


        transportationcompany.SetGoodsTransportationType(ui->transportCargoType->currentText().toStdString());

        if(transportationcompany.SignUpAsTransportationCompany(transportationcompany) == true) {
            QMessageBox::information(this, "Registration", "Registered successfully");
            return true;
        } else {
            QMessageBox::information(this, "Registration", "Email(username) already exists");
        }

    }
    return false;
}

bool MainWindow::registerDriver() {
    Vehicle vehicle;
    if (isNotEmpty(ui->driverUserName, "username") &&
            isNotEmpty(ui->driverPassword, "password") &&
            isNotEmpty(ui->driverFirstName, "first name") &&
            isNotEmpty(ui->driverFirstName, "last name") &&
            isNotEmpty(ui->driverEmail, "email") &&
            isNotEmpty(ui->driverAddress, "address") &&
            isNotEmpty(ui->driverCity, "city") &&
            isNotEmpty(ui->driverProvince, "province") &&
            isNotEmpty(ui->driverCountry, "country") &&
            isNotEmpty(ui->driverPostCodeLineEdit, "postcode") &&
            isNotEmpty(ui->driverNINumberLineEdit, "NI number") &&
            isNotEmpty(ui->driverPhone, "phone") &&
            areFieldsEqual(ui->driverPassword, ui->driverPasswordConfirmation, "Passwords do not match")) {
        if (!driver.ValidateCPC(ui->driverCpcNumber->text().toStdString())) {
            QMessageBox::critical(this, "Registration", "Invalid CPC number");
            return false;
        }

        if (!vehicle.ValidateRegistration(ui->driverVehicleRegistration->text().toStdString())) {
            QMessageBox::critical(this, "Registration", "Invalid registration format. Must have  two letters followed by three numbers followed by three letters");
            return false;
        }

        driver.SetUsername(ui->driverUserName->text().toStdString());
        driver.SetPassword(ui->driverPassword->text().toStdString());
        driver.SetFirstname(ui->driverFirstName->text().toStdString());
        driver.SetSurname(ui->driverFirstName->text().toStdString());

        driver.SetEmail(ui->driverEmail->text().toStdString());
        driver.SetAddress(ui->driverAddress->text().toStdString());
        driver.SetCity(ui->driverCity->text().toStdString());
        driver.SetProvince(ui->driverProvince->text().toStdString());

        driver.SetCountry(ui->driverCountry->text().toStdString());
        driver.SetPostcode(ui->driverPostCode->text().toStdString());
        driver.SetPhone(ui->driverPhone->text().toStdString());
        driver.SetNINumber(ui->driverNINumberLineEdit->text().toStdString());
        driver.SetCPC(ui->driverCpcNumber->text().toStdString());

        vehicle.SetVehicleType(ui->driverTypeOfLorry->currentText().toStdString());

        driver.SetRegistration(ui->driverVehicleRegistration->text().toStdString());
        vehicle.SetRegistration(ui->driverVehicleRegistration->text().toStdString());


        bool ok;
        vehicle.SetWeight(ui->driverVehicleWeight->text().toDouble(&ok));
        vehicle.SetHeight(ui->driverVehicleHeight->text().toDouble(&ok));

        vehicle.AddVehicle(vehicle);		// add vehicle

        if(driver.SignUpAsDriver(driver)) {
            QMessageBox::information(this, "Registration", "Registered successfully");
            return true;
        } else {
            QMessageBox::information(this, "Registration", "Username already exists");
        }

    }
    return false;



}

bool MainWindow::isNotEmpty(const QLineEdit* lineEdit,
                            const std::string& fieldName)
{
    std::string fieldValue = lineEdit->text().toStdString();
    if (fieldValue.empty()) {
        QMessageBox::critical(this, "Registration Error", QString::fromStdString("Empty " + fieldName));
        return false;
    }
    return true;
}

bool MainWindow::areFieldsEqual(const QLineEdit* lineEdit1,
                                const QLineEdit* lineEdit2,
                                const std::string& errorMessage) {
    std::string fieldValue1 = lineEdit1->text().toStdString();
    std::string fieldValue2 = lineEdit2->text().toStdString();
    bool fieldsEqual = (fieldValue1 == fieldValue2);
    if (!fieldsEqual) {
        QMessageBox::critical(this, "Registration Error", QString::fromStdString(errorMessage));
    }
    return fieldsEqual;
}

void MainWindow::on_driverCurrentOrders_clicked()
{
    driverUIHelper.populateTableView(ui->driverDisplayOrderTable);
    ui->stackedWidget->setCurrentIndex(driverDisplayOrder);
}


void MainWindow::on_driverOrderHistory_clicked()
{
    driverUIHelper.populateTableView(ui->driverOrderHistoryTable);
    ui->stackedWidget->setCurrentIndex(driverOrderHistory);
}


void MainWindow::on_driverDisplayOrderChangeStatus_clicked()
{
    //TODO: aDd logic
}


void MainWindow::on_driverDisplayOrderBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(driverProfileScreen);
}


void MainWindow::on_driverOrderHistoryBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(driverProfileScreen);
}


void MainWindow::on_transportDisplayOrderBackButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(transportProfileScreen);
}


void MainWindow::on_transportCancelOrder_clicked()
{

}


void MainWindow::on_transportDispatchOrder_clicked()
{

}


void MainWindow::on_transportProfileDisplayOrders_clicked()
{
    transportUIHelper.populateTableView(ui->transportDisplayOrderTable);
    ui->stackedWidget->setCurrentIndex(transportDisplayOrder);
}


void MainWindow::on_customerProfileOrderHistory_clicked()
{
    cargoOwnerUIHelper.populateTableView(ui->customerViewOrdersTable);
    ui->stackedWidget->setCurrentIndex(customerViewOrderScreen);
}



void MainWindow::on_customerViewOrdersBakc_clicked()
{
    ui->stackedWidget->setCurrentIndex(customerProfileScreen);
}


void MainWindow::on_pushButton_clicked()
{

}


void MainWindow::on_sendMessageBackButton_clicked()
{
    showProfilePage();
}


void MainWindow::on_sendMessageButton_clicked()
{

}



void MainWindow::on_viewMessageBackButton_clicked()
{
    showProfilePage();
}


void MainWindow::on_replyMessageBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(viewMessageScreen);
}


void MainWindow::on_customerProfileViewMsg_clicked()
{
    ui->stackedWidget->setCurrentIndex(viewMessageScreen);
}


void MainWindow::on_customerProfileSendMsg_clicked()
{
    ui->stackedWidget->setCurrentIndex(sendMessageScreen);
}


void MainWindow::on_driverViewMessages_clicked()
{
    ui->stackedWidget->setCurrentIndex(viewMessageScreen);
}


void MainWindow::on_driverSendMessage_clicked()
{
    ui->stackedWidget->setCurrentIndex(sendMessageScreen);
}


void MainWindow::on_transportProfileViewMsg_clicked()
{
    ui->stackedWidget->setCurrentIndex(viewMessageScreen);
}


void MainWindow::on_transportProfileSendMsg_clicked()
{
    ui->stackedWidget->setCurrentIndex(sendMessageScreen);
}


void MainWindow::on_viewMessageReply_clicked()
{
    ui->stackedWidget->setCurrentIndex(replyMessageScreen);
}

