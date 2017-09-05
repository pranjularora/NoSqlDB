#pragma once
/////////////////////////////////////////////////////////////////////
// queryManager.h - Query Engine, helps making query with databas  //
//                                                                 //
// Pranjul Arora, CSE687 - Object Oriented Design, Spring 2017     //
/////////////////////////////////////////////////////////////////////
/*
* This package is used the make different types of query to the database
*
*
* Package operations:
* -------------------
* This package contains:
* - Query template class that have functions to do all the queries as per the requirements
*		
*
* Required Files:
* ---------------
*   noSqlDB.h
*  
*
* Build Instructions:
* -------------------
* - The above required files should be build as static library
*   after undefining their test stub
*
*
*  Maintanence History:
* --------------------
* ver 1.0 : 5 February 2017
* Project #1 queryManager
*
*
*/


#include "../NoSqlDB/noSqlDB.h"
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <regex>

// returns current date-time in "yyyy-mm-dd hh:mm:ss"
const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

using Keys = std::vector<std::string>;

//query class of template type which helps quering the database
template<typename querytype>
class Query
{
public:

	Element<querytype> query_one(noSqlDB<querytype> db_query_obj, querytype key);  // query1
	std::vector<querytype> query_two(noSqlDB<querytype> db_query_obj, querytype key);  // query2
	std::vector<querytype> query_three(noSqlDB<querytype> db_query_obj, querytype pattern, Keys);   // query3
    // query 3 regex
	std::vector<querytype> query_three_regex(noSqlDB<querytype> db_query_obj, querytype pattern, Keys);

	std::vector<querytype> query_four(noSqlDB<querytype> db_query_obj, querytype name_pattern, Keys);   // query4
    // query 4 regex
	std::vector<querytype> query_four_regex(noSqlDB<querytype> db_query_obj, querytype name_pattern, Keys);

	std::vector<querytype> query_five(noSqlDB<querytype> db_query_obj, querytype category_pattern, Keys);  // query5
	// query 5 regex
	std::vector<querytype> query_five_regex(noSqlDB<querytype> db_query_obj, querytype category_pattern, Keys);

	std::vector<querytype> query_six(noSqlDB<querytype> db_query_obj, querytype data_pattern, Keys); // query6
	// query 6 regex
	std::vector<querytype> query_six_regex(noSqlDB<querytype> db_query_obj, querytype data_pattern, Keys);

	std::vector<querytype> query_seven(noSqlDB<querytype> db_query_obj, querytype time1, querytype time2, Keys); // query7
	// query 7 regex
	std::vector<querytype> query_seven_regex(noSqlDB<querytype> db_query_obj, querytype time1, querytype time2, Keys); 

	// making query4 on the keys returned by the query3...
	std::vector<querytype> query_eight(noSqlDB<querytype> db_query_obj, querytype pattern_q3, querytype pattern_q4, Keys);   // query8

	// making query5 on the keys returned by the query4...
	std::vector<querytype> query_nine(noSqlDB<querytype> db_query_obj, querytype pattern_q4, querytype pattern_q5, Keys);   // query9

	// making query6 on the keys returned by the query5...
	std::vector<querytype> query_ten(noSqlDB<querytype> db_query_obj, querytype pattern_q5, querytype pattern_q6, Keys);   // query10

	// making query7 on the keys returned by the query6...
	std::vector<querytype> query_eleven(noSqlDB<querytype> db_query_obj, querytype pattern_q6, querytype time1, querytype time2, Keys); // query 11

	// union query
	std::vector<querytype> query_twelve(noSqlDB<querytype> db_query_obj, querytype pattern_q3, querytype pattern_q4, Keys); // query 12 -- union of keys..
};

// query1 --> The value of a specified key.
template<typename querytype>
Element<querytype> Query<querytype>::query_one(noSqlDB<querytype> db_query_obj, querytype key)
{
	return(db_query_obj.value(key));

}

// query2--> the children of a specified key.
template<typename querytype>
std::vector<querytype> Query<querytype>::query_two(noSqlDB<querytype> db_query_obj, querytype key)
{
	std::vector<querytype> vec_two;
	Element<querytype> elem = db_query_obj.value(key);
	for (size_t i = 0; i < elem.children.size(); i++)
	{
		vec_two.push_back(elem.children.at(i));
	}
	return vec_two;
}

