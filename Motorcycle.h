#ifndef SDDS_Motorcycle
#define SDDS_Motorcycle
#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Motorcycle : public Vehicle
	{
		bool hasSideCar;

	public:
		//constructor
		Motorcycle();
		Motorcycle(const char* licensePlate, const char* makeModel);

		//copy constructor
		Motorcycle(const Motorcycle& mcycle);

		//destructor
		~Motorcycle();

		//overriding the writetype function in the derived class
		std::ostream& writeType(std::ostream& ostr)const;
		//overiding the read function
		std::istream& read(std::istream& istr = std::cin);
		//overriding the write function
		std::ostream& write(std::ostream& ostr = std::cout)const;
	};
}

#endif // !SDDS_Motorcycle
