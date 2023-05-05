/* Citation and Sources...

Final Project Milestone 5

Module: Motorcycle.h
Filename: Motorcycle.cpp

Version 1.0
Name: Karan Yatinbhai Dalsania
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#include <cstring>
#include "Motorcycle.h"

using namespace std;

namespace sdds
{
	Motorcycle::Motorcycle() : Vehicle()
	{
		this->hasSideCar = false;
	}

	Motorcycle::Motorcycle(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel)
	{
		if (licensePlate == nullptr || licensePlate[0] == '\0' || makeModel == nullptr || makeModel[0] == '\0')
		{
			this->setEmpty();
			this->hasSideCar = false;
		}
	}

	Motorcycle::Motorcycle(const Motorcycle& mcycle) : Vehicle(mcycle)
	{
		this->hasSideCar = mcycle.hasSideCar;
	}

	Motorcycle::~Motorcycle()
	{
		this->hasSideCar = false;
	}

	std::ostream& Motorcycle::writeType(std::ostream& ostr) const
	{
		if (this->isCsv())
			ostr << "M,";
		else
			ostr << "Vehicle type: Motorcycle" << endl;

		return ostr;
	}

	std::istream& Motorcycle::read(std::istream& istr)
	{
		char choice[3]{};

		if (this->isCsv())
		{
			Vehicle::read(istr);
			istr >> this->hasSideCar;
			istr.ignore(1000, '\n');
		}
		else
		{
			cout << endl << "Motorcycle information entry" << endl;
			Vehicle::read(istr);
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			do
			{
				istr >> choice;
				istr.ignore(1000, '\n');

				int len = strlen(choice);
				if (len > 1)
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				}
				else if (toupper(choice[0]) == 'Y')
				{
					this->hasSideCar = true;
					break;
				}
				else if (toupper(choice[0]) == 'N')
				{
					this->hasSideCar = false;
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

	std::ostream& Motorcycle::write(std::ostream& ostr) const
	{
		if (this->isEmpty())
		{
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else
		{
			Vehicle::write(ostr);
			if (this->isCsv())
				ostr << this->hasSideCar << endl;
			else
			{
				if (this->hasSideCar)
					ostr << "With Sidecar" << endl;
			}
		}

		return ostr;
	}

}