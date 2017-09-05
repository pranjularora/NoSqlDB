#pragma once
/////////////////////////////////////////////////////////////////////
// NoSqlDb.h - key/value pair in-memory database                   //
//                                                                 //
// Pranjul Arora, CSE687 - Object Oriented Design, Spring 2017     //
/////////////////////////////////////////////////////////////////////
/*
* This package is for building a key/value pair noSql Database.
*
*
* Package operations:
* -------------------
* This package contains:
* - noSqlDB template class that have functions -
*		- keys --> gives all the exsiting keys in the element
*		- save  --> save the current state of the Database
*		- value --> gives the value of the given key
*		- count --> gives size of DB
*		- editElem --> edit element (metadata or data) of a particular key
*		- deleteElem --> delete element of a particulat key
*		- editInstance --> edit the complete instance corresponding to a key
*
* - Element template class that define properties which helps making database
*
* Required Files:
* ---------------
*   CppProperties.h, CppProperties.cpp
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
* Project #1 noSql Database
*
*
*/



#include "../CppProperties/CppProperties.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <unordered_map>

template<typename Data>
class Element
{
public:
	using Name = std::string;
	using Category = std::string;
	using TimeDate = std::string;
	using Children = std::vector<std::string>;

	Property<Name> name;
	Property<Category> category;
	Property<TimeDate> timeDate;
	Children children;

	Property<Data> data;
	std::string show();



};

// returns the Element<Data> template class by coverting it to string for display
template<typename Data>
std::string Element<Data>::show()
{
	// show children when you've implemented them
	std::ostringstream out;
	int i = 0;
	out.setf(std::ios::adjustfield, std::ios::left);
	out << "\n    " << std::setw(8) << "name" << " : " << name;
	out << "\n    " << std::setw(8) << "category" << " : " << category;
	out << "\n    " << std::setw(8) << "timeDate" << " : " << timeDate;
	out << "\n    " << std::setw(8) << "data" << " : " << data;
	out << "\n    " << std::setw(8) << "children" << " : ";
	for (std::vector<std::string>::iterator it = children.begin(); it != children.end(); ++it)
	{
		if (i != 0)
			out << ", ";
		out << *it;
		i++;
	}
	out << "\n";
	return out.str();
}

// Class of template type to Create NoSql Database
template<typename Data>
class noSqlDB
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;

	Keys keys();
	bool save(Key key, Element<Data> elem);
	Element<Data> value(Key key);
	size_t count();

	void deleteElem(Key key);
	void editElem(Key key, Key editingValue, Key newChild);
	void editInstance(Key key, Element<Data> newElement);

private:
	using Item = std::pair<Key, Element<Data>>;

	std::unordered_map<Key, Element<Data>> store;
};


// code for editing Value part of the database i.e. editing Element class values
template<typename Data>
void noSqlDB<Data>::editElem(Key key, Key newCategory, Key newChild)
{
	if (store.find(key) != store.end())
	{
		// store[key] return value of the key, which is Element<Data> in our case
		Element<Data> editElement = store[key];
		editElement.category = newCategory;
		editElement.data = "edited Data";
		for (std::vector<std::string>::iterator it = editElement.children.begin(); it != editElement.children.end(); ++it)
		{
			if (*it == "arora")
				*it = newChild;
		}
		store[key] = editElement;
	}
	else
	{
		std::cout << "Key Not Found";
	}
}

// edit the whole instance of the class i.e. new element<Data> will be assigned to the existing key
template<typename Data>
void noSqlDB<Data>::editInstance(Key key, Element<Data> newElement)
{
	if (store.find(key) != store.end())
	{
		store[key] = newElement;
	}
}

// Delete an element corresponding to a particular key
template<typename Data>
void noSqlDB<Data>::deleteElem(Key key)
{
	if (store.find(key) != store.end())
	{
		store.erase(key);

		Keys newKeys = keys();

		for (Key newKey : newKeys)
		{
			Element<Data> editElement = store[newKey];
			for (std::vector<std::string>::iterator it = editElement.children.begin(); it != editElement.children.end(); ++it)
			{
				if (*it == key)
					it = editElement.children.erase(it);
			}
			store[newKey] = editElement;
		}
	}
}

// return all keys from the existing database
template<typename Data>
typename noSqlDB<Data>::Keys noSqlDB<Data>::keys()
{
	Keys keys;
	for (Item item : store)
	{
		keys.push_back(item.first);
	}
	return keys;
}

// Save to the Database
template<typename Data>
bool noSqlDB<Data>::save(Key key, Element<Data> elem)
{
	if (store.find(key) != store.end())
		return false;
	store[key] = elem;
	return true;
}

// Return value i.e. Element class corresponding to the key
template<typename Data>
Element<Data> noSqlDB<Data>::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element<Data>();
}

// Counts the size of the database
template<typename Data>
size_t noSqlDB<Data>::count()
{
	return store.size();
}