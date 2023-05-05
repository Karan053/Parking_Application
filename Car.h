#ifndef SDDS_Car
#define SDDS_Car
#include <iostream>
#include "Vehicle.h"

namespace sdds
{
	class Car : public Vehicle
	{
		bool carWash;

	public:
		//constructor
		Car();
		Car(const char* licensePlate, const char* makeModel);

		//copy constructor
		Car(const Car& c);
		//destructor
		/*~Car();*/

		//overriding pure virtual function in the derived class
		std::ostream& writeType(std::ostream& ostr)const;
		//overriding read function 
		std::istream& read(std::istream& istr = std::cin);
		//overloading the write class
		std::ostream& write(std::ostream& ostr = std::cout)const;
	};

}

#endif // !SDDS_Car
