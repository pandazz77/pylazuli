cmake_minimum_required(VERSION 3.10)

project(PythonEmbeddingExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED)
# Find Python and PyBind1
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

# Add the executable
add_executable(python_embed_example wrappers.cpp)

# Link against Python libraries
target_link_libraries(python_embed_example PRIVATE pybind11::embed ${PYTHON_LIBRARIES} Qt6::Widgets BaseNaviWidgetLib)

# Set include directories
target_include_directories(python_embed_example PRIVATE ${Python_INCLUDE_DIRS} ${pybind11_INCLUDE_DIRS})

# Set the Python executable path if needed (optional, depending on your setup)
set_target_properties(python_embed_example PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_NAME python_embed_example
)

add_custom_target(copy_python_file ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/test.py ${CMAKE_BINARY_DIR}/bin/
)