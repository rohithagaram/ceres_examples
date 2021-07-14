cmake_minimum_required(VERSION 3.9)
project(simple_ceres)

# # Google Logging
# message("-- Check for Google Log")
# find_package(Glog REQUIRED)
# if(GLOG_FOUND)
# 	message("-- Found Google Logging: ${GLOG_INCLUDE_DIRS}")
# else(GLOG_FOUND)
# 	message(FATAL_ERROR "Can't find Google Logging. Please set GLOG_INCLUDE_DIR & GLOG_LIBRARY")
# endif(GLOG_FOUND)

# Ceres Solver
set(Ceres_DIR "C:/Program Files/Ceres/bin")
message("-- Check for Ceres solver")
find_package(Ceres REQUIRED)
if(CERES_FOUND)
	message("-- Found Ceres Solver: ${CERES_INCLUDE_DIRS}")
else(CERES_FOUND)
	message(FATAL_ERROR "Can't find Ceres Solver. Please set CERES_INCLUDE_DIR & CERES_LIBRARY")
endif(CERES_FOUND)

include_directories(${CMAKE_INCLUDE_PATH} ${CERES_INCLUDE_DIRS})

# Add the executableqqq
add_executable(ceres_trial ceres_trial.cpp )
target_link_libraries(ceres_trial ${CERES_LIBRARIES})


