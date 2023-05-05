/* Citation and Sources...

Final Project Milestone 5

Module: Parking.h
Filename: Parking.cpp

Version 1.0
Name: Karan Yatinbhai Dalsania
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h"
#include "Parking.h"
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

namespace sdds
{
	Parking::Parking()
	{
		this->setEmpty();
		for (int i = 0; i < this->numOfSpots; i++)
		{
			this->vh[i] = nullptr;
		}
	}

	Parking::Parking(const char* str,int noOfSpots)
	{
		if (str == nullptr || str[0] == '\0' || noOfSpots > MAX_PARKING_SPOT || noOfSpots < 10)
		{
			this->setEmpty();
			for (int i = 0; i < this->numOfSpots; i++)
			{
				this->vh[i] = nullptr;
			}
			cout << "Error in data file" << endl;
		}
		else
		{
			this->fileName = new char[strlen(str) + 1];
			strcpy(this->fileName, str);
			this->numOfSpots = noOfSpots;

			if (this->loadData() == false)
			{
				cout << "Error in data file" << endl;
			}
			else
			{
				this->mm = "Parking Menu, select an action:";
				this->mm.add("Park Vehicle");
				this->mm.add("Return Vehicle");
				this->mm.add("List Parked Vehicles");
				this->mm.add("Find Vehicle");
				this->mm.add("Close Parking (End of day)");
				this->mm.add("Exit Program");
				this->mm.indent = 0;

				this->mm1 = "Select type of the vehicle:";
				this->mm1.add("Car");
				this->mm1.add("Motorcycle");
				this->mm1.add("Cancel");
				this->mm1.indent = 1;
			}
		}
	}

	Parking::~Parking()
	{
		this->saveDataFile();
		delete[] this->fileName;
		this->setEmpty();

		for (int i = 0; i < MAX_PARKING_SPOT; i++)
		{
			delete this->vh[i];
			this->vh[i] = nullptr;
		}
	}

	bool Parking::isEmpty()const
	{
		return this->fileName == nullptr;
	}

	void Parking::status() const
	{
		int count = 0;
		cout << "****** Valet Parking ******" << endl;
		for (int i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] == nullptr)
			{
				count += 1;
			}
		}
		cout << "*****  Available spots: " << count << "    *****" << endl;
	}

	void Parking::parkVehicle()
	{
		if (this->returnPos())
		{
			int num = this->mm1.run();

			if (num == 3)
			{
				cout << "Cancelled parking" << endl;
			}
			else if (num == 2)
			{
				int index = this->returnPos();
				this->vh[index] = new Motorcycle();
				this->vh[index]->setCsv(false);
				this->vh[index]->read();
				this->vh[index]->setParkingSpot(index + 1);

				cout << endl << "Parking Ticket" << endl;
				this->vh[index]->write();
			}
			else if (num == 1)
			{
				int index = this->returnPos();
				this->vh[index] = new Car();
				this->vh[index]->setCsv(false);
				this->vh[index]->read();
				this->vh[index]->setParkingSpot(index + 1);
				
				cout << endl << "Parking Ticket" << endl;
				this->vh[index]->write();
			}
		}
		else
		{
			cout << "Parking is full";
		}

		cout << endl;
		cin.clear();
	}

	void Parking::returnVehicle()
	{
		char licensePlate[9];
		bool flag = false;
		cout << "Return Vehicle" << endl;

		cout << "Enter License Plate Number: ";

		do
		{
			cin.getline(licensePlate, 8 , '\n');

			int len = strlen(licensePlate);
			if (len < 1 || len > 8)
			{
				cout << "Invalid Licence Plate, try again: ";
			}
			else
				break;
		} while (1);

		for (int i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] != nullptr && *(this->vh[i]) == licensePlate)
			{
				cout << endl << "Returning:" << endl;
				this->vh[i]->write();
				flag = true;
				delete this->vh[i];
				this->vh[i] = nullptr;
				cout << endl;
				break;
			}
		}

		if (flag == false)
		{
			int len = strlen(licensePlate);
			for (int i = 0; i < len; i++)
			{
				licensePlate[i] = toupper(licensePlate[i]);
			}
			cout << endl << "License plate " << licensePlate << " Not found" << endl << endl;
		}

		this->pause();
	}

	void Parking::listParkedVehicle() const
	{
		cout << "*** " << "List of parked vehicles ";
		cout << "***" << endl;
		for (int i = 0; i < this->numOfSpots; i++)
		{
			if(this->vh[i] != nullptr)
			{
				this->vh[i]->write();
				cout << "-------------------------------" << endl;
			}
		}
		this->pause();
	}

	void Parking::findVehicle() const
	{
		char licensePlate[9];
		bool flag = false;

		cout << "Vehicle Search" << endl;

		cout << "Enter Licence Plate Number: ";
		do
		{
			cin.getline(licensePlate, 8);
			int len = strlen(licensePlate);
			if (len < 1 || len > 8)
			{
				cout << "Invalid Licence Plate, try again: ";
			}
			else
				break;     
		} while (1);

		for (int i = 0; i < this->numOfSpots; i++)
		{
			if (this->vh[i] != nullptr && *this->vh[i] == licensePlate)
			{
				cout << endl << "Vechicle found: " << endl;
				flag = true;
				this->vh[i]->write();
				cout << endl;
			}
		}

		if (flag == false)
		{
			int len = strlen(licensePlate);
			for (int i = 0; i < len; i++)
			{
				licensePlate[i] = toupper(licensePlate[i]);
			}
			cout << endl <<"License plate " << licensePlate << " Not found" << endl << endl;
		}

		this->pause();
	}

	bool Parking::closeParking() 
	{
		bool check = false;
		char choice;
		
		if (this->isEmpty())
		{
			cout << "Closing Parking" << endl;
			check = true;
		}
		else
		{
			cout << "This will Remove and tow all remaining vehicles from the parking!" << endl;
			cout << "Are you sure? (Y)es/(N)o: ";
			

			while (!check)
			{
				cin >> choice;

				if (choice == 'Y' || choice == 'y')
				{
					cout << "Closing Parking" << endl;
					for (int i = 0; i < this->numOfSpots; i++)
					{
						if (this->vh[i] != nullptr)
						{
							cout << endl << "Towing request" << endl;
							cout << "*********************" << endl;
							this->vh[i]->write();
							delete this->vh[i];
							this->vh[i] = nullptr;
						}
					}
					check = true;
				}
				else if (choice == 'N' || choice == 'n')
				{
					return false;
				}
				else
				{
					cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
					cin >> choice;
				}
			}
		}

		return check;
	}

	bool Parking::exitProgram() const
	{
		bool check = false;
		char choice;
		cout << "This will terminate the program!" << endl;
		cout << "Are you sure? (Y)es/(N)o: ";

		while (!check)
		{
			cin >> choice;

			if (choice == 'Y' || choice == 'y')
			{
				cout << "Exiting program!" << endl;
				check = true;
			}
			else if (choice == 'N' || choice == 'n')
			{
				return false;
			}
			else
			{
				cout << "Invalid response, only (Y)es or (N)o are acceptable, retry: ";
				cin >> choice;
			}
		}

		return check;
	}

	void Parking::saveDataFile() const
	{
		if (!this->isEmpty())
		{
			ofstream oftr(this->fileName, ios::out);

			//oftr.open(this->fileName);

			if (oftr.is_open())
			{
				for (int i = 0; i < this->numOfSpots; i++)
				{
					if (this->vh[i] != nullptr)
					{
						this->vh[i]->setCsv(true);
						this->vh[i]->write(oftr);
					}
				}
			}

			oftr.close();
		}
	}

	bool Parking::loadData() 
	{
		bool check = false;

		if (this->isEmpty())
			check = true;

		else {
			ifstream iftr(this->fileName, ios::in);
			char readChar;
			Vehicle* vehicleTemp = nullptr;

			if (iftr.is_open())
			{
				while (iftr.get(readChar))
				{
					if (iftr.fail())
						break;
					else
					{
						check = true;
						//string data;
						iftr.ignore(1000, ',');
						if (readChar == 'C')
						{
							vehicleTemp = new Car();
							vehicleTemp->setCsv(true);
							vehicleTemp->read(iftr);
							vehicleTemp->setCsv(false);
						}
						else if (readChar == 'M')
						{
							vehicleTemp = new Motorcycle();
							vehicleTemp->setCsv(true);
							vehicleTemp->read(iftr);
							vehicleTemp->setCsv(false);
						}
					}

					if (iftr)
					{
						if (vehicleTemp != nullptr) {
							int index = vehicleTemp->getParkingSpot();
							this->vh[index - 1] = vehicleTemp;
						}
					}
					else
					{
						delete vehicleTemp;
						vehicleTemp = nullptr;
					}
				}
			}
			else 
				check = true;

			iftr.close();
		}

		return check;
	}

	int Parking::run()
	{
		int choice = 0;
		bool loopRun = true;

		if (!this->isEmpty())
		{
			do
			{
				this->status();
				choice = this->mm.run();

				switch (choice)
				{
				case 1:
					this->parkVehicle();
					this->pause();
					break;

				case 2:
					this->returnVehicle();
					break;

				case 3:
					this->listParkedVehicle();
					break;

				case 4:
					this->findVehicle();
					break;

				case 5:
					if (this->closeParking())
						loopRun = false;
					break;

				case 6:
					if (this->exitProgram())
						loopRun = false;
					break;
				}

			} while (loopRun);
		}

		return this->isEmpty();
	}

	void Parking::setEmpty()
	{
		this->fileName = nullptr;
		this->numOfSpots = 0;
	}
	int Parking::returnPos()const
	{
		int index = -1;
		bool vehicleFound = false;

		for (int i = 0; i < this->numOfSpots && !vehicleFound; i++)
		{
			if (this->vh[i] == nullptr)
			{
				vehicleFound = true;
				index = i;
			}
		}

		return index;
	}

	void Parking::pause()const {
		cout << "Press <ENTER> to continue....";
		cin.ignore(5000, '\n');
	}
};