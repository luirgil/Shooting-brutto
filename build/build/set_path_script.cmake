# set_path_script.cmake.in
# Script to set the PATH environment variable
SET(NEW_PATH "${CMAKE_CURRENT_BINARY_DIR};${CMAKE_CURRENT_BINARY_DIR}/bin;${ENV{PATH}}")
SET(ENV{PATH} )
