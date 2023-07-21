/*
 * Transaction.cpp
 *
 * Adeeb Sait and Matthew Boote
 */

#include <iostream>
#include "transaction.h"
#include "database.h"
#include "MessageInterface.h"
#include "transportationcompany.h"
#include "file_path.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include "exception.h"

using namespace boost::uuids;


/*!
 *\file transaction.cpp
    * 
    * \class Transaction
    * @brief Transaction class represents a single order.
    * 
    * @author Matthew Boote
    *
    */

  /*!
 *\file transaction.cpp
    * 
    * Transaction()
    * @brief Transaction constructor
    * 
    * @author Matthew Boote
    *
    * @details Initializes transaction object by loading the database associated with the transaction.
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    * @throw General exception  
    */
 
Transaction::Transaction(std::string transactionfilename) {
 TransactionDatabase=new Database();
 
 try {
  if(TransactionDatabase->Load(transactionfilename) == false) {				// Open transaction for user
  
   if(TransactionDatabase->New(transactionfilename) == false) {				// Create new database if can't open    
    throw("Can't create transaction");
     exit(1);
   }
 }
}
catch(const char *message) {
 std::cout << message << std::endl;
// exception_handler(message);
}

}
  /*!
 *\file transaction.cpp
    * 
    * PlaceOrder()
    * @brief Places an order.
    * 
    * @author Matthew Boote
    *
    * @details This function adds the order to the user's transaction database, finds the nearest transportation company to the user and sends a message to them.
    *
    * @param[in] std::string senderusername,std::string sendercity,std::string senderprovince,std::string sendercountry
    * 
    * @param[out] None
    *
    * @return boolean
    *
    * @throw General exception  
    */
  
bool Transaction::PlaceOrder(std::string senderusername,std::string sendercity,std::string senderprovince,std::string sendercountry) {
  std::vector<std::string> transaction_vector;
  Message message;
  TransportationCompany *transportationcompany=new TransportationCompany;

  transportationcompany=transportationcompany->FindNearestTransportationCompany(sendercity,senderprovince,sendercountry);
  if(transportationcompany == NULL) return false;

// Create a database entry
//
 // database uses vector, because it's implementation-agnostic

 transaction_vector.push_back(senderusername);
 transaction_vector.push_back(transportationcompany->GetUsername());
 transaction_vector.push_back(Firstname);
 transaction_vector.push_back(Surname);
 transaction_vector.push_back(DeliveryAddress);
 transaction_vector.push_back(City);
 transaction_vector.push_back(Province);
 transaction_vector.push_back(PostCode);
 transaction_vector.push_back(Country);
 transaction_vector.push_back(ContactPhone);
 transaction_vector.push_back(ContactEmail);
 transaction_vector.push_back(std::to_string(priority));
 transaction_vector.push_back(std::to_string(TotalCost));
 transaction_vector.push_back(std::to_string(ItemWeight));
 transaction_vector.push_back(ItemDescription);
 transaction_vector.push_back(Comments);
 transaction_vector.push_back(GoodsType);
 transaction_vector.push_back(DriverName);
 transaction_vector.push_back("waiting");

// Add it to transaction database

 const std::string tempid = boost::uuids::to_string(ID);		// Convert uuid to string

 if(TransactionDatabase->Write(tempid,transaction_vector) == false) return(false);

 TransactionDatabase->Save(TransactionDatabase->GetFileName());	// must save the dateabase

 
// Send new order message 

std::string newordermessage="Order "+tempid + \
    			 "Sender: " +GetSender()   + \
		         "Recipient name: "+GetFirstname() + " " +  GetSurname()    + \
    		         "Address: "+GetDeliveryAddress() + \
    			"Post code: "+GetPostCode() + \
    			"Country: "+ GetCountry()  + \
			"Phone: " + GetContactPhone() + \
			"Email: " + GetContactEmail() + \
			"Goods description: "  + GetDescription() + \
			"Weight: " + std::to_string(GetItemWeight()) + \
			"Type of goods: " + GetGoodsType()  + \
			"Comments: "+ GetComments() +"\n";
 		
 std::string newordersubject="You have a new order ("+tempid+")"; 
 message.SendMessageInternal(senderusername,transportationcompany->GetUsername(),newordersubject,newordermessage);

 std::cout << "The order has been placed" << std::endl;
return true;
}

  /*!
 *\file transaction.cpp
    * 
    * PlaceOrder()
    * @brief Cancels an order.
    * 
    * @author Matthew Boote
    *
    * @details This function deletes the order from the order database.
    *
    * @param[in] std::string senderusername,std::string sendercity,std::string senderprovince,std::string sendercountry
    * 
    * @param[out] None
    *
    * @return boolean
    */
 
