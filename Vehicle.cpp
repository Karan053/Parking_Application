/* Citation and Sources...

Final Project Milestone 5

Module: Vehicle.h
Filename: Vehicle.cpp

Version 1.0
Name: Karan Yatinbhai Dalsania
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Vehicle.h"
#include <string>
#include <cstring>

using namespace std;

namespace sdds
{
	Vehicle::Vehicle() : ReadWritable()
	{
		this->setEmpty();
	}

	Vehicle::Vehicle(const char* licensePlate, const char* makeModel)
	{
		if (licensePlate == nullptr || licensePlate[0] == '\0' || makeModel == nullptr || makeModel[0] == '\0' || checkLen(licensePlate) || checkLen(makeModel))
		{
			this->setEmpty();
		}
		else
		{
			strcpy(this->licensePlate, licensePlate);
			this->makeModel = new char[strlen(makeModel) + 1];
			strcpy(this->makeModel, makeModel);
			this->parkingSpot = 0;
		}
	}

	Vehicle::~Vehicle()
	{
		delete[] this->makeModel;
		this->setEmpty();
	}

	Vehicle::Vehicle(const Vehicle& vClass)
	{
		this->setEmpty();

		strcpy(this->licensePlate, vClass.licensePlate);
		this->makeModel = new char[strlen(vClass.makeModel) + 1];
		strcpy(this->makeModel, vClass.makeModel);
		this->parkingSpot = vClass.parkingSpot;
		this->setCsv(vClass.isCsv());
	}

	Vehicle& Vehicle::operator=(const Vehicle& vClass)
	{
		if (this != &vClass)
		{
			delete[] this->makeModel;
			this->setEmpty();

			strcpy(this->licensePlate, vClass.licensePlate);
			this->makeModel = new char[strlen(vClass.makeModel) + 1];
			strcpy(this->makeModel, vClass.makeModel);
			this->parkingSpot = vClass.parkingSpot;
			this->setCsv(vClass.isCsv());
		}

		return *this;
	}

	void Vehicle::setEmpty()
	{
		this->licensePlate[0] = '\0';
		this->makeModel = nullptr;
		this->parkingSpot = -1;
	}

	bool Vehicle::isEmpty() const
	{
		return this->licensePlate[0] == '\0';
	}

	const char* Vehicle::getLicensePlate() const
	{
		return this->licensePlate;
	}

	const char* Vehicle::getMakeModel() const
	{
		return this->makeModel;
	}

	void Vehicle::setMakeModel(const char* makeModel)
	{
		if (makeModel == nullptr || makeModel[0] == '\0')
		{
			delete[] this->makeModel;
			this->setEmpty();
		}
		else
		{
			delete[] this->makeModel;
			this->makeModel = nullptr;

			strcpy(this->makeModel, makeModel);
		}
	}

	int Vehicle::getParkingSpot() const
	{
		return this->parkingSpot;
	}

	void Vehicle::setParkingSpot(const int& num)
	{
		if (num < 0)
		{
			delete[] this->makeModel;
			this->setEmpty();
		}
		else
			this->parkingSpot = num;
	}

	bool Vehicle::operator==(const Vehicle& vh) const
	{
		char temp[9], temp1[9];

		strcpy(temp, this->licensePlate);
		strcpy(temp1, vh.licensePlate);

		strUpper(temp);
		strUpper(temp1);

		bool check = false;
		if (strcmp(temp1, temp))
			return check;
		else
			check = true;

		return check;
	}

	bool Vehicle::operator==(const char* licensePlate)
	{
		bool check = false;

		if (licensePlate == nullptr || licensePlate[0] == '\0' || checkLen(licensePlate))
			return check;
		else
		{
			char temp[9];
			strcpy(temp, licensePlate);
			strUpper(temp);
			if (strcmp(this->licensePlate, temp))
				check = false;
			else
				check = true;
			//strUpper(this->licensePlate);
		}

		return check;
	}

	std::istream& Vehicle::read(std::istream& istr)
	{
		delete[] this->makeModel;
		this->setEmpty();

		if (this->isCsv())
		{
			istr >> this->parkingSpot;
			istr.ignore(1000, ',');
			istr.getline(this->licensePlate, 8, ',');
			strUpper(this->licensePlate);

			char temp[60]{};
			istr.getline(temp, 60, ',');

			int len = strlen(temp);
			this->makeModel = new char[len + 1];
			strcpy(this->makeModel, temp);
			//istr.clear();
		}
		else
		{
			bool flag = true;
			char temp[60]{};

			delete[] this->makeModel;
			this->setEmpty();

			cout << "Enter License Plate Number: ";
			do
			{
				istr.getline(this->licensePlate, 8, '\n');

				if (istr.fail())
				{
					istr.clear();
					istr.ignore(1000, '\n');
					cout << "Invalid License Plate, try again: ";
				}
				else
				{
					flag = false;
					strUpper(this->licensePlate);
				}
			} while (flag);

			flag = true;

			cout << "Enter Make and Model: ";
			do
			{
				istr.getline(temp, 60, '\n');

				if (istr.fail() || strlen(temp) < 2)
				{
					cout << "Invalid Make and model, try again: ";
				}
				else
				{
					flag = false;
					this->makeModel = new char[strlen(temp) + 1];
					strcpy(this->makeModel, temp);
				}
			} while (flag);

			this->parkingSpot = 0;
		}
		if (istr.fail())
		{
			istr.clear();
			istr.ignore(1000, '\n');
			delete[] this->makeModel;
			this->setEmpty();
		}

		return istr;
	}


	std::ostream& Vehicle::write(std::ostream& ostr) const
	{
		if (this->isEmpty())
		{
			ostr << "Invalid Vehicle Object" << endl;
		}
		else
		{
			this->writeType(ostr);
			if (this->isCsv())
			{
				ostr << this->parkingSpot << ",";
				ostr << this->licensePlate << ",";
				ostr << this->makeModel << ",";
			}
			else
			{
				ostr << "Parking Spot Number: ";
				if (this->getParkingSpot() <= 0)
					ostr << "N/A" << endl;
				else
					ostr << this->parkingSpot << endl;

				ostr << "License Plate: " << this->getLicensePlate() << endl;
				ostr << "Make and Model: " << this->getMakeModel() << endl;
			}
		}
		return ostr;
	}

	bool Vehicle::checkLen(const char* str) const
	{
		bool check = false;
		int len = strlen(str);
		if (len > 8 || len < 2)
			check = true;

		return check;
	}

	void Vehicle::strUpper(char* str)const
	{
		int len = strlen(str);
		for (int i = 0; i < len; i++)
		{
			str[i] = toupper(str[i]);
		}
	}
};