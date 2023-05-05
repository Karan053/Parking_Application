#ifndef SDDS_Menu
#define SDDS_Menu
#include <iostream>

namespace sdds
{
	const int MAX_NO_OF_ITEMS = 10;

	class Menu;

	class MenuItem
	{
		friend class Menu;
		char menuData[51];

		//member function
		MenuItem();
		MenuItem(const char* str);
		MenuItem(const MenuItem&) = delete;
		void operator=(const MenuItem&) = delete;
		std::ostream& display(std::ostream& ostr = std::cout)const;
	};

	class Menu
	{
		char menuStr[51];
		int count;
		MenuItem mItem[MAX_NO_OF_ITEMS];

	public:
		int indent;
		Menu();
		Menu(const char* str, int num = 0);

		//indentation function

		//operator overloading
		operator int()const;
		operator bool()const;
		//copy constructor
		Menu(const Menu&) = delete;
		//check the empty state of the code
		bool isEmpty()const;
		//display function
		std::ostream& display(std::ostream& ostr = std::cout)const;
		//assignment operator
		Menu& operator=(const char* str);
		//add function
		void add(const char* str);
		//left shift operator overloading
		Menu& operator<<(const char* str);
		//run function
		int run()const;
		//clear function
		void clear();

		//helping function
		void Indentspace()const;
	};
}
#endif