#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ETransportTests
#include <boost/test/included/unit_test.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>

#include "cargoowner.h"
#include "database.h"
#include "driver.h"
#include "transaction.h"
#include "transportationcompany.h"
#include "user.h"
#include "vehicle.h"

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

BOOST_AUTO_TEST_SUITE( DatabaseTests )

BOOST_AUTO_TEST_CASE( LoadExistingDatabase )
{
Database database;

    BOOST_CHECK(database.Load("Users.csv") == true);
}

BOOST_AUTO_TEST_CASE( LoadNonExistentDatabase )
{
Database database;

    BOOST_CHECK(database.Load("UsersNonExistent.csv") == false);
}

BOOST_AUTO_TEST_CASE( SaveDatabase )
{
Database database;

    BOOST_CHECK(database.Load("Users.csv") == true);
    BOOST_CHECK(database.Save("Users2.csv") == true);
}

BOOST_AUTO_TEST_CASE( ReadTest)
{
Database database;
std::vector<std::string> row;

BOOST_CHECK(database.Load("Users.csv") == true);

row=database.Read("adambloggs@gmail.com");
BOOST_CHECK(row.size() != 0);
}

BOOST_AUTO_TEST_CASE(WriteExistingTest)
{
Database database;
std::vector<std::string> row;

BOOST_CHECK(database.Load("Users.csv") == true);

row=database.Read("adambloggs");
BOOST_CHECK(database.Write("adambloggs",row) == true);
}

BOOST_AUTO_TEST_CASE(WriteNewTest)
{
Database database;
std::vector<std::string> row;

BOOST_CHECK(database.Load("Users.csv") == true);

row = { "Test","abbbbbbbbbbbbbbbb","Booo","Testing","456 nowhere street","Derby","Derby","DE123XY","123456789","nowhere@nowhere.com","United Kingdom","Driver","FE1237636","ABC123456C","45DEF456" };
database.Write("adambloggs",row);

BOOST_CHECK(row[0].compare("Test") == 0);
BOOST_CHECK(row[1].compare("abbbbbbbbbbbbbbbb") == 0);
BOOST_CHECK(row[2].compare("Booo") == 0);
BOOST_CHECK(row[3].compare("Testing") == 0);
BOOST_CHECK(row[4].compare("456 nowhere street") == 0);
BOOST_CHECK(row[5].compare("Derby") == 0);
BOOST_CHECK(row[6].compare("Derby") == 0);
BOOST_CHECK(row[7].compare("DE123XY") == 0);
BOOST_CHECK(row[8].compare("123456789") == 0);
BOOST_CHECK(row[9].compare("nowhere@nowhere.com") == 0);
BOOST_CHECK(row[10].compare("United Kingdom") == 0);
BOOST_CHECK(row[11].compare("Driver") == 0);
BOOST_CHECK(row[12].compare("FE1237636") == 0);
BOOST_CHECK(row[13].compare("ABC123456C") == 0);
BOOST_CHECK(row[14].compare("45DEF456") == 0);

}

BOOST_AUTO_TEST_CASE(FindExistingTest)
{
Database database;
std::vector<std::string> row;

BOOST_CHECK(database.Load("Users.csv") == true);

row=database.Find();
BOOST_CHECK(row.size() != 0);
}

BOOST_AUTO_TEST_CASE(NewDatabaseTest)
{
Database database;
BOOST_CHECK(database.New("UsersNew.csv") != false);
}

BOOST_AUTO_TEST_CASE(SaveDatabaseTest)
{
Database database;
BOOST_CHECK(database.Load("Users.csv") != false);
BOOST_CHECK(database.Save("UsersNew.csv") != false);
}

BOOST_AUTO_TEST_CASE(DeleteExistingTest)
{
Database database;

Driver driver;

driver.SetFirstname("Test");
driver.SetSurname("User");
driver.SetAddress("123 Fake Street");
driver.SetCity("Nottingham");
driver.SetProvince("Nottingham");
driver.SetCountry("United Kingdom");
driver.SetPostcode("NG123ABC");
driver.SetPhone("1234");
driver.SetEmail("test@test.com");
driver.SetUsername(driver.GetEmail());			// email is username
driver.SetPassword("password");
driver.SignUpAsDriver(driver);

BOOST_CHECK(database.Load("Users.csv") != false);
BOOST_CHECK(database.Delete("test@test.com") != false);
}