bool Transaction::CancelTransaction(uuid orderid) {
 const std::string tempid = boost::uuids::to_string(orderid);		// Convert uuid to string

 return(TransactionDatabase->Delete(tempid));		// Delete order from database
}

  /*!
 *\file transaction.cpp
    * 
    * ChangeStatus()
    * @brief Changes the order's status
    * 
    * @author Matthew Boote
    *
    * @details This function changes the order status in the order's database entry. Order status can be waiting, on road and delivered.
    *
    * @param[in] uuid orderid,std::string status
    * 
    * @param[out] None
    *
    * @return boolean
    *
    * @throw General exception  
    */
bool Transaction::ChangeStatus(uuid orderid,std::string status) {
std::vector<std::string> readentry;
const std::string tempid = boost::uuids::to_string(orderid);		// Convert uuid to string

// Get order from database, update it and write it back

readentry=TransactionDatabase->Read(tempid);		// Read database entry

try {
 if(readentry.size() == 0) {		// no database entry
   throw("Order not found");
 }
}
catch(const char *message) {
 exception_handler(message);
 return(false);
}

readentry[TRANSACTION_VECTOR_STATUS]=status;		// Update status

readentry.erase(readentry.begin());			// remove first entry to remove duplicate id

if(status.compare("delivered") == 0) {			// If delivered, remove from database
 TransactionDatabase->Delete(tempid);
}
else
{
 TransactionDatabase->Write(tempid,readentry);		// Write database entry
}

return(true);
}

  /*!
 *\file transaction.cpp
    * 
    * FindNextTransaction()
    * @brief Finds the next transaction in the order databae
    * 
    * @author Matthew Boote
    *
    * @details This function returns each order in the database, in sequence.
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return boolean
    *
    * @throw Throws error if database entry not found
    */
bool Transaction::FindNextTransaction(void) {
 std::vector<std::string> databaseentry;

 databaseentry=TransactionDatabase->Find();			// Find next entry

try {
 if(databaseentry.size() == 0) {		// no database entry
   throw("Order not found");
 }
}
catch(const char *message) {
 exception_handler(message);
 return(false);
}


 // Read database into transaction
 
 uuid id = boost::lexical_cast<uuid>(databaseentry[TRANSACTION_VECTOR_ID]);
 ID=id;
 sender=databaseentry[TRANSACTION_VECTOR_SENDER_USERNAME];
 Firstname=databaseentry[TRANSACTION_VECTOR_FIRSTNAME];
 Surname=databaseentry[TRANSACTION_VECTOR_SURNAME];
 DeliveryAddress=databaseentry[TRANSACTION_VECTOR_DELIVERYADDRESS];
 PostCode=databaseentry[TRANSACTION_VECTOR_POSTCODE];
 City=databaseentry[TRANSACTION_VECTOR_CITY];
 Province=databaseentry[TRANSACTION_VECTOR_PROVINCE];
 Country=databaseentry[TRANSACTION_VECTOR_COUNTRY];
 ItemWeight=stod(databaseentry[TRANSACTION_VECTOR_WEIGHT]);
 ContactPhone=databaseentry[TRANSACTION_VECTOR_PHONE];
 ContactEmail=databaseentry[TRANSACTION_VECTOR_EMAIL];
 priority=stoi(databaseentry[TRANSACTION_VECTOR_PRIORITY]);
 GoodsType=databaseentry[TRANSACTION_VECTOR_GOODSTYPE];
 TotalCost=stod(databaseentry[TRANSACTION_VECTOR_TOTALCOST]);
 ItemWeight=stod(databaseentry[TRANSACTION_VECTOR_WEIGHT]);
 ItemDescription=databaseentry[TRANSACTION_VECTOR_DESCRIPTION];
 Comments=databaseentry[TRANSACTION_VECTOR_COMMENTS];
 Status=databaseentry[TRANSACTION_VECTOR_STATUS];
 return true;
}

  /*!
 *\file transaction.cpp
    * 
    * GetID()
    * @brief Gets the orders ID
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return uuid ID
    *
    */
