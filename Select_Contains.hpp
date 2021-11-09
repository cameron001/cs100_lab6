#pragma once

#include "select.hpp"

class Select_Contains : public Select_Column {
	private:
	std::string value;	//string data type that accepts the name in the constructor

	public:
		/*
 		* overloaded constructor that takes in the inherited constructor of Select_Column
 		*/
		Select_Contains(const Spreadsheet* sheet, const std::string& col, const std::string& value) : Select_Column(sheet, col) {
			this->value = value;
		}
	
		/*
 		* abstract function that will return true if the given value string matches or is a substring of the paramterized string
 		* @param- std::string& s
 		* @return- true if string is found, false if not
 		*/ 
		virtual bool select(const std::string& s) const {
			//std::cout << "called function\n";
			return (s.find(value) != std::string::npos);
		}
};
