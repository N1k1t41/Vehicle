#include <functions/vehiclearg.h>
#include <windows.h>
#include <string>
#include <conio.h>
using namespace vehicle;
using namespace std;
void app(){
	cout << " ____________________________________________________________________" << endl;
	cout << " |                                ����                               |" << endl;
	cout << " �-------------------------------------------------------------------" << endl;
	cout << " | 1 - �������� ���������											  |" << endl;
	cout << " | 2 - �������� ��������� �� �������                                 |" << endl;
	cout << " | 3 - ������� ��������� �� �������                                  |" << endl;
	cout << " | 4 - ������� ������ ����������                                     |" << endl;
	cout << " | 5 - ���������� ��������� ���������                                |" << endl;
	cout << " | 6 - ����� ������� ���������� � ���������� ���������� ���������    |" << endl;
	cout << " | 7 - ����� �� �������                                              |" << endl;
	cout << "  -------------------------------------------------------------------" << endl;
}
Vehicle create_vehicle(){
	Vehicle vehicle;
	string name;
	int type;
	float k, a;
	int typeeng;
	cout << "������� ��� ����������(Railway-1,Water-2,Air-3): ";
	cin >> type;
	if (type != 1 and type != 2 and type != 3)
		throw runtime_error("Unknown type");
	cout << "������� �������� ����������: ";
	getline(cin >> ws, name);
	cout << "������� ������� ����� ���������: ";
	cin >> k;
	if ((VehicleType)type == RAILWAY) {
		vehicle = { (VehicleType)type, name, k };
	}
	else if ((VehicleType)type == WATER) {
		cout << "������� ���������� ����������: ";
		cin >> a;
		vehicle = { (VehicleType)type, name, k, a };
	}
	else if ((VehicleType)type == AIR) {
		cout << "������� ��� ���������(Turboprop-1,Reactive-2): ";
		cin >> typeeng;
		if (typeeng != 1 and typeeng != 2)
			throw runtime_error("Unknown type");
		vehicle = { (VehicleType)type, name, k, (EngineType)typeeng };
	}
	return vehicle;
}
int main()
{
	SetConsoleTitle("Vehicles");
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	VehicleList vehicles;
	Vehicle vehicle;
	app();
	while (true)
	{
		int k;
		cin >> k;
		int index = 0;
		float m, d;
		system("cls");
		app();
		if (k == 7) {
			vehicles.clear();
			break;
		}
		switch (k)
		{
		case 1:
			vehicles.add(create_vehicle());
			break;
		case 2:
			cout << "������� ������ ��� ������� ����������: ";
			cin >> index;
			vehicles.insert(create_vehicle(), index);
			break;
		case 3:
			cout << "������� ������ ����������, ������� ����� �������: ";
			cin >> index;
			vehicles.remove(index);
			break;
		case 4:
			cout << vehicles;
			break;
		case 5:
			cout << "������� ����� ������: ";
			cin >> m;
			cout << "������� ����������: ";
			cin >> d;
			cout << "������� ������ ����������, ��������� ��������� �������� ����� ���������: ";
			cin >> index;
			cout << vehicles[index].calc(m, d);
			break;
		case 6:
			cout << "������� ����� ������: ";
			cin >> m;
			cout << "������� ����������: ";
			cin >> d;
			cout << "������ ���������� � ����������� ���������� ���������: " << vehicle::minim(vehicles, m, d) << endl;
			break;
		}
	}
	return 0;
}
