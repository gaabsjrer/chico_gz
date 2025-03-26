cmake_minimum_required(VERSION 3.5)
project(chico_gz)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(std_msgs REQUIRED)

add_library(plugin SHARED src/plugin.cc)
target_link_libraries(plugin ${GAZEBO_LIBRARIES} ${rclcpp_LIBRARIES})
ament_target_dependencies(plugin rclcpp gazebo_ros std_msgs)

install(TARGETS 
  plugin
  DESTINATION lib
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