// query3 -->  The set of all keys matching a specified pattern which defaults to all keys.
template<typename querytype>
std::vector<querytype> Query<querytype>::query_three(noSqlDB<querytype> db_query_obj, querytype pattern, Keys keys)
{
	std::vector<querytype> vec_three;
	std::vector<querytype> result_vec;
	vec_three = keys;


	for (size_t i = 0; i < vec_three.size(); i++)
	{
		if (vec_three.at(i).find(pattern) != std::string::npos)
		{
			result_vec.push_back(vec_three.at(i));
		}
	}

	return result_vec;
}

// this will call query3 with pattern_q3 and will check for pattern_q4 on query4. 
template<typename querytype>
std::vector<querytype> Query<querytype>::query_eight(noSqlDB<querytype> db_query_obj, querytype pattern_q3, querytype pattern_q4, Keys keys)
{
	std::vector<querytype> result_vec;
	std::vector<querytype> vec_from_query3;
	vec_from_query3 = query_three(db_query_obj, pattern_q3, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query3, i.e. finding pattern \"" << pattern_q3 << "\": ";
	for (size_t i = 0; i < vec_from_query3.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query3.at(i);
	}
	std::cout << "\n";

	for (size_t i = 0; i < vec_from_query3.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_from_query3.at(i));
		std::ostringstream out;
		out << elem.name;
		std::string name = out.str();
		if (name.find(pattern_q4) != std::string::npos)
		{
			result_vec.push_back(vec_from_query3.at(i));
		}
	}
	return result_vec;

}
// Same as query3 with regex 
template<typename querytype>
std::vector<querytype> Query<querytype>::query_three_regex(noSqlDB<querytype> db_query_obj, querytype pattern, Keys keys)
{
	std::vector<querytype> vec_three;
	std::vector<querytype> result_vec;
	vec_three = keys;

	std::ostringstream out;
	out << pattern;
	std::string pattern_str = out.str();
	std::string regex_string = "(.*)" + pattern_str + "(.*)";
	std::regex exp(regex_string);
	std::cout << "\n  Regex used: " << "(.*)" + pattern_str + "(.*)\n";

	for (size_t i = 0; i < vec_three.size(); i++)
	{
		std::string main_string = vec_three.at(i);
		
		if (std::regex_match(main_string.c_str(), exp))
		{
			result_vec.push_back(vec_three.at(i));
		}
	}
	return result_vec;
}

// query4 All keys that contain a specified string in their item name
template<typename querytype>
std::vector<querytype> Query<querytype>::query_four(noSqlDB<querytype> db_query_obj, querytype name_pattern, Keys keys)
{
	std::vector<querytype> vec_four;
	std::vector<querytype> result_vec_four;

	vec_four = keys;

	for (size_t i = 0; i < vec_four.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_four.at(i));
		std::ostringstream out;
		out << elem.name;
		std::string name = out.str();
		if (name.find(name_pattern) != std::string::npos)
		{
			result_vec_four.push_back(vec_four.at(i));
		}
	}
	return result_vec_four;
}


template<typename querytype>
std::vector<querytype> Query<querytype>::query_nine(noSqlDB<querytype> db_query_obj, querytype pattern_q4, querytype pattern_q5, Keys keys)
{
	std::vector<querytype> result_vec;
	std::vector<querytype> vec_from_query4;
	vec_from_query4 = query_four(db_query_obj, pattern_q4, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query4, i.e. finding pattern \"" << pattern_q4 << "\": ";
	for (size_t i = 0; i < vec_from_query4.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query4.at(i);
	}

	for (size_t i = 0; i < vec_from_query4.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_from_query4.at(i));
		std::ostringstream out;
		out << elem.category;
		std::string name = out.str();
		if (name.find(pattern_q5) != std::string::npos)
		{
			result_vec.push_back(vec_from_query4.at(i));
		}
	}
	return result_vec;

}

template<typename querytype>
std::vector<querytype> Query<querytype>::query_four_regex(noSqlDB<querytype> db_query_obj, querytype name_pattern, Keys keys)
{
	std::vector<querytype> vec_four;
	std::vector<querytype> result_vec_four;
	
	std::ostringstream out;
	out << name_pattern;
	std::string pattern_str = out.str();

	vec_four = keys;
	std::string regex_string = "(.*)" + pattern_str + "(.*)";
	std::regex exp(regex_string);
	std::cout << "\n  Regex used: " << "(.*)" + pattern_str + "(.*)\n";
	for (size_t i = 0; i < vec_four.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_four.at(i));
		std::ostringstream out;
		out << elem.name;
		std::string main_string = out.str();
		

		if (std::regex_match(main_string.c_str(), exp))
		{
			result_vec_four.push_back(vec_four.at(i));
		}

	
	}
	return result_vec_four;
}


