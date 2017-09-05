#pragma once
/////////////////////////////////////////////////////////////////////
// TestExecutive.h - Main Program                                  //
//                                                                 //
// Pranjul Arora, CSE687 - Object Oriented Design, Spring 2017     //
/////////////////////////////////////////////////////////////////////
/*
* This package is the starting point which is responsible for the
* displaying all the requirements of noSql Database.
*
*
* Package operations:
* -------------------
* This package contains:
* - TestExecutive template class that have functions -
*		- to make queries from QueryManager
*		- editing database
*		- persisting database
*		- augmenting database
*		- displaying database
*		- toXml
*		- fromXml

*
* Required Files:
* ---------------
*   noSqlDB.h,
*   Convert.h, Convert.cpp,
*   XmlDocument.h, XmlDocument.cpp, XmlElement.h, XmlElement.cpp,
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
* Project #1 Test Executive
*
*
*/

#include"../NoSqlDB/noSqlDB.h"
#include "../NoSqlDB/StrHelper.h"
#include "../QueryManager/queryManager.h"
#include "../Convert/Convert.h"
#include "../XmlDocument/XmlDocument/XmlDocument.h"
#include "../XmlDocument/XmlElement/XmlElement.h"
#include "../XmlDocument/XmlParser/XmlParser.h"
#include <string>
#include <vector>
#include <time.h>
using namespace std;
using StrData = string;
using intData = int;
using Key = noSqlDB<StrData>::Key;
using Keys = noSqlDB<StrData>::Keys;
using namespace XmlProcessing;

using SPtr = std::shared_ptr<AbstractXmlElement>;



template<typename Data>
class TestExecutive
{
public:
	int i = 0; // remove it----------------------------------------------------
	void displayHeading(int);
	void displayQueryResult(std::vector<Data>);
	void makeQueries(noSqlDB<Data>);
	void query1(noSqlDB<Data>, std::string);
	void query2(noSqlDB<Data>, std::string);
	void query3(noSqlDB<Data>, std::string);
	void query4(noSqlDB<Data>, std::string);
	void query5(noSqlDB<Data>, std::string);
	void query6(noSqlDB<Data>, std::string);
	void query7(noSqlDB<Data>);
	void query8(noSqlDB<Data>, std::string, std::string);
	void query9(noSqlDB<Data>, std::string, std::string);
	void query10(noSqlDB<Data>, std::string, std::string);
	void query11(noSqlDB<Data>, std::string);
	// requirement 9 -- union of keys
	void query12(noSqlDB<Data>);

	void addElement(noSqlDB<Data>&);      // add a new element to the current database..
	void displayDatabase(noSqlDB<Data>&); // display the current state of the database..
	void displayIntDatabase(noSqlDB<Data>&);
	void manualEditElements(noSqlDB<Data>&, std::string, std::string);

	void augmentDB(noSqlDB<Data>&, noSqlDB<Data>&);

	void autoPersist(noSqlDB<Data>&);
	Element<Data> newElement_forEdit();

	//toXml
	std::string toXml(noSqlDB<Data>& dbObj);

	//fromXml
	noSqlDB<Data> fromXml(const std::string& xml);
};



template<typename Data>
void TestExecutive<Data>::displayHeading(int number)
{
	cout << "\n  Query: " << number;
	cout << "\n ------------------------\n";
}

template<typename Data>
void TestExecutive<Data>::displayQueryResult(vector<Data> result)
{
	for (size_t i = 0; i < result.size(); i++)
	{
		if (i != 0)
			cout << ", ";
		cout << result.at(i);
	}
	cout << endl;
}

template<typename Data>
void TestExecutive<Data>::makeQueries(noSqlDB<Data> db)
{
	TestExecutive testExecutive;
	testExecutive.query1(db, "TestExecutive");
	testExecutive.query2(db, "TestExecutive");
	testExecutive.query3(db, "cu");
	testExecutive.query4(db, "Manager");
	testExecutive.query5(db, "Program");
	testExecutive.query6(db, "functions");
	testExecutive.query7(db);
	testExecutive.query8(db, "cu", "Manager");
	testExecutive.query9(db, "Manager", "Program");
	testExecutive.query10(db, "Program", "functions");
	testExecutive.query11(db, "functions");
	testExecutive.query12(db);
}

template<typename Data>
void TestExecutive<Data>::query1(noSqlDB<Data> dbQuery, string key)
{
	displayHeading(1);
	cout << " Value of Key \"" + key + "\": \n";
	Query<Data> queryManager;
	Element<Data> elemQ1 = queryManager.query_one(dbQuery, key);
	cout << elemQ1.show();
}

