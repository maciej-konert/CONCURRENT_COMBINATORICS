# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maciej/MIMUW/PW/task2/mk459179/mk459179

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest

# Include any dependencies generated for this target.
include parallel/CMakeFiles/parallel.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include parallel/CMakeFiles/parallel.dir/compiler_depend.make

# Include the progress variables for this target.
include parallel/CMakeFiles/parallel.dir/progress.make

# Include the compile flags for this target's objects.
include parallel/CMakeFiles/parallel.dir/flags.make

parallel/CMakeFiles/parallel.dir/main.c.o: parallel/CMakeFiles/parallel.dir/flags.make
parallel/CMakeFiles/parallel.dir/main.c.o: /home/maciej/MIMUW/PW/task2/mk459179/mk459179/parallel/main.c
parallel/CMakeFiles/parallel.dir/main.c.o: parallel/CMakeFiles/parallel.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object parallel/CMakeFiles/parallel.dir/main.c.o"
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT parallel/CMakeFiles/parallel.dir/main.c.o -MF CMakeFiles/parallel.dir/main.c.o.d -o CMakeFiles/parallel.dir/main.c.o -c /home/maciej/MIMUW/PW/task2/mk459179/mk459179/parallel/main.c

parallel/CMakeFiles/parallel.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/parallel.dir/main.c.i"
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maciej/MIMUW/PW/task2/mk459179/mk459179/parallel/main.c > CMakeFiles/parallel.dir/main.c.i

parallel/CMakeFiles/parallel.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/parallel.dir/main.c.s"
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maciej/MIMUW/PW/task2/mk459179/mk459179/parallel/main.c -o CMakeFiles/parallel.dir/main.c.s

# Object files for target parallel
parallel_OBJECTS = \
"CMakeFiles/parallel.dir/main.c.o"

# External object files for target parallel
parallel_EXTERNAL_OBJECTS =

parallel/parallel: parallel/CMakeFiles/parallel.dir/main.c.o
parallel/parallel: parallel/CMakeFiles/parallel.dir/build.make
parallel/parallel: common/libio.a
parallel/parallel: common/liberr.a
parallel/parallel: parallel/CMakeFiles/parallel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable parallel"
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parallel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
parallel/CMakeFiles/parallel.dir/build: parallel/parallel
.PHONY : parallel/CMakeFiles/parallel.dir/build

parallel/CMakeFiles/parallel.dir/clean:
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel && $(CMAKE_COMMAND) -P CMakeFiles/parallel.dir/cmake_clean.cmake
.PHONY : parallel/CMakeFiles/parallel.dir/clean

parallel/CMakeFiles/parallel.dir/depend:
	cd /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maciej/MIMUW/PW/task2/mk459179/mk459179 /home/maciej/MIMUW/PW/task2/mk459179/mk459179/parallel /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel /home/maciej/MIMUW/PW/task2/mk459179/mk459179/buildtest/parallel/CMakeFiles/parallel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : parallel/CMakeFiles/parallel.dir/depend

