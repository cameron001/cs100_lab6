#pragma once

#include "select.hpp"

class Select_And : public Select {
	private:
		Select *first;
		Select *second;

	public:
		Select_And(Select* f, Select* s) {
			this->first = f;
			this->second = s;
		}

		~Select_And() {
			delete first;
			delete second;
		}

		virtual bool select(const Spreadsheet* sheet, int row) const {
			return (first->select(sheet, row) && second->select(sheet, row));
		}
};