uuid Transaction::GetID(void) {
 return(ID);
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the first name of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return uuid ID
    *
    */
std::string Transaction::GetFirstname(void) {
return(Firstname);
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the surname of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetSurname(void) {
return(Surname);
}

  /*!
 *\file transaction.cpp
    * 
    * GetDeliveryAddress()
    * @brief Gets the address of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetDeliveryAddress(void) {
 return(DeliveryAddress);
}

  /*!
 *\file transaction.cpp
    * 
    * GetPostCode()
    * @brief Gets the postcode of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetPostCode(void) {
return(PostCode);
}

  /*!
 *\file transaction.cpp
    * 
    * GetContatPhone()
    * @brief Gets the contact phone number of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetContactPhone(void) {
return(ContactPhone);
}

  /*!
 *\file transaction.cpp
    * 
    * GetSender()
    * @brief Gets the order's sender
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetSender(void) {
return sender;
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the order's description
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetDescription(void) {
return ItemDescription;
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the goods type of the order (Animals, etc)
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */

std::string Transaction::GetGoodsType(void) {
return GoodsType;
}
  
  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the email of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetContactEmail(void) {
return(ContactEmail);
}

  /*!
 *\file transaction.cpp
    * 
    * GetPriority()
    * @brief Gets the order's priority
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return int
    *
    */
int Transaction::GetPriority(void) {
return(priority);
}

  /*!
 *\file transaction.cpp
    * 
    * GetTotalCost()
    * @brief Gets the total cost of the order
    * 
    * @author Matthew Boote
    *
    * @desc The order is calculated from the distance, weight and the driver and transportation company's commission.
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return double
    *
    */
double Transaction::GetTotalCost(void) {
return(TotalCost);
}

  /*!
 *\file transaction.cpp
    * 
    * GetItemWeight()
    * @brief Gets the weight of the item
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return double
    *
    */
double Transaction::GetItemWeight(void) {
 return(ItemWeight);
}

  /*!
 *\file transaction.cpp
    * 
    * GetRecipientUsername()
    * @brief Gets the username of the order's recipient
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetRecipientUsername(void) {
 return RecipientUsername;
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the order's comment
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetComments(void) {
 return Comments;
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the order's description
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetItemDescription(void) {
 return(ItemDescription);
}

  /*!
 *\file transaction.cpp
    * 
    * GetProvince()
    * @brief Gets the order's recipient province
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetProvince(void) {
 return Province;
}

  /*!
 *\file transaction.cpp
    * 
    * GetFirstName()
    * @brief Gets the order's recipient city
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetCity(void) {
 return City;
}


  /*!
 *\file transaction.cpp
    * 
    * GetCountry()
    * @brief Gets the recipient's country
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
std::string Transaction::GetCountry(void) {
 return Country;
}

  /*!
 *\file transaction.cpp
    * 
    * GenerateID()
    * @brief Generates a unique boost UUID
    * 
    * @author Matthew Boote
    *
    * @desc The ID is used as the primary key for the order database
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::GenerateID(void) {
 random_generator gen;
 ID = gen();
}

  /*!
 *\file transaction.cpp
    * 
    * SetID()
    * @brief Sets the order's ID
    * 
    * @author Matthew Boote
    *
    * @desc The ID is used as the primary key for the order database
    *
    * @param[in] uuid id
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetID(uuid id) {
 ID = id;
}

  /*!
 *\file transaction.cpp
    * 
    * SetSender()
    * @brief Sets the sender's name
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string fname
    * 
    * @param[out] None
    *
    * @return std::string
    *
    */
void Transaction::SetSender(std::string fname) {
sender=fname;
}

  /*!
 *\file transaction.cpp
    * 
    * SetSenderFirstName()
    * @brief Sets the sender's first name
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string fname
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetFirstname(std::string fname) {
Firstname=fname;
}

  /*!
 *\file transaction.cpp
    * 
    * SetSenderSurname()
    * @brief Sets the sender's surname
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string sname
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetSurname(std::string sname) {
Surname=sname;
}

  /*!
 *\file transaction.cpp
    * 
    * SetSender()
    * @brief Sets the order's delivery address
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string address
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetDeliveryAddress(std::string address) {
DeliveryAddress=address;
}

  /*!
 *\file transaction.cpp
    * 
    * SetPostCode()
    * @brief Sets the order's postcode
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string pcode
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetPostCode(std::string pcode) {
 PostCode=pcode;
}

  /*!
 *\file transaction.cpp
    * 
    * SetSender()
    * @brief Sets the order's country
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string country
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetCountry(std::string country) {
 Country=country;
}

  /*!
 *\file transaction.cpp
    * 
    * SetWeight()
    * @brief Sets the item's weight
    * 
    * @author Matthew Boote
    *
    * @param[in] double w
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetWeight(double w) {
 ItemWeight=w;
}
 

  /*!
 *\file transaction.cpp
    * 
    * SetContactPhone()
    * @brief Sets the order's contact phone number
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string pnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetContactPhone(std::string pnumber) {
ContactPhone=pnumber;
}

 /*!
 *\file transaction.cpp
    * 
    * SetContactEmail()
    * @brief Sets the order's contact email address
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string email
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetContactEmail(std::string email) {
ContactEmail=email;
}

 /*!
 *\file transaction.cpp
    * 
    * SetPriority()
    * @brief Sets the order's priority
    * 
    * @author Matthew Boote
    *
    * @desc The priority is from 1-3 and determines the speed and cost of the delivery.
    *
    * @param[in] std::string pnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetPriority(int pri) {
priority=pri;
}

 /*!
 *\file transaction.cpp
    * 
    * SetGoodsType()
    * @brief Sets the type of the order
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string type
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetGoodsType(std::string type) {
GoodsType=type;
}

 /*!
 *\file transaction.cpp
    * 
    * SetContactPhone()
    * @brief Sets the order's contact phone number
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string pnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetTotalCost(double cost) {
TotalCost=cost;
}

 /*!
 *\file transaction.cpp
    * 
    * SetDescription()
    * @brief Sets the order's description
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string desc
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetDescription(std::string desc) {
 ItemDescription=desc;
}

 /*!
 *\file transaction.cpp
    * 
    * SetComents()
    * @brief Sets the order's comments
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string comments
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetComments(std::string comments) {
 Comments=comments;
}

void Transaction::SetRecipientUsername(std::string username) {
 RecipientUsername=username;
}

 /*!
 *\file transaction.cpp
    * 
    * SetProvince()
    * @brief Sets the order's province 
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string pnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetProvince(std::string province) {
 Province=province;
}

 /*!
 *\file transaction.cpp
    * 
    * SetCity()
    * @brief Sets the order's city
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string pnumber
    * 
    * @param[out] None
    *
    * @return None
    *
    */
void Transaction::SetCity(std::string city) {
 City=city;
}

 /*!
 *\file transaction.cpp
    * 
    * SetLocation()
    * @brief Gets the current location
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::vector<double>
    *
    */
std::vector<double> Transaction::GetLocation(void) {
 return { 122,272 };
}

 /*!
 *\file transaction.cpp
    * 
    * CalculateCommission()
    * @brief Calculates the driver and transportation company's commission
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::vector<double>
    *
    */

double Transaction::CalculateCommission(void) {
 return CalculateShippingRates() * COMISSION_PERCENTAGE_DECIMAL;
}

 /*!
 *\file transaction.cpp
    * 
    * CalculateShippingRates()
    *Calculates the shipping rate for the order
    * 
    * @author Matthew Boote
    *
    * @desc The shipping rate is calculated from the distance the order is to travel and the weight of the item.
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::vector<double>
    *
    */

double Transaction::CalculateShippingRates(void) {
double ShippingRate;
double distance;
double lat;
double lon;
std::vector<double> thislocation;
double latdistance=0;
double londistance=0;
std::vector<std::string> driver_city;
Database citydatabase;

citydatabase.Load(DATA_FOLDER_PATH + "worldcities.csv");		// Load cities database

driver_city=citydatabase.Read(City);	// Get city

try {
if(driver_city.size() == 0) {		// no match
 throw("Unknown city");
}
}
catch(const char *message) {
 std::cout << message;
}

lat=stod(driver_city[CITY_LATITUDE]);
lon=stod(driver_city[CITY_LONGITUDE]);

thislocation=GetLocation();

latdistance *= 110;				// 110 kilometers per degree
londistance *= 111;				// 111 kilometers per degree

if(lat > thislocation[0]) {			// calculate latitude distance
 latdistance=lat-thislocation[0];
}
else
{

 latdistance=thislocation[0]-lat;
}

if(lon > thislocation[1]) {			// calculate longitude distance
 londistance=lon-thislocation[1];
}
else
{
 londistance=thislocation[1]-lon;
}

distance=sqrt((londistance*londistance)+(latdistance*latdistance));	// get distance

return (distance*COST_PER_DISTANCE)+(GetItemWeight()*COST_PER_GRAM);
}

 /*!
 *\file transaction.cpp
    * 
    * CalculateCostOfDelivery()
    * @brief Calculates the cost of delivery
    * 
    * @author Matthew Boote
    *
    * @desc the cost of delivery is (shipping rates+commission)*priority
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::vector<double>
    *
    */

double Transaction::CalculateCostOfDelivery() {
 return (CalculateShippingRates() + CalculateCommission())*GetPriority();
}

 /*!
 *\file transaction.cpp
    * 
    * GetDriverName()
    * @brief Gets the driver's name
    * 
    * @author Matthew Boote
    *
    * @param[in] None
    * 
    * @param[out] None
    *
    * @return std::string
    */

std::string Transaction::GetDriverName(void) {
return DriverName;
}

 /*!
 *\file transaction.cpp
    * 
    * SetDriverName()
    * @brief Sets the driver's name
    * 
    * @author Matthew Boote
    *
    * @param[in] std::string drivername
    * 
    * @param[out] None
    *
    * @return None
    *
    */

void Transaction::SetDriverName(std::string drivername) {
DriverName=drivername;
}

