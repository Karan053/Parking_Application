/* Citation and Sources...

Final Project Milestone 5

Module: Menu.h
Filename: Menu.cpp

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
#include <cstring>

using namespace std;

namespace sdds
{
	void Menu::Indentspace()const
	{
		for (int j = 0; j < this->indent; j++)
		{
			cout << "    ";
		}
	}
	MenuItem::MenuItem()
	{
		this->menuData[0] = '\0';
	}

	MenuItem::MenuItem(const char* str)
	{
		if (str == nullptr)
			this->menuData[0] = '\0';

		else
		{
			if (strlen(str) > 50)
			{
				strncpy(this->menuData, str, 50);
			}
			else
				strcpy(this->menuData, str);
		}
	}

	ostream& MenuItem::display(ostream& ostr) const
	{
		if (this->menuData[0] != '\0')
		{
			ostr << this->menuData << endl;
		}

		return ostr;
	}

	Menu::Menu()
	{
		this->menuStr[0] = '\0';
		this->indent = 0;
		this->count = 0;
	}

	Menu::Menu(const char* str, int num)
	{
		if (str == nullptr)
		{
			this->menuStr[0] = '\0';
			this->indent = 0;
			this->count = 0;
		}

		else
		{
			this->indent = num;
			this->count = 0;
			if (strlen(str) > 50)
			{
				strncpy(this->menuStr, str, 50);
			}
			else

				strcpy(this->menuStr, str);
		}
	}

	Menu::operator bool() const
	{
		return this->menuStr[0] != '\0';
	}

	bool Menu::isEmpty() const
	{
		return this->menuStr[0] == '\0';
	}

	ostream& Menu::display(ostream& ostr) const
	{
		if (isEmpty())
			ostr << "Invalid Menu!" << endl;

		else
		{
			Menu::Indentspace();
			ostr << this->menuStr << endl;

			bool flag = false;
			for (int i = 0; i < this->count; i++)
			{
				if (this->mItem[i].menuData[0] == '\0')
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				ostr << "No Items to display!" << endl;
			}
			else
			{
				for (int i = 0; i < this->count; i++)
				{
					Menu::Indentspace();
					ostr << i + 1 << "- ";
					this->mItem[i].display();
				}
				Menu::Indentspace();
				ostr << "> ";
			}

		}

		return ostr;
	}

	Menu& Menu::operator=(const char* str)
	{
		if (str == nullptr)
			this->menuStr[0] = '\0';

		else
		{
			if (strlen(str) > 50)
			{
				strncpy(this->menuStr, str, 50);
			}
			else
				strcpy(this->menuStr, str);
		}

		return *this;
	}

	void Menu::add(const char* str)
	{
		if (str == nullptr)
		{
			for (int i = 0; i < this->count; i++)
			{
				this->mItem[i].menuData[0] = '\0';
			}
			this->menuStr[0] = '\0';
		}

		else
		{
			if (this->count < MAX_NO_OF_ITEMS && bool(*this))
			{
				if (strlen(str) > 50)
				{
					strncpy(this->mItem[this->count].menuData, str, 50);
					this->count++;
				}
				else
				{
					strcpy(this->mItem[this->count].menuData, str);
					this->count++;
				}
			}
		}
	}

	Menu& Menu::operator<<(const char* str)
	{
		Menu::add(str);

		return *this;
	}

	int Menu::run() const
	{
		int num = 0;
		bool check = true;

		Menu::display();
		if (this->mItem[0].menuData[0] == '\0' || isEmpty())
		{
			return 0;
		}
		else
		{
			while (check)
			{
				cin >> num;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid Integer, try again: ";
				}
				else if ((num > this->count || num < 1))
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid selection, try again: ";
				}
				else
				{
					cin.ignore(1000, '\n');
					check = false;
				}

			}
		}

		return num;
	}

	void Menu::clear()
	{
		this->menuStr[0] = '\0';
		for (int i = 0; i < this->count; i++)
		{
			this->mItem[i].menuData[0] = '\0';
		}
		this->indent = 0;
	}

	Menu::operator int() const
	{
		return this->run();
	}
}