// query 5 --> All keys that contain a specified string in their category name
template<typename querytype>
std::vector<querytype> Query<querytype>::query_five(noSqlDB<querytype> db_query_obj, querytype category_pattern, Keys keys)
{
	std::vector<querytype> vec_five;
	std::vector<querytype> result_vec_five;

	vec_five = keys;

	for (size_t i = 0; i < vec_five.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_five.at(i));
		std::ostringstream out;
		out << elem.category;
		std::string name = out.str();
		if (name.find(category_pattern) != std::string::npos)
		{
			result_vec_five.push_back(vec_five.at(i));
		}
	}
	return result_vec_five;
}

// For Requirement 8 --> results returned by making query5 will be used for query6
template<typename querytype>
std::vector<querytype> Query<querytype>::query_ten(noSqlDB<querytype> db_query_obj, querytype pattern_q5, querytype pattern_q6, Keys keys)
{
	std::vector<querytype> result_vec;
	std::vector<querytype> vec_from_query5;

	vec_from_query5 = query_five(db_query_obj, pattern_q5, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query5, i.e. finding pattern \"" << pattern_q5 << "\": ";
	for (size_t i = 0; i < vec_from_query5.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query5.at(i);
	}

	for (size_t i = 0; i < vec_from_query5.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_from_query5.at(i));
		std::ostringstream out;
		out << elem.data;
		std::string name = out.str();
		if (name.find(pattern_q6) != std::string::npos)
		{
			result_vec.push_back(vec_from_query5.at(i));
		}
	}
	return result_vec;

}

template<typename querytype>
std::vector<querytype> Query<querytype>::query_five_regex(noSqlDB<querytype> db_query_obj, querytype category_pattern, Keys keys)
{
	std::vector<querytype> vec_five;
	std::vector<querytype> result_vec_five;

	std::ostringstream out;
	out << category_pattern;
	std::string pattern_str = out.str();

	vec_five = keys;

	std::string regex_string = "(.*)" + pattern_str + "(.*)";
	std::regex exp(regex_string);
	std::cout << "\n  Regex used: " << "(.*)" + pattern_str + "(.*)\n";

	for (size_t i = 0; i < vec_five.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_five.at(i));
		std::ostringstream out;
		out << elem.category;
		std::string main_string = out.str();
		
		if (std::regex_match(main_string.c_str(), exp))
		{
			result_vec_five.push_back(vec_five.at(i));
		}
	}
	return result_vec_five;
}


// query6 --> All keys that contain a specified string in their template data section when that makes sense.
template<typename querytype>
std::vector<querytype> Query<querytype>::query_six(noSqlDB<querytype> db_query_obj, querytype data_pattern, Keys keys)
{
	std::vector<querytype> vec_six;
	std::vector<querytype> result_vec_six;

	vec_six = keys;

	for (size_t i = 0; i < vec_six.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_six.at(i));
		std::ostringstream out;
		out << elem.data;
		std::string name = out.str();
		if (name.find(data_pattern) != std::string::npos)
		{
			result_vec_six.push_back(vec_six.at(i));
		}
	}
	return result_vec_six;
}
// For Requirement 8 --> results returned by making query6 will be used for query7
template<typename querytype>
std::vector<querytype> Query<querytype>::query_eleven(noSqlDB<querytype> db_query_obj, querytype pattern_q6, querytype time1, querytype time2, Keys keys)
{
	std::vector<querytype> result_vec;
	std::vector<querytype> vec_from_query6;

	vec_from_query6 = query_six(db_query_obj, pattern_q6, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query6, i.e. finding pattern \"" << pattern_q6 << "\": ";
	for (size_t i = 0; i < vec_from_query6.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query6.at(i);
	}

	for (size_t i = 0; i < vec_from_query6.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_from_query6.at(i));
		std::ostringstream out;
		out << elem.timeDate;
		std::string check_date = out.str();

		if (time2 == "")
		{
			time2 = currentDateTime();
		}
		if (check_date > time1 && check_date < time2)
			result_vec.push_back(vec_from_query6.at(i));
	}
	return result_vec;
}

