cmake_minimum_required(VERSION 3.9.2 FATAL_ERROR)

setup_exe(bluetooth_test)
link_project(bluetooth)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "tests")
