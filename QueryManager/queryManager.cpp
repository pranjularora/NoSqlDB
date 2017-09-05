/////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - Main Program                                //
//                                                                 //
// Pranjul Arora, CSE687 - Object Oriented Design, Spring 2017     //
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "queryManager.h"
// Test Stub
#ifdef Query_Manager
using StrData = std::string;
int main()
{
	noSqlDB<StrData> db;
	Element<StrData> elem1;
	elem1.name = "pranjul";
	elem1.category = "Test1";
	elem1.timeDate = "2017-02-03 04:19:33";
	elem1.data = "Elem1 data";

	db.save("pranjul", elem1);

	Element<StrData> elem2;
	elem2.name = "arora";
	elem2.category = "Test2";
	elem2.data = "Elem2 data";
	elem2.timeDate = "2017-02-01 04:19:33";
	elem2.children.push_back(elem2.name);

	db.save("key2", elem2);

	std::cout << "\n  Query: 1";
	std::cout << "\n ------------------------\n";
	Query<StrData> queryManager;
	Element<StrData> elemQ1 = queryManager.query_one(db, "pranjul");
	std::cout << elemQ1.show();


	std::cout << "\n  Query: 2";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec2 = queryManager.query_two(db, "key3");
	std::cout << "\n  Children of key3-->  ";
	for (size_t i = 0; i < queryVec2.size(); i++)
	{
		std::cout << queryVec2.at(i) << ", ";
	}

	std::cout << "\n\n  Query: 3";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec3 = queryManager.query_three(db, "ke");

	std::cout << "\n  Keys with pattern \"ke\":-->  ";
	for (size_t i = 0; i < queryVec3.size(); i++)
	{
		std::cout << queryVec3.at(i) << ", ";
	}

	queryVec3.clear();
	std::cout << "\n\n  Query: 3 with regex";
	std::cout << "\n ------------------------\n";
	queryVec3 = queryManager.query_three_regex(db, "ke");

	std::cout << "\n  Keys with pattern \"ke\":-->  ";
	for (size_t i = 0; i < queryVec3.size(); i++)
	{
		std::cout << queryVec3.at(i) << ", ";
	}

	std::cout << "\n\n  Query: 4";
	std::cout << "\n ------------------------\n";
	std::cout << "\n  Keys with pattern \"pra\" in their item name:-->  ";
	std::vector<StrData> queryVec4 = queryManager.query_four(db, "pra");
	for (size_t i = 0; i < queryVec4.size(); i++)
	{
		std::cout << queryVec4.at(i) << ", ";
	}

	queryVec4.clear();
	std::cout << "\n\n  Query: 4 with regex";
	std::cout << "\n ------------------------\n";
	std::cout << "\n  Keys with pattern \"pra\" in their item name:-->  ";
	queryVec4 = queryManager.query_four_regex(db, "pra");
	for (size_t i = 0; i < queryVec4.size(); i++)
	{
		std::cout << queryVec4.at(i) << ", ";
	}

	std::cout << "\n\n  Query: 5";
	std::cout << "\n ------------------------\n";
	std::cout << "\n  Keys with pattern \"pranjul\" in their category name:-->  ";
	std::vector<StrData> queryVec5 = queryManager.query_five(db, "pranjul");
	for (size_t i = 0; i < queryVec5.size(); i++)
	{
		std::cout << queryVec5.at(i) << ", ";
	}

	queryVec5.clear();
	std::cout << "\n\n  Query: 5 with regex";
	std::cout << "\n ------------------------\n";
	std::cout << "\n  Keys with pattern \"pranjul\" in their category name:-->  ";
	queryVec5 = queryManager.query_five(db, "pranjul");
	for (size_t i = 0; i < queryVec5.size(); i++)
	{
		std::cout << queryVec5.at(i) << ", ";
	}

	std::cout << "\n\n  Query: 6";
	std::cout << "\n ------------------------\n";
	std::cout << "  Keys with pattern \"Elem1\" in their data section:-->  ";
	std::vector<StrData> queryVec6 = queryManager.query_six(db, "Elem1");
	for (size_t i = 0; i < queryVec6.size(); i++)
	{
		std::cout << queryVec6.at(i) << ", ";
	}

	queryVec6.clear();
	std::cout << "\n\n  Query: 6 with regex";
	std::cout << "\n ------------------------\n";
	std::cout << "  Keys with pattern \"Elem1\" in their data section:-->  ";
	queryVec6 = queryManager.query_six(db, "Elem1");
	for (size_t i = 0; i < queryVec6.size(); i++)
	{
		std::cout << queryVec6.at(i) << ", ";
	}
	std::cout << "\n\n  Query: 7";
	std::cout << "\n ------------------------\n";
	std::cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"2017-02-01 05:19:33\" are/is:-->  ";
	std::vector<StrData> queryVec7 = queryManager.query_seven(db, "2017-02-01 02:19:33", "2017-02-01 05:19:33");

	for (size_t i = 0; i < queryVec7.size(); i++)
	{
		std::cout << queryVec7.at(i) << ", ";
	}

	queryVec7.clear();
	// include a function for current time.....
	std::cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	queryVec7 = queryManager.query_seven(db, "2017-02-01 02:19:33", "");

	for (size_t i = 0; i < queryVec7.size(); i++)
	{
		std::cout << queryVec7.at(i) << ", ";
	}

	queryVec7.clear();
	std::cout << "\n\n  Query: 7 with regex";
	std::cout << "\n ------------------------\n";
	std::cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"2017-02-01 05:19:33\" are/is:-->  ";
	queryVec7 = queryManager.query_seven_regex(db, "2017-02-01 02:19:33", "2017-02-01 05:19:33");

	for (size_t i = 0; i < queryVec7.size(); i++)
	{
		std::cout << queryVec7.at(i) << ", ";
	}

	queryVec7.clear();
	// include a function for current time.....
	std::cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	queryVec7 = queryManager.query_seven_regex(db, "2017-02-01 02:19:33", "");

	for (size_t i = 0; i < queryVec7.size(); i++)
	{
		std::cout << queryVec7.at(i) << ", ";
	}

	// requirement 8
	std::cout << "\n\n  Query: 8";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec8 = queryManager.query_eight(db, "ke", "pra");

	std::cout << "\n  Making query4 on Keys returned from query3 and finding pattern \"pra\" in their item name:-->  ";
	for (size_t i = 0; i < queryVec8.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec8.at(i);
	}

	std::cout << "\n\n  Query: 9";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec9 = queryManager.query_nine(db, "pra", "pranjul");

	std::cout << "\n  Making query5 on Keys returned from query4 and finding pattern \"pranjul\" in their category item:-->  ";
	for (size_t i = 0; i < queryVec9.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec9.at(i);
	}


	std::cout << "\n\n  Query: 10";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec10 = queryManager.query_ten(db, "Test", "Elem2");

	std::cout << "\n  Making query6 on  Keys returned and finding pattern \"pranjul\" in their data item:-->  ";
	for (size_t i = 0; i < queryVec10.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec10.at(i);
	}


	std::cout << "\n\n  Query: 11";
	std::cout << "\n ------------------------\n";
	std::vector<StrData> queryVec11 = queryManager.query_eleven(db, "Elem", "2017-02-01 02:19:33", "2017-02-01 05:19:33");

	std::cout << "\n  Making query7 on  Keys returned and finding keys between time:-->  ";
	for (size_t i = 0; i < queryVec11.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec11.at(i);
	}
	std::cout << "\n\n";
	queryVec11.clear();
	queryVec11 = queryManager.query_eleven(db, "Elem", "2017-02-01 02:19:33", "");
	std::cout << "\n  Making query7 on  Keys returned and finding keys that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	for (size_t i = 0; i < queryVec11.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec11.at(i);
	}

	// requirement 9 -- union of keys

	std::cout << "\n\n  Query: 12";
	std::cout << "\n ------------------------\n";

	std::cout << "Union type1 -->> where keys are over lapping --> A U B = A + B - (A intersection B)\n";
	std::vector<StrData> queryVec12 = queryManager.query_twelve(db, "ke", "pra");

	std::cout << "\n  Union of query3 and query4 results:-->  ";
	for (size_t i = 0; i < queryVec12.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec12.at(i);
	}

	queryVec12.clear();
	std::cout << "\n\nUnion type2 -->> where keys are distinct --> A U B = A + B \n";
	queryVec12 = queryManager.query_twelve(db, "key", "pranjul");
	std::cout << "\n  Union of query3 and query4 results:-->  ";

	for (size_t i = 0; i < queryVec12.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << queryVec12.at(i);
	}

}
#endif 

