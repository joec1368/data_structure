# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/chenyuchiao/Desktop/ds/min_heap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/min_heap.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/min_heap.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/min_heap.dir/flags.make

CMakeFiles/min_heap.dir/main.c.o: CMakeFiles/min_heap.dir/flags.make
CMakeFiles/min_heap.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/min_heap.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/min_heap.dir/main.c.o -c /Users/chenyuchiao/Desktop/ds/min_heap/main.c

CMakeFiles/min_heap.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/min_heap.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/chenyuchiao/Desktop/ds/min_heap/main.c > CMakeFiles/min_heap.dir/main.c.i

CMakeFiles/min_heap.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/min_heap.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/chenyuchiao/Desktop/ds/min_heap/main.c -o CMakeFiles/min_heap.dir/main.c.s

# Object files for target min_heap
min_heap_OBJECTS = \
"CMakeFiles/min_heap.dir/main.c.o"

# External object files for target min_heap
min_heap_EXTERNAL_OBJECTS =

min_heap: CMakeFiles/min_heap.dir/main.c.o
min_heap: CMakeFiles/min_heap.dir/build.make
min_heap: CMakeFiles/min_heap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable min_heap"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/min_heap.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/min_heap.dir/build: min_heap
.PHONY : CMakeFiles/min_heap.dir/build

CMakeFiles/min_heap.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/min_heap.dir/cmake_clean.cmake
.PHONY : CMakeFiles/min_heap.dir/clean

CMakeFiles/min_heap.dir/depend:
	cd /Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chenyuchiao/Desktop/ds/min_heap /Users/chenyuchiao/Desktop/ds/min_heap /Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug /Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug /Users/chenyuchiao/Desktop/ds/min_heap/cmake-build-debug/CMakeFiles/min_heap.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/min_heap.dir/depend

