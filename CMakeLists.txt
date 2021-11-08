CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(spreadsheet
	 main.cpp 
	 spreadsheet.cpp 
	 spreadsheet.hpp 
	 Select_Contains.hpp 
	 select.hpp
	 Select_And.hpp
)

ADD_EXECUTABLE(test 
	 test.cpp
	 spreadsheet.cpp)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_LINK_LIBRARIES(test gmock)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
