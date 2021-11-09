#include "select.hpp"

class Select_Or : public Select {
	private:
		Select *first;
		Select *second;

	public:
		Select_Or(Select* f, Select* s) {
			this->first = f;
			this->second = s;
		}

		~Select_Or() {
			delete first;
			delete second;
		}

		virtual bool select(const Spreadsheet* sheet, int row) const {
			return (first->select(sheet, row) || second->select(sheet, row));
		}
};
