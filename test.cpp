#include "spreadsheet.hpp"
#include "Select_Contains.hpp"
#include "Select_And.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <sstream>

using ::testing::HasSubstr;

TEST(Select_Contains_class, passing_param) {
	Spreadsheet s;
	s.set_column_names({"First", "Last", "Age", "Major"});
	s.add_row({"Blake", "Dickerson", "22", "computer science"});
	Select_Contains sc(&s, "Last", "Dickerson");
	bool pass = sc.select("Dickerson");
	ASSERT_TRUE(pass);
}

TEST(Select_Contains_class, check_correct_output) {
	Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
	s.set_selection(new Select_Contains(&s, "First", "John"));
	s.print_selection(ss);
	EXPECT_EQ("John Apple 22 computer science \n", ss.str());	
}

TEST(Select_Contains_class, check_empty_quotes) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_Contains(&s, "Last", ""));
        s.print_selection(ss);
        EXPECT_EQ("Blake Dickerson 22 computer science \nJohn Apple 22 computer science \nbig man 22 computer science \n", ss.str());
}

TEST(Select_Contains_class, check_substr) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_Contains(&s, "Last", "erson"));
        s.print_selection(ss);
        EXPECT_EQ("Blake Dickerson 22 computer science \n", ss.str());
}

TEST(Select_Contains_class, check_failing_substr) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_Contains(&s, "First", "Johnnnnn"));
        s.print_selection(ss);
        EXPECT_EQ("", ss.str());
}

TEST(Select_Contains_class, check_double_column) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_Contains(&s, "First", "First"));
        s.print_selection(ss);
        EXPECT_EQ("", ss.str());
}

TEST(Select_And_class, check_correct_output) {
	Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
	s.add_row({"big", "man", "22", "computer science"});
	std::stringstream ss;
  	s.set_selection(new Select_And(
                        new Select_Contains(&s, "First", "big"),
			new Select_Contains(&s, "Last", "man")));
	s.print_selection(ss);
	EXPECT_EQ("big man 22 computer science \n", ss.str());
}

TEST(Select_And_class, check_double_query) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_And(
                        new Select_Contains(&s, "First", "big"),
                        new Select_Contains(&s, "First", "big")));
        s.print_selection(ss);
        EXPECT_EQ("big man 22 computer science \n", ss.str());
}

TEST(Select_And_class, check_double_columns) {
        Spreadsheet s;
        s.set_column_names({"First", "First", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_And(
                        new Select_Contains(&s, "First", "big"),
                        new Select_Contains(&s, "First", "big")));
        s.print_selection(ss);
        EXPECT_EQ("big man 22 computer science \n", ss.str());
}

TEST(Select_And_class, check_double_quotes) {
        Spreadsheet s;
        s.set_column_names({"First", "Last", "Age", "Major"});
        s.add_row({"Blake", "Dickerson", "22", "computer science"});
        s.add_row({"John", "Apple", "22", "computer science"});
        s.add_row({"big", "man", "22", "computer science"});
        std::stringstream ss;
        s.set_selection(new Select_And(
                        new Select_Contains(&s, "First", ""),
                        new Select_Contains(&s, "Last", "")));
        s.print_selection(ss);
        EXPECT_EQ("Blake Dickerson 22 computer science \nJohn Apple 22 computer science \nbig man 22 computer science \n", ss.str());
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
