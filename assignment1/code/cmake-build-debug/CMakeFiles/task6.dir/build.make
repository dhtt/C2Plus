# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/task6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task6.dir/flags.make

CMakeFiles/task6.dir/task6.cpp.o: CMakeFiles/task6.dir/flags.make
CMakeFiles/task6.dir/task6.cpp.o: ../task6.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task6.dir/task6.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/task6.dir/task6.cpp.o -c /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task6.cpp

CMakeFiles/task6.dir/task6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task6.dir/task6.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task6.cpp > CMakeFiles/task6.dir/task6.cpp.i

CMakeFiles/task6.dir/task6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task6.dir/task6.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task6.cpp -o CMakeFiles/task6.dir/task6.cpp.s

# Object files for target task6
task6_OBJECTS = \
"CMakeFiles/task6.dir/task6.cpp.o"

# External object files for target task6
task6_EXTERNAL_OBJECTS =

task6: CMakeFiles/task6.dir/task6.cpp.o
task6: CMakeFiles/task6.dir/build.make
task6: CMakeFiles/task6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task6.dir/build: task6

.PHONY : CMakeFiles/task6.dir/build

CMakeFiles/task6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task6.dir/clean

CMakeFiles/task6.dir/depend:
	cd /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles/task6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task6.dir/depend

