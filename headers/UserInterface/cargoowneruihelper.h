#ifndef CARGOOWNERUIHELPER_H
#define CARGOOWNERUIHELPER_H

class QTableWidget;
class CargoOwner;

class CargoOwnerUIHelper
{
private:
    CargoOwner* cargoOwner;
    
public:
    CargoOwnerUIHelper(CargoOwner* cargoOwner);
    
    void populateTableView(QTableWidget* tableWidget);
};

#endif // CARGOOWNERUIHELPER_H
