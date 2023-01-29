#include "Car.cpp"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <memory>
#include <cstdlib>
using namespace std;

class Bus : public Car {
	public:
		int max_passengers;
		int gas_mileage_penalty;
		vector<int> stop_number;
		Bus(int max_passengers, int gas_mileage_penalty, vector<int> stop_number);
		list<int> generate_route(int starting_stop); 
		bool move_to(int coordinates[2]);
};

class MedicalCenter{
	public: 
		map<string, int> providers;
		map<string, int> patients;
		MedicalCenter(map<string, int> providers, map<string, int> patients);
};

class Ambulance : public Car, public MedicalCenter{
	public:
		Ambulance(int capacity_patients, int capacity_patients_providers, int gas_mileage_penalty, int current_people);
		int capacity_patients;
		int capacity_patients_providers;
		int gas_mileage_penalty; 
		int current_people;
		bool move_to(int coordinates[2]);
};

vector<unique_ptr<Car>> filter_car(vector<unique_ptr<Car>>& cars, int coordinates[2]);