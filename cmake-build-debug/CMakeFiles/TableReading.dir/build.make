# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/bozhidar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.126/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/bozhidar/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.6668.126/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bozhidar/Desktop/TableReading

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bozhidar/Desktop/TableReading/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TableReading.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TableReading.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TableReading.dir/flags.make

CMakeFiles/TableReading.dir/main.cpp.o: CMakeFiles/TableReading.dir/flags.make
CMakeFiles/TableReading.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bozhidar/Desktop/TableReading/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TableReading.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TableReading.dir/main.cpp.o -c /home/bozhidar/Desktop/TableReading/main.cpp

CMakeFiles/TableReading.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TableReading.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bozhidar/Desktop/TableReading/main.cpp > CMakeFiles/TableReading.dir/main.cpp.i

CMakeFiles/TableReading.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TableReading.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bozhidar/Desktop/TableReading/main.cpp -o CMakeFiles/TableReading.dir/main.cpp.s

# Object files for target TableReading
TableReading_OBJECTS = \
"CMakeFiles/TableReading.dir/main.cpp.o"

# External object files for target TableReading
TableReading_EXTERNAL_OBJECTS =

TableReading: CMakeFiles/TableReading.dir/main.cpp.o
TableReading: CMakeFiles/TableReading.dir/build.make
TableReading: CMakeFiles/TableReading.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bozhidar/Desktop/TableReading/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TableReading"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TableReading.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TableReading.dir/build: TableReading

.PHONY : CMakeFiles/TableReading.dir/build

CMakeFiles/TableReading.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TableReading.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TableReading.dir/clean

CMakeFiles/TableReading.dir/depend:
	cd /home/bozhidar/Desktop/TableReading/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bozhidar/Desktop/TableReading /home/bozhidar/Desktop/TableReading /home/bozhidar/Desktop/TableReading/cmake-build-debug /home/bozhidar/Desktop/TableReading/cmake-build-debug /home/bozhidar/Desktop/TableReading/cmake-build-debug/CMakeFiles/TableReading.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TableReading.dir/depend