template<typename querytype>
std::vector<querytype> Query<querytype>::query_six_regex(noSqlDB<querytype> db_query_obj, querytype data_pattern, Keys keys)
{
	std::vector<querytype> vec_six;
	std::vector<querytype> result_vec_six;

	std::ostringstream out;
	out << data_pattern;
	std::string pattern_str = out.str();

	std::string regex_string = "(.*)" + pattern_str + "(.*)";
	std::regex exp(regex_string);
	std::cout << "\n  Regex used: " << "(.*)" + pattern_str + "(.*)\n";

	vec_six = keys;

	for (size_t i = 0; i < vec_six.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_six.at(i));
		std::ostringstream out;
		out << elem.data;
		std::string main_string = out.str();
		

		if (std::regex_match(main_string.c_str(), exp))
		{
			result_vec_six.push_back(vec_six.at(i));
		}
	}
	return result_vec_six;
}

// query7--> All keys that contain values written within a specified time-date interval
template<typename querytype>
std::vector<querytype> Query<querytype>::query_seven(noSqlDB<querytype> db_query_obj, querytype time1, querytype time2, Keys keys)
{
	std::vector<querytype> vec_seven;
	std::vector<querytype> result_vec_seven;
	vec_seven = keys;

	for (size_t i = 0; i < vec_seven.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_seven.at(i));
		std::ostringstream out;
		out << elem.timeDate;
		std::string check_date = out.str();

		if (time2 == "")
			time2 = currentDateTime();
		if (check_date > time1 && check_date < time2)
			result_vec_seven.push_back(vec_seven.at(i));
	}
	return result_vec_seven;
}

template<typename querytype>
std::vector<querytype> Query<querytype>::query_seven_regex(noSqlDB<querytype> db_query_obj, querytype time1, querytype time2, Keys keys)
{
	std::vector<querytype> vec_seven;
	std::vector<querytype> result_vec_seven;
	vec_seven = keys;
	std::string regex_string = "^\\s*$";
	std::cout << "\n  Regex used to check whether a time constrain is empty: " << regex_string;
	std::regex exp(regex_string);
	std::cout << "\n";
	for (size_t i = 0; i < vec_seven.size(); i++)
	{
		Element<querytype> elem = db_query_obj.value(vec_seven.at(i));
		std::ostringstream out;
		out << elem.timeDate;
		std::string check_date = out.str();

		std::ostringstream out1;
		out1 << time2;
		std::string main_string = out1.str();
		

		if (std::regex_match(main_string.c_str(), exp))
		{
			time2 = currentDateTime();
		}
		if (check_date > time1 && check_date < time2)
			result_vec_seven.push_back(vec_seven.at(i));

	}

	return result_vec_seven;
}

// Union Query--> union of query3 results with query4--> A U B = A + B - A intersection B
template<typename querytype>
std::vector<querytype> Query<querytype>::query_twelve(noSqlDB<querytype> db_query_obj, querytype pattern_q3, querytype pattern_q4, Keys keys)
{
	std::unordered_map<querytype, querytype> unionKeys;
	int k = 0;

	std::vector<querytype> result_vec;
	std::vector<querytype> vec_from_query3;
	vec_from_query3 = query_three(db_query_obj, pattern_q3, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query3, i.e. finding pattern \"" << pattern_q3 << "\": ";
	for (size_t i = 0; i < vec_from_query3.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query3.at(i);
	}

	std::vector<querytype> vec_from_query4;
	vec_from_query4 = query_four(db_query_obj, pattern_q4, db_query_obj.keys());
	std::cout << "\n  Keys returned by making query4, i.e. finding pattern \"" << pattern_q4 << "\": ";
	for (size_t i = 0; i < vec_from_query4.size(); i++)
	{
		if (i != 0)
			std::cout << ", ";
		std::cout << vec_from_query4.at(i);
	}


	for (size_t i = 0; i < vec_from_query3.size(); i++)
	{
		unionKeys[vec_from_query3.at(i)] = k;
		k++;
	}

	for (size_t i = 0; i < vec_from_query4.size(); i++)
	{
		if (unionKeys.find(vec_from_query4.at(i)) == unionKeys.end())
		{
			unionKeys[vec_from_query4.at(i)] = k;
			k++;
		}
	}

	for (std::pair<querytype,querytype> map: unionKeys)
	{
		result_vec.push_back(map.first);
	}

	return result_vec;
}

