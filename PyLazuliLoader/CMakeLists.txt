cmake_minimum_required(VERSION 3.10)

project(PyLazuliLoader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)
# Find Python and PyBind1
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

message(STATUS "Python Interpreter: ${Python_EXECUTABLE}")
message(STATUS "Python Include Directories: ${Python_INCLUDE_DIRS}")
message(STATUS "Python Libraries: ${Python_LIBRARIES}")
message(STATUS "Python Version: ${Python_VERSION}")

set(SRCS
    PyLazuliLoader.h PyLazuliLoader.cpp
)

# fetch BaseNaviWidgetLib include dir to pass qt moc interface
get_target_property(BaseNaviWidget_INCLUDE_DIRS BaseNaviWidgetLib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${BaseNaviWidget_INCLUDE_DIRS})

qt_wrap_cpp(MOC_SOURCES PyLazuliLoader.h)


add_library(${PROJECT_NAME} SHARED ${SRCS} ${MOC_SOURCES})

add_definitions(-DPYTHON_LIBRARIES="${Python_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} PUBLIC pybind11::embed ${Python_LIBRARIES} Qt6::Widgets BaseNaviWidgetLib )
target_include_directories(${PROJECT_NAME} PUBLIC ${pybind11_INCLUDE_DIRS} ${Python_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)