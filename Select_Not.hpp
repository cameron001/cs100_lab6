#include "select.hpp"

class Select_Not : public Select {
	private:
		Select *first;
		Select *second;

	public:
		Select_Not(Select* f) {
			this->first = f;
		//	this->second = s;
		}

		~Select_Not() {
			delete first;
		//	delete second;
		}

		virtual bool select(const Spreadsheet* sheet, int row) const {
			return !(first->select(sheet, row));
		//}
	//	virtual bool select(const std::string& s) const {
		//	std::cout << "called function\n";
		//	return !(s.find(value) != std::string::npos);								
		}
};
