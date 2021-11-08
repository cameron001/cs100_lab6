#include "spreadsheet.hpp"
#include "select.hpp"

#include <algorithm>
#include <iostream>

Spreadsheet::~Spreadsheet()
{
    delete select;
}

void Spreadsheet::set_selection(Select* new_select)
{
    delete select;
    select = new_select;
}

void Spreadsheet::clear()
{
    column_names.clear();
    data.clear();
    delete select;
    select = nullptr;
}

void Spreadsheet::set_column_names(const std::vector<std::string>& names)
{
    column_names=names;
}

void Spreadsheet::add_row(const std::vector<std::string>& row_data)
{
    data.push_back(row_data);
}

int Spreadsheet::get_column_by_name(const std::string& name) const
{
    for(int i=0; i<column_names.size(); i++)
        if(column_names.at(i) == name)
            return i;
    return -1;
}

//TODO implement print_selection
void Spreadsheet::print_selection(std::ostream& out) const {
	if (select) {
		//std::cout << "in select\n";
       		for (int i= 0; i < data.size(); i++) {
            		//std::cout << "in loop\n";
			if(select->select(this, i)) {
                		//std::cout << "in if\n";
				for (int j = 0; j < data.at(i).size(); j++) {
                   			//std::cout << "in for\n";
			 		out << cell_data(i,j) << " ";
                		}
               			out << "\n";
            		}
       		}
    	}
        else {
                for (int i = 0; i < data.size(); i++) {
                	for (int j = 0; j < data.at(i).size(); j++) {
                		out << cell_data(i,j) << " ";
            		}
            		out << "\n";
        	}
	}
}