BOOST_AUTO_TEST_CASE(DeleteNonExistingTest)
{
Database database;
BOOST_CHECK(database.Load("Users.csv") != false);
BOOST_CHECK(database.Delete("adamblah") == false);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CargoOwnerTests )

BOOST_AUTO_TEST_CASE( SignUpAsCargoOwner)
{
CargoOwner cargoowner;

cargoowner.SetFirstname("Test");
cargoowner.SetSurname("User");
cargoowner.SetAddress("123 Fake Street");
cargoowner.SetCity("Nottingham");
cargoowner.SetProvince("Nottingham");
cargoowner.SetCountry("United Kingdom");
cargoowner.SetPostcode("NG123ABC");
cargoowner.SetPhone("1234");
cargoowner.SetEmail("test@test.com");
cargoowner.SetUsername(cargoowner.GetEmail());			// email is username
cargoowner.SetPassword("password");
BOOST_CHECK(cargoowner.SignUpAsCargoOwner(cargoowner)== true);
}

BOOST_AUTO_TEST_CASE(SetCompanyNameTest)
{
std::string testvar;
CargoOwner cargoowner;
cargoowner.SetCompanyName("test");
BOOST_CHECK(cargoowner.GetCompanyName() == "test");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UserTests )

BOOST_AUTO_TEST_CASE(SetNINumberTest)
{
std::string testvar;

User user;
user.SetUsername("test");
BOOST_CHECK(user.GetUsername() == "test");
}

BOOST_AUTO_TEST_CASE(SetUserNameTest)
{
std::string testvar;

User user;
user.SetUsername("test");
BOOST_CHECK(user.GetUsername() == "test");
}

BOOST_AUTO_TEST_CASE(SetPasswordTest)
{
std::string testvar;
std::string encryptedpassword;

User user;
user.SetUsername("test@test.com");
user.SetPassword("test");
encryptedpassword=user.HashPassword(user.GetUsername(),user.GetPassword());			// hash password

BOOST_CHECK(user.GetPassword() == "teH0wLIpW0gyQ");
}

BOOST_AUTO_TEST_CASE(SetFirstname)
{
std::string testvar;

User user;
user.SetFirstname("test");
BOOST_CHECK(user.GetFirstname() == "test");
}

BOOST_AUTO_TEST_CASE(SetSurnameTest)
{
std::string testvar;

User user;

user.SetSurname("test");
BOOST_CHECK(user.GetSurname() == "test");
}

BOOST_AUTO_TEST_CASE(SetAddressTest)
{
std::string testvar;

User user;
user.SetAddress("test");
BOOST_CHECK(user.GetAddress() == "test");
}

BOOST_AUTO_TEST_CASE(SetCity)
{
std::string testvar;

User user;
user.SetCity("test");
BOOST_CHECK(user.GetCity() == "test");
}

BOOST_AUTO_TEST_CASE(SetProvinceTest)
{
User user;
user.SetProvince("test");

BOOST_CHECK(user.GetProvince() == "test");
}

BOOST_AUTO_TEST_CASE(SetPostcodeTest)
{
std::string testvar;

User user;
user.SetPostcode("test");
BOOST_CHECK(user.GetPostcode() == "test");
}

BOOST_AUTO_TEST_CASE(SetCountryTest)
{
std::string testvar;

User user;
user.SetCountry("test");
BOOST_CHECK(user.GetCountry() == "test");
}

BOOST_AUTO_TEST_CASE(SetEmailTest)
{
std::string testvar;

User user;
user.SetEmail("test");
BOOST_CHECK(user.GetEmail() == "test");
}

BOOST_AUTO_TEST_CASE(SetPhoneTest)
{
std::string testvar;

User user;
user.SetPhone("test");
BOOST_CHECK(user.GetPhone() == "test");
}

BOOST_AUTO_TEST_CASE(SetAccountTypeTest)
{
std::string testvar;

User user;
user.SetAccountType("Driver");
BOOST_CHECK(user.GetAccountType() == "Driver");
}

