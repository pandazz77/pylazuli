cmake_minimum_required(VERSION 3.10)

project(PyLazuliLoader LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)
# Find Python and PyBind1
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

set(SRCS
    NaviPluginInterface.h NaviPluginInterface.cpp
    PyLazuliLoader.h PyLazuliLoader.cpp
)

qt_wrap_cpp(MOC_SOURCES NaviPluginInterface.h PyLazuliLoader.h)


add_library(${PROJECT_NAME} SHARED ${SRCS} ${MOC_SOURCES})

# Определяем макрос QEXPORT только при компиляции библиотеки
target_compile_definitions(${PROJECT_NAME} PRIVATE Q_EXPORT)
target_link_libraries(${PROJECT_NAME} PUBLIC pybind11::embed ${PYTHON_LIBRARIES} Qt6::Widgets BaseNaviWidgetLib )

target_include_directories(${PROJECT_NAME} PUBLIC ${Python_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)