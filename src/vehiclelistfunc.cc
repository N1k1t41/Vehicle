#include <functions/vehiclearg.h>
#include <stdexcept>
using namespace vehicle;
using namespace std;
VehicleList::VehicleList() :_vehicles(nullptr), _size(0) {}

VehicleList::VehicleList(const VehicleList& copy) :
	_vehicles(new Vehicle* [copy._size]),
	_size(copy._size)
{
	for (int i = 0; i < _size; ++i)
		_vehicles[i] = new Vehicle(*copy._vehicles[i]);
};

void VehicleList::swap(VehicleList& rhs) noexcept{
	std::swap(_size, rhs._size);
	std::swap(_vehicles, rhs._vehicles);
}
VehicleList& VehicleList::operator=(VehicleList copy){
	swap(copy);
	return *this;
}
VehicleList::~VehicleList(){
	clear();
}
void VehicleList::clear() {
	if (_vehicles == nullptr)
		return;
	for (int i = 0; i < _size; ++i)
		delete _vehicles[i];
	_size = 0;
	delete[] _vehicles;
	_vehicles = nullptr;
}
int VehicleList::size() const {
	return _size;
}
const Vehicle& VehicleList::operator[](int index) const {
	if (index < 0 or index >= _size) {
		throw out_of_range("Error");
	}
	return *_vehicles[index];
}
Vehicle& VehicleList::operator[](int index) {
	if (index < 0 or index >= _size) {
		throw out_of_range("Error");
	}
	return *_vehicles[index];
}
void VehicleList::insert(Vehicle vehicle, int index) {
	if (index < 0 or index >= _size)
		throw runtime_error("Error");
	auto vehicles = new Vehicle * [_size + 1];
	for (int i = 0; i < _size; i++) {
		vehicles[i] = _vehicles[i];
	}
	for (int i = _size - 1; i > index; i--) {
		vehicles[i] = vehicles[i - 1];
	}
	vehicles[index] = new Vehicle(vehicle);
	delete[] _vehicles;
	_vehicles = vehicles;
	_size++;
}
void VehicleList::add(Vehicle vehicle) {
	auto vehicles = new Vehicle * [_size + 1];
	for (int i = 0; i < _size; i++) {
		vehicles[i] = _vehicles[i];
	}
	vehicles[_size] = new Vehicle(vehicle);
	delete[] _vehicles;
	_vehicles = vehicles;
	_size++;
}
void VehicleList::remove(int index) {
	if (index < 0 or index >= _size) {
		throw runtime_error("Error");
	}
	delete _vehicles[index];
	for (int i = index; i < _size - 1; i++) {
		_vehicles[i] = _vehicles[i + 1];
	}
	_size--;
}
const Vehicle& VehicleList::get_vehicle(int index) const {
	if (index < 0 or index >= _size)
		throw runtime_error("Error");
	return *_vehicles[index];
}


std::ostream& vehicle::operator<<(std::ostream& stream, const VehicleList& vehicles) {
	stream << vehicles.size() << " Vehicles: " << endl;
	for (int i = 0; i < vehicles.size(); i++) cout << "  " << i + 1 << ") " << vehicles.get_vehicle(i);
	return stream;
}