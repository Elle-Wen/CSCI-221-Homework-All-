#include "Vehicle.hh"

using namespace std;

Bus::Bus(int max_passengerss, int gas_mileage_penaltyy, vector<int> stop_numberr){ //the list is always sorted in ascending order 
	max_passengers = max_passengerss;
	gas_mileage_penalty = gas_mileage_penaltyy;
	stop_number = stop_numberr; 
}

// if the stop list is {4,5,6,7,8} and the starting stop is 6, it returns {6,7,8,4,5}
list<int> Bus:: generate_route(int starting_stop){
	list<int> route;
	for (int i=0; i < stop_number.size(); ++i){ //to assign the stops that are greater than the starting stop
		if (stop_number[i]>= starting_stop){
			route.push_back(stop_number[i]); 
		}
	}
	for (int i=0; i < stop_number.size(); ++i){ //to assign the stops that are less than the starting stop 
		if (stop_number[i]< starting_stop){
			route.push_back(stop_number[i]);
		}
	}
	return route;
}
//overwrite the old method by taking into consideration of mileage_penalty
bool Bus:: move_to(int coordinates[2]){
	int distance = distance1(coordinates, current_position); 
	int fuel_needed = distance / miles_per_gallon + gas_mileage_penalty*stop_number.size(); 
	if (fuel_needed > current_fuel){
		return false; 
	}
	else{
		current_fuel = current_fuel - fuel_needed;
		current_position[0] = coordinates[0];
		current_position[1] = coordinates[1];
		return true; 
	}
}

MedicalCenter::MedicalCenter(map<string, int> providerss, map<string, int> patientss){
	providers = providerss;
	patients = patientss;
}

Ambulance::Ambulance(int capacity_patientss,int capacity_patients_providerss,int gas_mileage_penaltyy,int current_peoplee){
	capacity_patients = capacity_patientss;
	capacity_patients_providers = capacity_patients_providerss;
	gas_mileage_penalty = gas_mileage_penaltyy;
	current_people = current_peoplee;
}

bool Ambulance:: move_to(int coordinates[2]){
	int distance = distance1(coordinates, current_position); 
	int fuel_needed = distance / miles_per_gallon + gas_mileage_penalty*current_people; 
	if (fuel_needed > current_fuel){
		return false; 
	}
	else{
		current_fuel = current_fuel - fuel_needed;
		current_position[0] = coordinates[0];
		current_position[1] = coordinates[1];
		return true; 
	}
}

vector<unique_ptr<Car>> filter_car(vector<unique_ptr<Car>>& cars, int coordinates[2]){
	vector<unique_ptr<Car>> result;
	for (const auto& car: cars){
		if (car->move_to(coordinates)){
			unique_ptr<Car> copy = make_unique<Car>(*car);
			copy->move_to(coordinates);
			result.push_back(move(copy));
		}
	}
	return result; 
}