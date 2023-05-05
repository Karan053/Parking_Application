#ifndef SDDS_Parking
#define SDDS_Parking
#include <iostream>
#include "Menu.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
	const int MAX_PARKING_SPOT = 100;

	class Parking
	{
		Menu mm{};
		Menu mm1{};

		Vehicle* vh[MAX_PARKING_SPOT]{};
		int numOfSpots{};

		char* fileName{};
		char selection[51]{};

		//private member function
		bool isEmpty()const;
		//parking Status function
		void status()const;
		//parking vehicle functions
		void parkVehicle();
		//returning the vehicle
		void returnVehicle();
		//listing the parked vehicle
		void listParkedVehicle()const;
		//finding a vehicle
		void findVehicle()const;
		//close parking function
		bool closeParking();
		//exit program
		bool exitProgram()const;
		//save data file function
		void saveDataFile()const;

	public:
		//constructor
		Parking();
		Parking(const char* str,int noOfSpots);
		//destructor
		~Parking();
		//load data file function
		bool loadData();

		//copy and assignment function
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;

		//run function
		int run();
		//set empty
		void setEmpty();
		//return empty spot position to the user
		int returnPos()const;
		//pause
		void pause()const;
		
	};
}

#endif 
