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
CMAKE_SOURCE_DIR = /Users/chenyuchiao/Desktop/ds/R_B_Tree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/R_B_Tree.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/R_B_Tree.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/R_B_Tree.dir/flags.make

CMakeFiles/R_B_Tree.dir/main.c.o: CMakeFiles/R_B_Tree.dir/flags.make
CMakeFiles/R_B_Tree.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/R_B_Tree.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/R_B_Tree.dir/main.c.o -c /Users/chenyuchiao/Desktop/ds/R_B_Tree/main.c

CMakeFiles/R_B_Tree.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/R_B_Tree.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/chenyuchiao/Desktop/ds/R_B_Tree/main.c > CMakeFiles/R_B_Tree.dir/main.c.i

CMakeFiles/R_B_Tree.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/R_B_Tree.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/chenyuchiao/Desktop/ds/R_B_Tree/main.c -o CMakeFiles/R_B_Tree.dir/main.c.s

# Object files for target R_B_Tree
R_B_Tree_OBJECTS = \
"CMakeFiles/R_B_Tree.dir/main.c.o"

# External object files for target R_B_Tree
R_B_Tree_EXTERNAL_OBJECTS =

R_B_Tree: CMakeFiles/R_B_Tree.dir/main.c.o
R_B_Tree: CMakeFiles/R_B_Tree.dir/build.make
R_B_Tree: CMakeFiles/R_B_Tree.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable R_B_Tree"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/R_B_Tree.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/R_B_Tree.dir/build: R_B_Tree
.PHONY : CMakeFiles/R_B_Tree.dir/build

CMakeFiles/R_B_Tree.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/R_B_Tree.dir/cmake_clean.cmake
.PHONY : CMakeFiles/R_B_Tree.dir/clean

CMakeFiles/R_B_Tree.dir/depend:
	cd /Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/chenyuchiao/Desktop/ds/R_B_Tree /Users/chenyuchiao/Desktop/ds/R_B_Tree /Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug /Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug /Users/chenyuchiao/Desktop/ds/R_B_Tree/cmake-build-debug/CMakeFiles/R_B_Tree.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/R_B_Tree.dir/depend
