# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /home/maciej/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/maciej/.local/share/JetBrains/Toolbox/apps/clion/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release

# Include any dependencies generated for this target.
include mk459179/reference/CMakeFiles/reference.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mk459179/reference/CMakeFiles/reference.dir/compiler_depend.make

# Include the progress variables for this target.
include mk459179/reference/CMakeFiles/reference.dir/progress.make

# Include the compile flags for this target's objects.
include mk459179/reference/CMakeFiles/reference.dir/flags.make

mk459179/reference/CMakeFiles/reference.dir/main.c.o: mk459179/reference/CMakeFiles/reference.dir/flags.make
mk459179/reference/CMakeFiles/reference.dir/main.c.o: /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/reference/main.c
mk459179/reference/CMakeFiles/reference.dir/main.c.o: mk459179/reference/CMakeFiles/reference.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mk459179/reference/CMakeFiles/reference.dir/main.c.o"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mk459179/reference/CMakeFiles/reference.dir/main.c.o -MF CMakeFiles/reference.dir/main.c.o.d -o CMakeFiles/reference.dir/main.c.o -c /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/reference/main.c

mk459179/reference/CMakeFiles/reference.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/reference.dir/main.c.i"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/reference/main.c > CMakeFiles/reference.dir/main.c.i

mk459179/reference/CMakeFiles/reference.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/reference.dir/main.c.s"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/reference/main.c -o CMakeFiles/reference.dir/main.c.s

# Object files for target reference
reference_OBJECTS = \
"CMakeFiles/reference.dir/main.c.o"

# External object files for target reference
reference_EXTERNAL_OBJECTS =

mk459179/reference/reference: mk459179/reference/CMakeFiles/reference.dir/main.c.o
mk459179/reference/reference: mk459179/reference/CMakeFiles/reference.dir/build.make
mk459179/reference/reference: mk459179/common/libio.a
mk459179/reference/reference: mk459179/common/liberr.a
mk459179/reference/reference: mk459179/reference/CMakeFiles/reference.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable reference"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reference.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mk459179/reference/CMakeFiles/reference.dir/build: mk459179/reference/reference
.PHONY : mk459179/reference/CMakeFiles/reference.dir/build

mk459179/reference/CMakeFiles/reference.dir/clean:
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference && $(CMAKE_COMMAND) -P CMakeFiles/reference.dir/cmake_clean.cmake
.PHONY : mk459179/reference/CMakeFiles/reference.dir/clean

mk459179/reference/CMakeFiles/reference.dir/depend:
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/reference /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-release/mk459179/reference/CMakeFiles/reference.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : mk459179/reference/CMakeFiles/reference.dir/depend

