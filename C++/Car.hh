using namespace std;
int distance(int* cor1,int* cor2);
class Car{
	public:
		Car(int miles_per_gallonn, int size_fueltankk);
		Car();
		~Car();
		int current_fuel;
		int* current_position;
		bool move_to(int coordinates[2]);
		int cost;
		int miles_per_gallon;
		int size_fueltank;
		int distance1(int* cor1,int* cor2);
	private:
	protected:
};
int car_can_move(Car whole_list[], int length, int* coordinates);
class GasStation{
	public:
		GasStation(int* location, int dollar_per_gallon);
		GasStation();
		int* location;
		int dollar_per_gallon;
	private:
	protected:
	
};
Car* car_can_move_modified(Car whole_list_car[], int length_car, int* coordinates, GasStation list_gasstation[], int length_gasstation);