BOOST_AUTO_TEST_CASE(SignInValidUserTest)
{
CargoOwner user;
BOOST_CHECK(user.SignIn("adambloggs@gmail.com","password") == true);
}

BOOST_AUTO_TEST_CASE(SignInInvalidUsernameTest)
{
CargoOwner user;
BOOST_CHECK(user.SignIn("adamblahs","password") == false);
}

BOOST_AUTO_TEST_CASE(SignInInValidPasswordTest)
{
CargoOwner user;
BOOST_CHECK(user.SignIn("adambloggs","badpassword") == false);
}

BOOST_AUTO_TEST_CASE(SignOutTest)
{
User user;
BOOST_CHECK(user.SignOut() == true);
}

BOOST_AUTO_TEST_CASE(HashPasswordTest)
{
User user;
BOOST_CHECK(user.HashPassword("adambloggs","password") == "advwtv/9yU5yQ");
}

BOOST_AUTO_TEST_CASE(HashPasswordTestInValid)
{
User user;
BOOST_CHECK(user.HashPassword("adambloggs","fakepassword") != "advwtv/9yU5yQ");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(DriverTests )

BOOST_AUTO_TEST_CASE( SignUpAsDriver)
{
Driver driver;
random_generator gen;
uuid ID;

driver.SetFirstname("Test");
driver.SetSurname("User");
driver.SetAddress("123 Fake Street");
driver.SetCity("Nottingham");
driver.SetProvince("Nottingham");
driver.SetCountry("United Kingdom");
driver.SetPostcode("NG123ABC");
driver.SetPhone("1234");

ID = gen();
const std::string tempid = boost::uuids::to_string(ID);		// Convert uuid to string

std::cout << tempid;

driver.SetEmail(tempid);
driver.SetUsername(driver.GetEmail());			// email is username
driver.SetPassword("password");

BOOST_CHECK(driver.SignUpAsDriver(driver) == true);
}

BOOST_AUTO_TEST_CASE( FindNearestDriver)
{
Driver driver;

driver=driver.FindNearestDriver("Nottingham","Nottingham","United Kingdom");

BOOST_CHECK(driver.GetCity() != "");
}

BOOST_AUTO_TEST_CASE(SetRegistrationTest)
{
std::string testvar;
Driver driver;

driver.SetRegistration("test");
BOOST_CHECK(driver.GetRegistration() == "test");
}

BOOST_AUTO_TEST_CASE(ValidateCPCTest)
{
std::string testvar;
Driver driver;

BOOST_CHECK(driver.ValidateCPC("AA12345678") == true);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestNoLetters)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("12345678") == false);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestNoNumbers)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("AA") == false);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestTooFewLetters)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("A12345678") == false);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestTooManyLetters)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("AAA12345678") == false);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestTooFewNumbers)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("AA125678") == false);
}

BOOST_AUTO_TEST_CASE(ValidateCPCTestTooManyNumber)
{
Driver driver;

BOOST_CHECK(driver.ValidateCPC("AA1256789") == false);
}

BOOST_AUTO_TEST_CASE(SetCPCTest)
{
std::string testvar;
Driver driver;

driver.SetCPC("test");
BOOST_CHECK(driver.GetCPC() == "test");
}


BOOST_AUTO_TEST_SUITE(TransportationCompanyTests )

BOOST_AUTO_TEST_CASE( SignUpAstransportationcompany)
{
random_generator gen;
uuid ID;

TransportationCompany transportationcompany;

transportationcompany.SetFirstname("Test");
transportationcompany.SetSurname("User");
transportationcompany.SetAddress("123 Fake Street");
transportationcompany.SetCity("Nottingham");
transportationcompany.SetProvince("Nottingham");
transportationcompany.SetCountry("United Kingdom");
transportationcompany.SetPostcode("NG123ABC");
transportationcompany.SetPhone("1234");

ID = gen();
const std::string tempid = boost::uuids::to_string(ID);		// Convert uuid to string

transportationcompany.SetEmail(tempid);
transportationcompany.SetUsername(transportationcompany.GetEmail());			// email is username
transportationcompany.SetPassword("password");
BOOST_CHECK(transportationcompany.SignUpAsTransportationCompany(transportationcompany)== true);
}