template<typename Data>
void TestExecutive<Data>::query2(noSqlDB<Data> dbQuery, string key)
{
	displayHeading(2);
	cout << " Children of Key \"" + key + "\": \n";
	Query<Data> queryManager;
	cout << "\n  Children of " << key << "-->  ";
	displayQueryResult(queryManager.query_two(dbQuery, key));
}

template<typename Data>
void TestExecutive<Data>::query3(noSqlDB<Data> dbQuery, string keyPattern)
{
	displayHeading(3);
	Query<Data> queryManager;

	cout << "\n  Keys with pattern \"" << keyPattern << "\":-->  ";
	displayQueryResult(queryManager.query_three(dbQuery, keyPattern, dbQuery.keys()));

	cout << "\n\n  Query: 3 with regex";
	cout << "\n ------------------------\n";

	vector<Data> result = queryManager.query_three_regex(dbQuery, keyPattern, dbQuery.keys());
	cout << "\n  Keys with pattern \"" << keyPattern << "\":-->  ";
	displayQueryResult(result);

}

template<typename Data>
void TestExecutive<Data>::query4(noSqlDB<Data> dbQuery, string itemNamePattern)
{
	displayHeading(4);
	Query<Data> queryManager;

	cout << "\n  Keys with pattern \"" << itemNamePattern << "\" in their item name:-->  ";
	displayQueryResult(queryManager.query_four(dbQuery, itemNamePattern, dbQuery.keys()));

	cout << "\n\n  Query: 4 with regex";
	cout << "\n ------------------------\n";
	vector<Data> result = queryManager.query_four_regex(dbQuery, itemNamePattern, dbQuery.keys());
	cout << "\n  Keys with pattern \"" << itemNamePattern << "\" in their item name:-->  ";
	displayQueryResult(result);

}

template<typename Data>
void TestExecutive<Data>::query5(noSqlDB<Data> dbQuery, string itemCtgryPattern)
{
	displayHeading(5);
	Query<Data> queryManager;

	cout << "\n  Keys with pattern \"" << itemCtgryPattern << "\" in their category name:-->  ";
	displayQueryResult(queryManager.query_five(dbQuery, itemCtgryPattern, dbQuery.keys()));


	cout << "\n\n  Query: 5 with regex";
	cout << "\n ------------------------\n";
	vector<Data> result = queryManager.query_five_regex(dbQuery, itemCtgryPattern, dbQuery.keys());
	cout << "\n  Keys with pattern \"" << itemCtgryPattern << "\" in their category name:-->  ";
	displayQueryResult(result);

}

template<typename Data>
void TestExecutive<Data>::query6(noSqlDB<Data> dbQuery, string dataPattern)
{
	displayHeading(6);
	Query<Data> queryManager;

	cout << "  Keys with pattern \"" << dataPattern << "\" in their data section:-->  ";
	displayQueryResult(queryManager.query_six(dbQuery, dataPattern, dbQuery.keys()));

	cout << "\n\n  Query: 6 with regex";
	cout << "\n ------------------------\n";
	vector<Data> result = queryManager.query_six_regex(dbQuery, dataPattern, dbQuery.keys());
	cout << "  Keys with pattern \"" << dataPattern << "\" in their data section:-->  ";
	displayQueryResult(result);

}
template<typename Data>
void TestExecutive<Data>::query7(noSqlDB<Data> dbQuery)
{
	displayHeading(7);
	Query<Data> queryManager;

	cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"2017-02-05 06:19:33\" are/is:-->  ";
	displayQueryResult(queryManager.query_seven(dbQuery, "2017-02-01 02:19:33", "2017-02-05 06:19:33", dbQuery.keys()));
	// include a function for current time.....
	cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	displayQueryResult(queryManager.query_seven(dbQuery, "2017-02-01 02:19:33", "", dbQuery.keys()));

	cout << "\n\n  Query: 7 with regex";
	cout << "\n ------------------------\n";
	vector<Data> result = queryManager.query_seven_regex(dbQuery, "2017-02-01 02:19:33", "2017-02-05 06:19:33", dbQuery.keys());
	cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"2017-02-05 06:19:33\" are/is:-->  ";
	displayQueryResult(result);
	// include a function for current time.....
	result.clear();
	result = queryManager.query_seven_regex(dbQuery, "2017-02-01 02:19:33", "", dbQuery.keys());
	cout << "  Keys/key that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	displayQueryResult(result);
}

// requirement 8
template<typename Data>
void TestExecutive<Data>::query8(noSqlDB<Data> dbQuery, string pattern_q3, string pattern_q4)
{
	cout << "\nDisplaying Requirement 8: -->>> :";
	cout << "\n -----------------------------------------------------------\n";
	displayHeading(8);
	Query<Data> queryManager;
	vector<Data> result = queryManager.query_eight(dbQuery, pattern_q3, pattern_q4, dbQuery.keys());
	cout << "  Making query4 on Keys returned from query3 and finding pattern \"pra\" in their item name:-->  ";
	displayQueryResult(result);

}

