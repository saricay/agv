cmake_minimum_required(VERSION 2.8.3)

project(agv)

find_package(catkin REQUIRED COMPONENTS
  roscpp)

catkin_package()

find_package(roslaunch)

add_executable(move_agv src/move_agv.cpp)
add_dependencies(move_agv ${move_agv_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_agv
${catkin_LIBRARIES}
)

add_executable(move_to_pose src/move_to_pose.cpp)
add_dependencies(move_to_pose ${move_to_pose_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(move_to_pose
${catkin_LIBRARIES}
)

add_executable(read_odom src/read_odom.cpp)
add_dependencies(read_odom ${read_odom_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(read_odom
${catkin_LIBRARIES}
)

include_directories(include ${catkin_INCLUDE_DIRS})

foreach(dir config launch meshes urdf)
	install(DIRECTORY ${dir}/
		DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)