BOOST_AUTO_TEST_CASE( FindNearestTransportationCompany)
{
TransportationCompany *transportationcompany=new TransportationCompany();

transportationcompany=transportationcompany->FindNearestTransportationCompany("Nottingham","Nottingham","United Kingdom");

BOOST_CHECK(transportationcompany->GetCity() != "");
}

BOOST_AUTO_TEST_CASE(SetGoodsTransportationTypeTest)
{
TransportationCompany transportationcompany;

transportationcompany.SetGoodsTransportationType("test");
BOOST_CHECK(transportationcompany.GetGoodsTransportationType() == "test");
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( TransactionTests )

BOOST_AUTO_TEST_CASE( CreateNewTransactionTest )
{
 Transaction transaction("test_transactions.csv");
 uuid orderid;

 transaction.SetGoodsType("Freight");
 transaction.SetFirstname("Test");
 transaction.SetSurname("User");
 transaction.SetDeliveryAddress("123 Fake Street");
 transaction.SetCity("Nottingham");
 transaction.SetProvince("Nottingham");
 transaction.SetPostCode("NG123AB");
 transaction.SetCountry("United Kingdom");
 transaction.SetContactPhone("123");
 transaction.SetContactEmail("test@test.com");
 transaction.SetPriority(1);
 transaction.SetTotalCost(transaction.CalculateCostOfDelivery());
 transaction.SetWeight(12);
 transaction.SetComments("Test delivery");
 transaction.SetDescription("A test order");
 transaction.GenerateID();		// Generate UUID to represent order

 orderid=transaction.GetID();

 BOOST_CHECK(transaction.PlaceOrder("test","Nottingham","Nottingham","United Kingdom")== true);
}

BOOST_AUTO_TEST_CASE( CancelTransactionTest )
{
 Transaction transaction("test_transactions.csv");
 uuid orderid;

 transaction.SetGoodsType("Freight");
 transaction.SetFirstname("Test");
 transaction.SetSurname("User");
 transaction.SetDeliveryAddress("123 Fake Street");
 transaction.SetCity("Nottingham");
 transaction.SetProvince("Nottingham");
 transaction.SetPostCode("NG123AB");
 transaction.SetCountry("United Kingdom");
 transaction.SetContactPhone("123");
 transaction.SetContactEmail("test@test.com");
 transaction.SetPriority(1);
 transaction.SetTotalCost(transaction.CalculateCostOfDelivery());
 transaction.SetWeight(12);
 transaction.SetComments("Test delivery");
 transaction.SetDescription("A test order");
 transaction.GenerateID();		// Generate UUID to represent order

 BOOST_CHECK(transaction.PlaceOrder("test","Nottingham","Nottingham","United Kingdom")== true);
 uuid id = boost::lexical_cast<uuid>("35fee53e-b6e5-4ab0-818d-44cd37857a5c");

 BOOST_CHECK(transaction.CancelTransaction(transaction.GetID()) == true);
}

BOOST_AUTO_TEST_CASE( CancelNonExistingTransactionTest )
{
 uuid id = boost::lexical_cast<uuid>("abcdef12-abcd-1234-ab12-abcd12345abb");
  Transaction transaction("test_transactions.csv");

  BOOST_CHECK(transaction.CancelTransaction(id)== false);
}

BOOST_AUTO_TEST_CASE( GetOrderIDTest )
{
 Transaction transaction("test_transactions.csv");
 uuid orderid;

 transaction.GenerateID();		// Generate UUID to represent order
 orderid=transaction.GetID();

 BOOST_CHECK(transaction.GetID() == orderid);
}

BOOST_AUTO_TEST_CASE(SetSender)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

transaction.SetSender("test");
BOOST_CHECK(transaction.GetSender() == "test");
}

BOOST_AUTO_TEST_CASE(SetFirstname)
{
Transaction transaction("test_transactions.csv");

transaction.SetFirstname("test");
BOOST_CHECK(transaction.GetFirstname() == "test");
}

