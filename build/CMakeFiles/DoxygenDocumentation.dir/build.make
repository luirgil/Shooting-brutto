# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\MinGW\bin\cmake.exe

# The command to remove a file.
RM = C:\MinGW\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting\build

# Utility rule file for DoxygenDocumentation.

# Include any custom commands dependencies for this target.
include CMakeFiles/DoxygenDocumentation.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DoxygenDocumentation.dir/progress.make

CMakeFiles/DoxygenDocumentation:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating Doxygen documentation"
	C:\MinGW\bin\doxygen.exe C:/Users/luigi/OneDrive/Documenti/Programmazione/cpp/Shooting/build/MakeDocumentation

DoxygenDocumentation: CMakeFiles/DoxygenDocumentation
DoxygenDocumentation: CMakeFiles/DoxygenDocumentation.dir/build.make
.PHONY : DoxygenDocumentation

# Rule to build all files generated by this target.
CMakeFiles/DoxygenDocumentation.dir/build: DoxygenDocumentation
.PHONY : CMakeFiles/DoxygenDocumentation.dir/build

CMakeFiles/DoxygenDocumentation.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\DoxygenDocumentation.dir\cmake_clean.cmake
.PHONY : CMakeFiles/DoxygenDocumentation.dir/clean

CMakeFiles/DoxygenDocumentation.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting\build C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting\build C:\Users\luigi\OneDrive\Documenti\Programmazione\cpp\Shooting\build\CMakeFiles\DoxygenDocumentation.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DoxygenDocumentation.dir/depend
