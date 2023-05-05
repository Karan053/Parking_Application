/* Citation and Sources...

Final Project Milestone 5

Module: ReadWritable.h
Filename: ReadWritable.cpp

Version 1.0
Name: Karan Yatinbhai Dalsania
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
-----------------------------------------------------------
*/

#define _CRT_SECURE_NO_WARNINGS
#include "ReadWritable.h"

using namespace std;

namespace sdds
{

	ReadWritable::ReadWritable()
	{
		this->commaSeparated = false;
	}

	bool ReadWritable::isCsv() const
	{
		return this->commaSeparated;
	}

	void ReadWritable::setCsv(bool value)
	{
		this->commaSeparated = value;
	}

	std::ostream& operator<<(std::ostream& ostr, const ReadWritable& rwd)
	{
		return rwd.write(ostr);
	}

	std::istream& operator>>(std::istream& istr, ReadWritable& rwd)
	{
		return rwd.read(istr);
	}
};