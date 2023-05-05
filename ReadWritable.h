#ifndef SDDS_ReadWritable
#define SDDS_ReadWritable
#include <iostream>

namespace sdds
{
	class ReadWritable
	{
		bool commaSeparated;

	public:
		//constructor
		ReadWritable();
		//destructor
		virtual ~ReadWritable() {};
		//check for the comma separated values flag
		bool isCsv()const;
		//This function set the Comma Separated Values flag to the incoming bool value.
		void setCsv(bool value);

		//virtual read and write classes
		virtual std::ostream& write(std::ostream& ostr = std::cout)const = 0;
		virtual std::istream& read(std::istream& istr = std::cin) = 0;

		//insertion and extraction operator
		friend std::ostream& operator<<(std::ostream& ostr, const ReadWritable& rwd);
		friend std::istream& operator>>(std::istream& istr, ReadWritable& rwd);
	};
};

#endif // !SDDS_ReadWritable