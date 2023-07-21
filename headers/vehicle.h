//
// Vehicle.h
//

#include <string>
#include <sstream>

class Vehicle {
private:
 std::string registration;
 std::string vehicletype;
 double weight;		// In tonnes
 double height;
 
public:
 Vehicle();
 std::string GetRegistration();
 std::string GetVehicleType();
 double GetWeight();
 double GetHeight();
 void SetRegistration(std::string reg);
 void SetVehicleType(std::string vt);
 void SetWeight(int wt);
 void SetHeight(int ht);
 bool AddVehicle(Vehicle vehicle);
 bool ValidateRegistration(std::string regnumber);
};


