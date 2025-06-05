cmake_minimum_required(VERSION 3.10)

project(PythonEmbeddingExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)
# Find Python and PyBind1
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Add the executable
add_executable(python_embed_example embed.cpp)
add_executable(plugin_loader plugin_loader.cpp)

# Link against Python libraries
target_link_libraries(python_embed_example PRIVATE pybind11::embed ${PYTHON_LIBRARIES} Qt6::Widgets BaseNaviWidgetLib)
target_link_libraries(plugin_loader        PRIVATE pybind11::embed ${PYTHON_LIBRARIES} Qt6::Widgets BaseNaviWidgetLib)

# Set include directories
target_include_directories(python_embed_example PRIVATE ${Python_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS})
target_include_directories(plugin_loader        PRIVATE ${Python_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS})

add_custom_target(copy_python_file ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/test.py ${CMAKE_CURRENT_BINARY_DIR}
)