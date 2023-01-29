#include "Car.hh"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

//distance function 
int distance(int* cor1,int* cor2){
	int first = cor1[0]-cor2[0]; 
	int second = cor1[1]-cor1[1];
	int distance = pow((pow(first, 2) + pow(second, 2) * 1.0),0.5);
	return distance;
}
int Car::distance1(int* cor1,int* cor2){
	int first = cor1[0]-cor2[0]; 
	int second = cor1[1]-cor1[1];
	int distance = pow((pow(first, 2) + pow(second, 2) * 1.0),0.5);
	return distance;
	}
//class Car 
Car::Car(int miles_per_gallonn,int size_fueltankk){ //with parameter
	miles_per_gallon = miles_per_gallonn;
	size_fueltank = size_fueltankk;
	current_fuel = size_fueltank; //full tank 
	int* current_position = new int[2] { 0 , 0 }; //allocate data, starting from origin 
	int cost = 0; 
}
Car::Car(){ //without parameter
	miles_per_gallon = 0;
	size_fueltank = 0;
	current_fuel = size_fueltank; //full tank 
	int* current_position = new int[2] { 0 , 0 }; //allocate data, starting from origin 
	int cost = 0; 
}
Car::~Car(){
	delete current_position; 
}
bool Car::move_to(int coordinates[2]){
	int distance = distance1(coordinates, current_position); 
	int fuel_needed = distance / miles_per_gallon; 
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
//return an array of car that can move and the size (array is stored in a pointer)
int car_can_move(Car whole_list[], int length, int* coordinates){
	int i = 0;
	int k = 0;
	Car* new_list = new Car [length]; 
	for (i; i< length ; i++){
		bool result = whole_list[i].move_to(coordinates); //car moved 
		if (result == true){
			new_list[k] = whole_list[i]; 
			k++; 
		}
	}
	return k; 
}
//class GasStation
GasStation::GasStation(int* locationn, int dollar_per_gallonn){
	location = locationn;
	dollar_per_gallon = dollar_per_gallonn; 
}
GasStation::GasStation(){
	int* location = new int[2] { 0 , 0 };
	dollar_per_gallon = 0; 
}
//helper func for car_can_move_modified
int calculate_cost(int gas_station_index, Car car, GasStation* gas_station_list, int length){
	int cost = 0;
	for (gas_station_index; gas_station_index<length; gas_station_index++){
		cost = distance(car.current_position, gas_station_list[gas_station_index].location) / car.miles_per_gallon * gas_station_list[gas_station_index].dollar_per_gallon + cost;
		car.move_to(gas_station_list[gas_station_index].location);
		car.current_fuel = car.size_fueltank; 
	}
	return cost; 
}
//return the list of car that can move to the destination if fuel some gas, and the cost 
Car* car_can_move_modified(Car whole_list_car[], int length_car, int* coordinates, GasStation list_gasstation[], int length_gasstation){
	GasStation* list_nodes = new GasStation[length_gasstation+1];
	int p = 0;
	for (p; p < length_gasstation; p++){
		list_nodes[p] = list_gasstation[p];
	}
	GasStation destination(coordinates, 0); 
	list_nodes[length_gasstation] = destination; //setting the last element to be the destination
	Car* new_list = new Car [length_car]; //allocate new list of cars 
	int i = 0; //index for car 
	int j = 0; //index for new_list 
	int k = length_gasstation; //index for list_nodes 
	for (i;i<length_car;i++){ //traversing car list 
		if (whole_list_car[i].move_to(list_nodes[length_gasstation+1].location) == true){ //directly go to the destination
			new_list[j] = whole_list_car[i]; //add to the list without cost 
			j++;
			continue; //go to next car 
		}
		for (k-1;k>=0;k--){
			if (distance(list_nodes[k].location, list_nodes[k+1].location)<= whole_list_car[i].miles_per_gallon*whole_list_car[i].size_fueltank){//if car can move from k to k+1
				if (whole_list_car[i].move_to(list_nodes[k].location)==true){ //if car can move to the gas station at index k 
					//calculate the cost 
					whole_list_car[i].cost = calculate_cost(k, whole_list_car[i],list_gasstation, length_gasstation);
					//move to the destination
					whole_list_car[i].current_position = coordinates;
					whole_list_car[i].current_fuel = whole_list_car[i].size_fueltank - distance(coordinates, list_nodes[length_gasstation].location)/ whole_list_car[i].miles_per_gallon;
					new_list[j] = whole_list_car[i];
					j++;
					break; //go to next car 
				}
				else{
				}
			}
			else{//if can't 
				break; //go to next car 
			}
		}
	}
	return new_list;
}

int main(){
	Car pony(5,20);
}