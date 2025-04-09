cmake_minimum_required(VERSION 3.8)
project(laser_rahcm_simulation)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)

include_directories(
  include
  ${Boost_INCLUDE_DIRS}
  ${Eigen3_INCLUDE_DIRS}
  ${GAZEBO_INCLUDE_DIRS}
  ${GAZEBO_MSG_INCLUDE_DIRS}
  ${IGNITION-COMMON_INCLUDE_DIRS}
  ${IGNITION-MATHS_INCLUDE_DIRS}
  ${IGNITION-MSGS_INCLUDE_DIRS}
)

add_library(Hydrodynamics SHARED
  src/Gazebo.cc
  src/Geometry.cc
  src/PhysicalConstants.cc
  src/Physics.cc
  src/Utilities.cc
  src/Wavefield.cc
  src/WavefieldEntity.cc
)
target_link_libraries(Hydrodynamics
  ${Boost_LIBRARIES}
  ${gazebo_ros_LIBRARIES}
  ${GAZEBO_LIBRARIES}
)
target_compile_options(Hydrodynamics PRIVATE "-Wno-unknown-pragmas")
set(WAVE_GAZEBO_LIBRARIES_LIST Hydrodynamics)

add_library(WavefieldModelPlugin SHARED
  src/WavefieldModelPlugin.cc
)
target_link_libraries(WavefieldModelPlugin
  ${Boost_LIBRARIES}
  ${gazebo_ros_LIBRARIES}
  ${GAZEBO_LIBRARIES}
  ${WAVE_GAZEBO_LIBRARIES_LIST}
)
target_compile_options(WavefieldModelPlugin PRIVATE "-Wno-unknown-pragmas")
set(WAVE_GAZEBO_PLUGINS_LIST WavefieldModelPlugin)

add_library(WavefieldVisualPlugin SHARED
  src/WavefieldVisualPlugin.cc
)
target_link_libraries(WavefieldVisualPlugin
  ${Boost_LIBRARIES}
  ${gazebo_ros_LIBRARIES}
  ${GAZEBO_LIBRARIES}
  ${WAVE_GAZEBO_LIBRARIES_LIST}
)
target_compile_options(WavefieldVisualPlugin PRIVATE "-Wno-unknown-pragmas")
list(APPEND WAVE_GAZEBO_PLUGINS_LIST WavefieldVisualPlugin)

add_library(wavegauge_plugin SHARED
  src/wavegauge_plugin.cc
)
target_link_libraries(wavegauge_plugin
  WavefieldModelPlugin
  ${Boost_LIBRARIES}
  ${gazebo_ros_LIBRARIES}
  ${GAZEBO_LIBRARIES}
  ${WAVE_GAZEBO_LIBRARIES_LIST}
)
add_dependencies(wavegauge_plugin WavefieldModelPlugin)
target_compile_options(wavegauge_plugin PRIVATE "-Wno-unknown-pragmas")
list(APPEND WAVE_GAZEBO_PLUGINS_LIST wavegauge_plugin)

install(TARGETS ${WAVE_GAZEBO_LIBRARIES_LIST} ${WAVE_GAZEBO_PLUGINS_LIST}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME}
  FILES_MATCHING PATTERN "*.hh"
  PATTERN "*~" EXCLUDE
)

install(DIRECTORY include/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hh"
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/
  DESTINATION include
  FILES_MATCHING PATTERN "*.pb.*"
  PATTERN "*~" EXCLUDE
)

ament_export_include_directories(include)
ament_export_libraries(Hydrodynamics WavefieldModelPlugin WavefieldVisualPlugin wavegauge_plugin)
ament_export_dependencies(gazebo_ros gazebo Eigen3 Boost)

ament_package()
