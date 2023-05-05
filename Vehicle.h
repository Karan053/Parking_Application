#ifndef SDDS_Vehicle
#define SDDS_Vehicle
#include "ReadWritable.h"

namespace sdds
{
	class Vehicle : public ReadWritable
	{
		char licensePlate[9];
		char* makeModel;
		int parkingSpot;

	public:
		//default constructor
		Vehicle();
		//parameterized constructor
		Vehicle(const char* licensePlate, const char* make);
		//destructor
		~Vehicle();

		//copy constructor
		Vehicle(const Vehicle& vClass);
		//assignment operator
		Vehicle& operator=(const Vehicle& vClass);
		//getParkingSpot
		int getParkingSpot()const;
		//setParkingSpot
		void setParkingSpot(const int& number);

		//double equalto operator for comparing a object to object
		bool operator==(const Vehicle& vh)const;
		//operator overloading for the object3
		bool operator==(const char* licensePlate);
		//read function overloaded from the base class
		virtual std::istream& read(std::istream& istr = std::cin);
		//writetype class
		virtual std::ostream& writeType(std::ostream& ostr)const = 0;
		//write function overloaded from the base class
		virtual std::ostream& write(std::ostream& ostr = std::cout)const;

		//extra helper function
		bool checkLen(const char* str)const;
		//convert to upper function
		void strUpper(char* str)const;

	protected:
		//setEmpty
		void setEmpty();
		//isEmpty 
		bool isEmpty()const;
		//getLicensePlate
		const char* getLicensePlate()const;
		//getMakeModel
		const char* getMakeModel()const;
		//setMakeModel
		void setMakeModel(const char* make);
	};
};

#endif // !SDDS_Vehicle