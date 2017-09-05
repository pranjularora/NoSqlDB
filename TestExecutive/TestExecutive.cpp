/////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - Main Program                                //
//                                                                 //
// Pranjul Arora, CSE687 - Object Oriented Design, Spring 2017     //
/////////////////////////////////////////////////////////////////////

#include"TestExecutive.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>


using namespace std;

// main function
int main()
{
	try
	{
		int count = 0;
		TestExecutive<StrData> testExecutive;
		TestExecutive<intData> testExecutive_int;
		noSqlDB<StrData> existingDB; // existing database
		XmlParser parser_int("../Integer-DB.xml");    // --->>> retrieving from Int Database
		XmlDocument* pDoc_int = parser_int.buildDocument();
		testExecutive.manualEditElements(existingDB, "M1", "manual 1");
		XmlParser parser1("../Program-structure.xml"); // --->>> retrieving from string database
		XmlDocument* pDoc1 = parser1.buildDocument();
		cout << "\nDisplaying Requirement 5 and 2: -->>> Program Structure Database Retrieved from XMLs:\n\n -----------------------------------------------------------\nInteger type database retrieved from XML\n -----------------------\n";
		noSqlDB<intData> db_int = testExecutive_int.fromXml(pDoc_int->toString());
		testExecutive_int.displayIntDatabase(db_int);  // display int database
		cout << "\n  String type database retrieved from XML\n -----------------------";
		noSqlDB<StrData> db = testExecutive.fromXml(pDoc1->toString());
		testExecutive.displayDatabase(db); // display string database
		cout << "\n ====================================Now Augmenting DB=================================\nExisting Database--\n";
		testExecutive.displayDatabase(existingDB);
		cout << "Augmenting existing database with the retrieved one(String DB) and this will be the current database now--\n";
		testExecutive.augmentDB(existingDB, db); count++; // counting counts for number of writes
		testExecutive.displayDatabase(existingDB);
		cout << "\n -------------------------------------\nDisplaying Requirement 7: -->>>\n";
		testExecutive.makeQueries(existingDB); // this function will execute all the queries on this database object..
		cout << "\n -------------------------------------\nDisplaying Requirement 3: -->>> Adding element with key: \"key4\" and deleting element with key: \"M1 \" and all its dependency\n";
	
		testExecutive.addElement(existingDB); // addition, deletion and editing will be performed here
		existingDB.deleteElem("M1"); count = count + 2;
		cout << "\n\n===========Requirement 6: Persisting the database as number of writes is 3 ==========================\n\n";
		testExecutive.autoPersist(existingDB);
		testExecutive.displayDatabase(existingDB);
		cout << "\n\nDisplaying Requirement 4: -->>>\nchanging category of key: \"key4\" to \"edited category\", data to \"edited data\" and children to \"key4\" ";
		existingDB.editElem("key4", "edited Key4 Category", "TestExecutive");
		cout << "\nReplacing existing instance of key: \"key4\" with edited version\n \n -------------------------------------\n";
		Element<StrData> newInstance = testExecutive.newElement_forEdit();
		existingDB.editInstance("key4", newInstance);
		testExecutive.displayDatabase(existingDB);
		cout << "\n -------------------------------------\n\nDisplaying Requirement 5: -->>> Persisting database to XML, check file with name \"Program-structure-new.xml\" ";
		testExecutive.autoPersist(existingDB);
	}
	catch (std::exception& e)
	{
		cout << "ERROR: " << e.what();
	}
	catch (...)
	{
		cout << "Unknows error ";
	}
	std::cin.get();
}