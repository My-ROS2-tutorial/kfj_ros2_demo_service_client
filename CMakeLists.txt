cmake_minimum_required(VERSION 3.5)
project(kfj_ros2_demo_service_client)

set(CMAKE_PREFIX_PATH
    $ENV{CMAKE_PREFIX_PATH}
    ${CMAKE_PREFIX_PATH}
    )

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(kfj_ros2_demo_service_interface REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(client main.cpp)
ament_target_dependencies(client rclcpp kfj_ros2_demo_service_interface)

install(TARGETS client
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    )

ament_package()

