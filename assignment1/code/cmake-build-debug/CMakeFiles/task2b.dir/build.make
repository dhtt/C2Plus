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
include CMakeFiles/task2b.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/task2b.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/task2b.dir/flags.make

CMakeFiles/task2b.dir/task2b.cpp.o: CMakeFiles/task2b.dir/flags.make
CMakeFiles/task2b.dir/task2b.cpp.o: ../task2b.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/task2b.dir/task2b.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/task2b.dir/task2b.cpp.o -c /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task2b.cpp

CMakeFiles/task2b.dir/task2b.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/task2b.dir/task2b.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task2b.cpp > CMakeFiles/task2b.dir/task2b.cpp.i

CMakeFiles/task2b.dir/task2b.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/task2b.dir/task2b.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/task2b.cpp -o CMakeFiles/task2b.dir/task2b.cpp.s

# Object files for target task2b
task2b_OBJECTS = \
"CMakeFiles/task2b.dir/task2b.cpp.o"

# External object files for target task2b
task2b_EXTERNAL_OBJECTS =

task2b: CMakeFiles/task2b.dir/task2b.cpp.o
task2b: CMakeFiles/task2b.dir/build.make
task2b: CMakeFiles/task2b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable task2b"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/task2b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/task2b.dir/build: task2b

.PHONY : CMakeFiles/task2b.dir/build

CMakeFiles/task2b.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/task2b.dir/cmake_clean.cmake
.PHONY : CMakeFiles/task2b.dir/clean

CMakeFiles/task2b.dir/depend:
	cd /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug /Users/dhthutrang/Documents/BIOINFO/Programmierung/Assignment/1/assignment1/code/cmake-build-debug/CMakeFiles/task2b.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/task2b.dir/depend

