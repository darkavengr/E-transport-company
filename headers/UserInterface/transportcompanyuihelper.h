#ifndef TRANSPORTCOMPANYUIHELPER_H
#define TRANSPORTCOMPANYUIHELPER_H
#include <boost/uuid/uuid.hpp>

using namespace boost::uuids;

class QTableWidget;
class TransportationCompany;
class Message;

class TransportCompanyUIHelper
{
private:
    TransportationCompany* transportCompany;
    Message* message;

public:
    TransportCompanyUIHelper(TransportationCompany* transportCompany, Message* message);


    void populateTableView(QTableWidget* tableWidget);


    void CancelOrder(uuid id);
    void DispatchOrder(uuid id);
};

#endif // TRANSPORTCOMPANYUIHELPER_H
