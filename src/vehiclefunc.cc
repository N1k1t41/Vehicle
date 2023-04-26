#include <functions/vehiclearg.h>
#include <cmath>
#include <string>
#include <stdexcept>
using namespace std;
using namespace vehicle;
Vehicle::Vehicle() :_type(RAILWAY), _name(""), _k(0), _a(0), _engine(TURB) {}
Vehicle::Vehicle(VehicleType type, string name, float k) :_type(type), _name(name), _k(k) {}
Vehicle::Vehicle(VehicleType type, string name, float k, float a) :_type(type), _name(name), _k(k), _a(a) {}
Vehicle::Vehicle(VehicleType type, string name, float k, EngineType engine) :_type(type), _name(name), _k(k), _engine(engine) {}
string Vehicle::get_name() const { return _name; }
float Vehicle::get_k() const { return _k; }
float Vehicle::get_a() const { return _a; }
std::string Vehicle::get_engine() const {
    switch (_engine)
    {
    case EngineType::TURB:
        return "Turboprop";
    case EngineType::REACT:
        return "Reactive";
    default:
        throw runtime_error("Unknown type");
    }
}
std::string Vehicle::get_type() const {
    switch (_type)
    {
    case VehicleType::RAILWAY:
        return "Railway";
    case VehicleType::WATER:
        return "Water";
    case VehicleType::AIR:
        return "Air";
    default:
        throw runtime_error("Unknown type");
    }
}
float Vehicle::calc(float m, float d) {
    switch (_type) {
    case RAILWAY:
        return _k * m * d;
    case WATER:
        return _k * m * d * pow(_a, d / 5000);
    case AIR:
        switch (_engine) {
        case TURB:
            if (d < 1000) return _k * m * d * 0.5;
            else return _k * m * d * 1.5;
        case REACT:
            if (d < 1000) return _k * m * d * 1.5;
            else return _k * m * d * 0.5;
        }
    }
}
int vehicle::minim(VehicleList& vehicles, float m, float d) {
    int s = vehicles.size();
    int index = 0;
    float min_price = vehicles[0].calc(m, d);
    for (int i = 1; i < s; i++) {
        const float price = vehicles[i].calc(m, d);
        if (price < min_price) {
            index = i;
            min_price = price;
        }
    }
    return index;
}
std::ostream& vehicle::operator<<(std::ostream& stream, const Vehicle& vehicle) {
    if (vehicle.get_type() == "Railway")
        stream << "Vehicle Type: " << vehicle.get_type() << "\n" << "     Vehicle Name: " << vehicle.get_name() << "\n" << "     Basic Rate: " << vehicle.get_k() << "\n";
    else if (vehicle.get_type() == "Water")
        stream << "Vehicle Type: " << vehicle.get_type() << "\n" << "     Vehicle Name: " << vehicle.get_name() << "\n" << "     Basic Rate: " << vehicle.get_k() << "\n" << "     Encouraging Coefficient: " << vehicle.get_a() << "\n";
    else if (vehicle.get_type() == "Air")
        stream << "Vehicle Type: " << vehicle.get_type() << "\n" << "     Vehicle Name: " << vehicle.get_name() << "\n" << "     Basic Rate: " << vehicle.get_k() << "\n" << "     Engine Type: " << vehicle.get_engine() << "\n";
    return stream;
}