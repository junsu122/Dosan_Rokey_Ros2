cmake_minimum_required(VERSION 3.8)
project(cpp_qt_plugin)

set(CMAKE_CXX_STANDARD 17)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

set(SOURCES
    src/main.cpp
)
set(HEADERS
)

# Add compile options for GNU or Clang compilers
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Enable AUTOMOC for Qt meta-object compiler
set(CMAKE_AUTOMOC ON)

# Define executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include ${Python3_INCLUDE_DIRS})

# Link libraries - don't forget
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets ${Python3_LIBRARIES})

# Specify ament dependencies - don't forget
ament_target_dependencies(${PROJECT_NAME} rclcpp std_msgs Python3)

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Enable linting if BUILD_TESTING is enabled
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()