BOOST_AUTO_TEST_CASE(SetSurnameTest)
{
Transaction transaction("test_transactions.csv");
transaction.SetSurname("test");

BOOST_CHECK(transaction.GetSurname() == "test");
}

BOOST_AUTO_TEST_CASE(SetAddressTest)
{
Transaction transaction("test_transactions.csv");
transaction.SetDeliveryAddress("test");

BOOST_CHECK(transaction.GetDeliveryAddress() == "test");
}

BOOST_AUTO_TEST_CASE(SetCity)
{
Transaction transaction("test_transactions.csv");
transaction.SetCity("test");
BOOST_CHECK(transaction.GetCity() == "test");
}

BOOST_AUTO_TEST_CASE(SetProvinceTest)
{
Transaction transaction("test_transactions.csv");
transaction.SetProvince("test");
BOOST_CHECK(transaction.GetProvince() == "test");
}

BOOST_AUTO_TEST_CASE(SetPostCodeTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetPostCode("test");
BOOST_CHECK(transaction.GetPostCode() == "test");
}

BOOST_AUTO_TEST_CASE(SetCountryTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetCountry("test");
BOOST_CHECK(transaction.GetCountry() == "test");
}

BOOST_AUTO_TEST_CASE(SetEmailTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetContactEmail("test@test.com");
BOOST_CHECK(transaction.GetContactEmail() == "test@test.com");
}

BOOST_AUTO_TEST_CASE(SetPhoneTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetContactPhone("test");
BOOST_CHECK(transaction.GetContactPhone() == "test");
}

BOOST_AUTO_TEST_CASE(SetSenderTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetSender("test");
BOOST_CHECK(transaction.GetSender() == "test");
}

BOOST_AUTO_TEST_CASE(SetPriorityTest)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

transaction.SetPriority(1);
BOOST_CHECK(transaction.GetPriority() == 1);
}

BOOST_AUTO_TEST_CASE(SetTotalCost)
{
Transaction transaction("test_transactions.csv");

transaction.SetTotalCost(1.23);
BOOST_CHECK(transaction.GetTotalCost() == 1.23);
}

BOOST_AUTO_TEST_CASE(SetWeightTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetWeight(1.23);
BOOST_CHECK(transaction.GetItemWeight() == 1.23);
}

BOOST_AUTO_TEST_CASE(SetDescriptionTest)
{
Transaction transaction("test_transactions.csv");

transaction.SetDescription("test");
BOOST_CHECK(transaction.GetDescription() == "test");
}

BOOST_AUTO_TEST_CASE(SetComments)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

transaction.SetComments("test");
BOOST_CHECK(transaction.GetComments() == "test");
}

BOOST_AUTO_TEST_CASE(SetGoodsTypeTest)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

transaction.SetGoodsType("freight");
BOOST_CHECK(transaction.GetGoodsType() == "freight");
}

BOOST_AUTO_TEST_CASE(SetRecipientUsernameTest)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

transaction.SetRecipientUsername("test");
BOOST_CHECK(transaction.GetRecipientUsername() == "test");
}

BOOST_AUTO_TEST_CASE(ChangeStatusTest)
{
std::string testvar;
uuid orderid;

Transaction transaction("test_transactions.csv");

 transaction.SetGoodsType("Freight");
 transaction.SetFirstname("Test");
 transaction.SetSurname("User");
 transaction.SetDeliveryAddress("123 Fake Street");
 transaction.SetCity("Nottingham");
 transaction.SetProvince("Nottingham");
 transaction.SetPostCode("NG123AB");
 transaction.SetCountry("United Kingdom");
 transaction.SetContactPhone("123");
 transaction.SetContactEmail("test@test.com");
 transaction.SetPriority(1);
 transaction.SetTotalCost(transaction.CalculateCostOfDelivery());
 transaction.SetWeight(12);
 transaction.SetComments("Test delivery");
 transaction.SetDescription("A test order");
 transaction.GenerateID();		// Generate UUID to represent order

 orderid=transaction.GetID();

transaction.PlaceOrder("test","Nottingham","Nottingham","United Kingdom");

BOOST_CHECK(transaction.ChangeStatus(transaction.GetID(),"on road") == true);
}