template<typename Data>
void TestExecutive<Data>::query9(noSqlDB<Data> dbQuery, string pattern_q4, string pattern_q5)
{
	displayHeading(9);
	Query<Data> queryManager;
	vector<Data> result = queryManager.query_nine(dbQuery, pattern_q4, pattern_q5, dbQuery.keys());

	cout << "\n  Making query5 on Keys returned from query4 and finding pattern \"pranjul\" in their category item:-->  ";
	displayQueryResult(result);
}
template<typename Data>
void TestExecutive<Data>::query10(noSqlDB<Data> dbQuery, string pattern_q5, string pattern_q6)
{
	displayHeading(10);
	Query<Data> queryManager;
	vector<Data> result = queryManager.query_ten(dbQuery, pattern_q5, pattern_q6, dbQuery.keys());
	cout << "\n  Making query6 on  Keys returned and finding pattern \"" << pattern_q6 << "\" in their data item:-->  ";
	displayQueryResult(result);
}


template<typename Data>
void TestExecutive<Data>::query11(noSqlDB<Data> dbQuery, string pattern_q6)
{
	displayHeading(11);
	Query<Data> queryManager;
	vector<Data> result = queryManager.query_eleven(dbQuery, pattern_q6, "2017-02-01 02:19:33", "2017-02-04 05:19:33", dbQuery.keys());
	cout << "\n  Making query7 on  Keys returned and finding keys between time:-->  ";
	displayQueryResult(result);
	result.clear();

	result = queryManager.query_eleven(dbQuery, pattern_q6, "2017-02-01 02:19:33", "", dbQuery.keys());
	cout << "\n  Making query7 on  Keys returned and finding keys that exist between date \"2017-02-01 02:19:33\" and \"Current Time\" are/is :-->  ";
	displayQueryResult(result);

}

// requirement 9 -- union of keys
template<typename Data>
void TestExecutive<Data>::query12(noSqlDB<Data> dbQuery)
{
	cout << "\nDisplaying Requirement 9: -->>> :";
	cout << "\n -----------------------------------------------------------\n";
	displayHeading(12);
	Query<Data> queryManager;
	cout << "Union --> A U B = A + B - (A intersection B)\n";
	vector<Data> result = queryManager.query_twelve(dbQuery, "cu", "Manager", dbQuery.keys());

	cout << "\n  Union of query3 and query4 results:-->  ";
	displayQueryResult(result);

}

//augment DB
template<typename Data>
void TestExecutive<Data>::augmentDB(noSqlDB<Data>& existingDB, noSqlDB<Data>& newDB)
{
	vector<Data> newKeys = newDB.keys();
	for (Data key : newKeys)
	{
		Element<Data> elem = newDB.value(key);
		existingDB.save(key, elem);
	}
}


// addition function to add new element to the database..
template<typename Data>
void TestExecutive<Data>::addElement(noSqlDB<Data>& db)
{
	Element<Data> elem1;
	elem1.name = "Test Element 4";
	elem1.category = "Test4";
	elem1.timeDate = currentDateTime();
	elem1.data = "Elem4 data";
	db.save("key4", elem1);
}

template<typename Data>
void TestExecutive<Data>::manualEditElements(noSqlDB<Data>& db, string key, string metadata)
{
	Element<Data> elem;
	elem.name = "Name " + metadata;
	elem.category = "category " + metadata;
	elem.timeDate = currentDateTime();
	elem.data = "Data " + metadata;
	db.save(key, elem);
}

template<typename Data>
Element<Data> TestExecutive<Data>::newElement_forEdit()
{
	Element<Data> elem1;
	elem1.name = "arora-edited";
	elem1.category = "edited category";
	elem1.timeDate = currentDateTime();
	elem1.data = "edited data";
	elem1.children.push_back("TestExecutive");

	return elem1;
}

template<typename Data>
void TestExecutive<Data>::displayDatabase(noSqlDB<Data>& db)
{
	Keys keysFromXml = db.keys();
	for (Key key : keysFromXml)
	{
		cout << "\n  " << key << ":";
		cout << db.value(key).show();
	}
	cout << "\n -------------------------------------\n";
}

template<typename Data>
void TestExecutive<Data>::displayIntDatabase(noSqlDB<Data>& db)
{
	Keys keysFromXml = db.keys();
	for (Key key : keysFromXml)
	{
		cout << "\n  " << key << ":";
		cout << db.value(key).show();
	}
}

