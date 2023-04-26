#include <functions/vehiclearg.h>
#include <windows.h>
#include <string>
#include <conio.h>
using namespace vehicle;
using namespace std;
void app(){
	cout << " ____________________________________________________________________" << endl;
	cout << " |                                ћеню                               |" << endl;
	cout << " Ч-------------------------------------------------------------------" << endl;
	cout << " | 1 - добавить транспорт											  |" << endl;
	cout << " | 2 - вставить транспорт по индексу                                 |" << endl;
	cout << " | 3 - удалить транспорт по индексу                                  |" << endl;
	cout << " | 4 - вывести список транспорта                                     |" << endl;
	cout << " | 5 - рассчитать стоимость перевозки                                |" << endl;
	cout << " | 6 - поиск первого траснпорта с наименьшей стоимостью перевозки    |" << endl;
	cout << " | 7 - выйти из системы                                              |" << endl;
	cout << "  -------------------------------------------------------------------" << endl;
}
Vehicle create_vehicle(){
	Vehicle vehicle;
	string name;
	int type;
	float k, a;
	int typeeng;
	cout << "¬ведите тип транспорта(Railway-1,Water-2,Air-3): ";
	cin >> type;
	if (type != 1 and type != 2 and type != 3)
		throw runtime_error("Unknown type");
	cout << "¬ведите название транспорта: ";
	getline(cin >> ws, name);
	cout << "¬ведите базовый тариф перевозки: ";
	cin >> k;
	if ((VehicleType)type == RAILWAY) {
		vehicle = { (VehicleType)type, name, k };
	}
	else if ((VehicleType)type == WATER) {
		cout << "¬ведите поощр€ющий коэффицент: ";
		cin >> a;
		vehicle = { (VehicleType)type, name, k, a };
	}
	else if ((VehicleType)type == AIR) {
		cout << "¬ведите тип двигател€(Turboprop-1,Reactive-2): ";
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
			cout << "¬ведите индекс дл€ вставки транспорта: ";
			cin >> index;
			vehicles.insert(create_vehicle(), index);
			break;
		case 3:
			cout << "¬ведите индекс транспорта, который нужно удалить: ";
			cin >> index;
			vehicles.remove(index);
			break;
		case 4:
			cout << vehicles;
			break;
		case 5:
			cout << "¬ведите массу товара: ";
			cin >> m;
			cout << "¬ведите рассто€ние: ";
			cin >> d;
			cout << "¬ведите индекс транспорта, стоимость перевозки которого нужно посчитать: ";
			cin >> index;
			cout << vehicles[index].calc(m, d);
			break;
		case 6:
			cout << "¬ведите массу товара: ";
			cin >> m;
			cout << "¬ведите рассто€ние: ";
			cin >> d;
			cout << "»ндекс транспорта с минимальной стоимостью перевозки: " << vehicle::minim(vehicles, m, d) << endl;
			break;
		}
	}
	return 0;
}
