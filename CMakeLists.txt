cmake_minimum_required(VERSION 3.5)
project(chico_gz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(
  ${GAZEBO_INCLUDE_DIRS}
  ${rclcpp_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
)

link_directories(${GAZEBO_LIBRARY_DIRS})

# plugin
add_library(plugin SHARED src/plugin.cc)
ament_target_dependencies(plugin rclcpp gazebo_ros std_msgs)
target_link_libraries(plugin ${GAZEBO_LIBRARIES} ${rclcpp_LIBRARIES})

# plugin_control
# add_library(plugin_control SHARED src/plugin_control.cc)
# ament_target_dependencies(plugin_control gazebo)
# target_link_libraries(plugin_control ${GAZEBO_LIBRARIES})

install(TARGETS 
  plugin
  # plugin_control
  LIBRARY DESTINATION lib
)

install(DIRECTORY
  launch
  worlds
  models
  DESTINATION share/${PROJECT_NAME}
)

if(build_testing)
  find_package(ament_lint_auto required)
  set(ament_cmake_copyright_found true)
  set(ament_cmake_cpplint_found true)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

