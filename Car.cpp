/* Citation and Sources...

Final Project Milestone 5

Module: Car.h
Filename: Car.cpp

Version 1.0
Name: Karan Yatinbhai Dalsania
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include "Car.h"
#include <cstring>
#include <string>

using namespace std;

namespace sdds {

	Car::Car() : Vehicle()
	{
		this->carWash = false;
	}

	Car::Car(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel)
	{
		if (licensePlate == nullptr || licensePlate[0] == '\0' || makeModel == nullptr || makeModel[0] == '\0')
		{
			this->setEmpty();
			this->carWash = false;
		}
	}

	Car::Car(const Car& c) : Vehicle(c)
	{
		this->carWash = c.carWash;
	}

	//Car::~Car()
	//{
	//	this->carWash = false;
	//}
	std::ostream& Car::writeType(std::ostream& ostr) const
	{
		if (this->isCsv())
			ostr << "C,";
		else
			ostr << "Vehicle type: Car" << endl;

		return ostr;
	}

	std::istream& Car::read(std::istream& istr)
	{
		char opt[3];

		if (this->isCsv())
		{
			Vehicle::read(istr);
			istr >> this->carWash;
			istr.ignore(1000, '\n');
		}
		else
		{
			cout << endl << "Car information entry" << endl;
			Vehicle::read(istr);
			cout << "Carwash while parked? (Y)es/(N)o: ";
			do
			{
				istr >> opt;
				istr.ignore(1000, '\n');

				int len = strlen(opt);
				if (len > 1)
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (toupper(opt[0]) == 'Y')
				{
					this->carWash = true;
					break;
				}
				else if (toupper(opt[0]) == 'N')
				{
					this->carWash = false;
					break;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}

			} while (1);
		}

		return istr;
	}

	std::ostream& Car::write(std::ostream& ostr) const
	{
		if (this->isEmpty())
		{
			ostr << "Invalid Car Object" << endl;;
		}
		else
		{
			Vehicle::write(ostr);
			if (this->isCsv())
			{
				ostr << this->carWash << endl;
			}
			else
			{
				if (this->carWash)
					ostr << "With Carwash" << endl;
				else
					ostr << "Without Carwash" << endl;
			}
		}

		return ostr;
	}
}