BOOST_AUTO_TEST_CASE(CalculateShippingRatesTest)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

 transaction.SetCity("Nottingham");
 transaction.SetProvince("Nottingham");
 transaction.SetCountry("United Kingdom");
 transaction.SetWeight(1);
 transaction.SetPriority(1);

 std::cout << transaction.CalculateShippingRates() << std::endl;

BOOST_TEST(transaction.CalculateShippingRates() == 311.316,tt::tolerance(0.01));
}

BOOST_AUTO_TEST_CASE(CalculateCostOfDelivery)
{

Transaction transaction("test_transactions.csv");

transaction.SetCity("Nottingham");
transaction.SetProvince("Nottingham");
transaction.SetCountry("United Kingdom");
transaction.SetWeight(1);
transaction.SetPriority(1);

BOOST_TEST(transaction.CalculateCostOfDelivery() == 342.447,tt::tolerance(0.01));
}
  
BOOST_AUTO_TEST_CASE(CalculateCommission)
{
std::string testvar;
Transaction transaction("test_transactions.csv");

 transaction.SetCity("Nottingham");
 transaction.SetProvince("Nottingham");
 transaction.SetCountry("United Kingdom");
 transaction.SetWeight(1);
 transaction.SetPriority(1);
 transaction.SetTotalCost(transaction.CalculateCostOfDelivery());
 

BOOST_TEST(transaction.CalculateCommission() == 31.1316,tt::tolerance(0.01));
}

BOOST_AUTO_TEST_CASE(GetLocation)
{
std::vector<double> location;
Transaction transaction("test_transactions.csv");

location=transaction.GetLocation();

BOOST_CHECK(location[0] == 122);
BOOST_CHECK(location[1] == 272);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(VehicleTests )

BOOST_AUTO_TEST_CASE( AddVehicleTest )
{
Vehicle vehicle;

vehicle.SetRegistration("AA1234AAA");
vehicle.SetVehicleType("HGV");
vehicle.SetWeight(123);
vehicle.SetHeight(12);

BOOST_CHECK(vehicle.AddVehicle(vehicle) == true);
}

BOOST_AUTO_TEST_CASE(SetRegistrationTest)
{
std::string testvar;
Vehicle vehicle;

vehicle.SetRegistration("ZZ456XYZ");
BOOST_CHECK(vehicle.GetRegistration() == "ZZ456XYZ");
}

BOOST_AUTO_TEST_CASE(SetWeightTest)
{
std::string testvar;
Vehicle vehicle;

vehicle.SetWeight(1234);
BOOST_CHECK(vehicle.GetWeight() == 1234);
}

BOOST_AUTO_TEST_CASE(SetHeightTest)
{
std::string testvar;
Vehicle vehicle;

vehicle.SetHeight(1234);
BOOST_CHECK(vehicle.GetHeight() == 1234);
}

BOOST_AUTO_TEST_CASE(SetVehicleTypeTest)
{
std::string testvar;
Vehicle vehicle;

vehicle.SetVehicleType("HGV");
BOOST_CHECK(vehicle.GetVehicleType() == "HGV");
}

BOOST_AUTO_TEST_CASE(ValidateRegistrationTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("AB123XYZ") == true);
}


BOOST_AUTO_TEST_CASE(ValidateRegistrationTooFewLettersBeginningTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("A1234XYZ") == false);
}


BOOST_AUTO_TEST_CASE(ValidateRegistrationTooFewNumbersTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("ABC124XYZ") == false);
}


BOOST_AUTO_TEST_CASE(ValidateRegistrationTooManyNumbersTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("AB12345XYZ") == false);
}

BOOST_AUTO_TEST_CASE(ValidateRegistrationTooManyLettersEndTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("AB1234XYZZ") == false);
}

BOOST_AUTO_TEST_CASE(ValidateRegistrationTooFewsEndTest)
{
std::string testvar;
Vehicle vehicle;

BOOST_CHECK(vehicle.ValidateRegistration("AB1234XY") == false);
}

BOOST_AUTO_TEST_SUITE_END()
}