template<typename Data>
void TestExecutive<Data>::autoPersist(noSqlDB<Data>& db)
{
	cout << "\n\n===========Persisting the database ==========================\n\n";

	string xml = toXml(db);

	ofstream out("../Program-structure-new.xml");
	out << xml;
	out.close();
}

template<typename Data>
std::string TestExecutive<Data>::toXml(noSqlDB<Data>& dbObj)
{
	string xml;
	XmlDocument doc;
	SPtr pRoot = makeTaggedElement("NoSqlDB");
	doc.docElement() = pRoot;
	Keys keys = dbObj.keys();
	for (Key key : keys)
	{
		SPtr element = makeTaggedElement("Element");  // key
		pRoot->addChild(element);
		SPtr dbKeyElem = makeTaggedElement("Key");
		element->addChild(dbKeyElem);
		SPtr dbKeyValue = makeTextElement(key); // it is the text element

		dbKeyElem->addChild(dbKeyValue);
		SPtr dbValElem = makeTaggedElement("Value");  // value
		element->addChild(dbValElem);
		SPtr name_Tag = makeTaggedElement("Name");
		dbValElem->addChild(name_Tag);
		SPtr name_Value = makeTextElement(dbObj.value(key).name);
		name_Tag->addChild(name_Value);
		SPtr category_Tag = makeTaggedElement("Category");
		dbValElem->addChild(category_Tag);
		SPtr category_Value = makeTextElement(dbObj.value(key).category);
		category_Tag->addChild(category_Value);
		SPtr date_Tag = makeTaggedElement("TimeDate");
		dbValElem->addChild(date_Tag);
		SPtr date_Value = makeTextElement(dbObj.value(key).timeDate);
		date_Tag->addChild(date_Value);
		SPtr data_Tag = makeTaggedElement("Data");
		dbValElem->addChild(data_Tag);
		SPtr data_Value = makeTextElement(dbObj.value(key).data);
		data_Tag->addChild(data_Value);
		SPtr children_Tag = makeTaggedElement("Children");
		dbValElem->addChild(children_Tag);
		SPtr children_Value;
		string children_Vector_val = "";
		if (!dbObj.value(key).children.empty())
			for (size_t i = 0; i < dbObj.value(key).children.size(); i++)
			{
				SPtr child_Key_Tag = makeTaggedElement("Child_Key");
				children_Tag->addChild(child_Key_Tag);
				SPtr children_key_Value = makeTextElement(dbObj.value(key).children[i]);
				child_Key_Tag->addChild(children_key_Value);
			}
	}
	xml = doc.toString();
	return xml;
}

template<typename Data>
noSqlDB<Data> TestExecutive<Data>::fromXml(const std::string& xml)
{
	noSqlDB<Data> dbXml;
	try
	{
		XmlDocument doc(xml, XmlDocument::str);
		vector<SPtr> totl_Elems = doc.elements("NoSqlDB").select();
		Element<Data> elemXml;
		string key_value; // value of key 
		if (totl_Elems.size() > 0)
		{
			for (size_t i = 0; i < totl_Elems.size(); i++)
			{
				vector<SPtr> elemInfo;
				vector<SPtr> metaDataInfo;
				elemInfo = totl_Elems[i]->children();
				key_value = trim(elemInfo[0]->children()[0]->value());  // key info
				metaDataInfo = elemInfo[1]->children();// metadata Info
				elemXml.name = trim(metaDataInfo[0]->children()[0]->value());
				elemXml.category = trim(metaDataInfo[1]->children()[0]->value());
				elemXml.timeDate = trim(metaDataInfo[2]->children()[0]->value());
				elemXml.data = Convert<Data>::fromString(trim(metaDataInfo[3]->children()[0]->value()));
				vector<SPtr> childInfo = metaDataInfo[4]->children();
				elemXml.children.clear();
				for (size_t i = 0; i < childInfo.size(); i++)
					elemXml.children.push_back(trim(childInfo[i]->children()[0]->value()));
				dbXml.save(key_value, elemXml);
			}
		}
		for (auto pElem : totl_Elems)
		{
			string check = pElem->children()[0]->value();
			vector<SPtr> desc = doc.descendents("NoSqlDB").descendents("Element").descendents("Key").select();
			string key_value = desc[0]->children()[0]->value();
			key_value = trim(key_value);
			desc.clear();
			desc = doc.descendents("NoSqlDB").descendents("Element").descendents("Value").descendents("Name").select();
			string name_value = desc[0]->children()[0]->value();
			name_value = trim(name_value);
			elemXml.name = name_value;
			dbXml.save(key_value, elemXml);
		}
	}
	catch (std::exception& ex)
	{
		std::cout << "\n something bad happened";
		std::cout << "\n " << ex.what();
	}
	return dbXml;
}
