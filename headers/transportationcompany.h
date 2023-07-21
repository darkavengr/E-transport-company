#include <string>
#include <sstream>

#include "user.h"
#include "transaction.h"
#include "driver.h"

#ifndef TRANSPORTATIONCOMPANY_H_
#define TRANSPORTATIONCOMPANY_H_

class TransportationCompany : public User {
 private:
 std::string CompanyName;

 public:
 TransportationCompany();
 bool SignUpAsTransportationCompany(TransportationCompany transportationcompany);
 double CalculateCommission(TransportationCompany);
 bool ForwardOrder(TransportationCompany);
 std::string GetCompanyName(void);
 bool ReceiveOrder(Transaction transaction);
 void SetCompanyName(std::string companyname);
 TransportationCompany *FindNearestTransportationCompany(std::string city,std::string province,std::string country);
 void SetGoodsTransportationType(std::string GoodsType);
 std::string GetGoodsTransportationType(void); 
};

#endif /* TRANSPORTATIONCOMPANY_H_ */


