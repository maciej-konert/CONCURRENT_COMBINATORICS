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
CMAKE_BINARY_DIR = /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug

# Include any dependencies generated for this target.
include mk459179/common/CMakeFiles/io.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include mk459179/common/CMakeFiles/io.dir/compiler_depend.make

# Include the progress variables for this target.
include mk459179/common/CMakeFiles/io.dir/progress.make

# Include the compile flags for this target's objects.
include mk459179/common/CMakeFiles/io.dir/flags.make

mk459179/common/CMakeFiles/io.dir/io.c.o: mk459179/common/CMakeFiles/io.dir/flags.make
mk459179/common/CMakeFiles/io.dir/io.c.o: /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/common/io.c
mk459179/common/CMakeFiles/io.dir/io.c.o: mk459179/common/CMakeFiles/io.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mk459179/common/CMakeFiles/io.dir/io.c.o"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT mk459179/common/CMakeFiles/io.dir/io.c.o -MF CMakeFiles/io.dir/io.c.o.d -o CMakeFiles/io.dir/io.c.o -c /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/common/io.c

mk459179/common/CMakeFiles/io.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/io.dir/io.c.i"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/common/io.c > CMakeFiles/io.dir/io.c.i

mk459179/common/CMakeFiles/io.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/io.dir/io.c.s"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/common/io.c -o CMakeFiles/io.dir/io.c.s

# Object files for target io
io_OBJECTS = \
"CMakeFiles/io.dir/io.c.o"

# External object files for target io
io_EXTERNAL_OBJECTS =

mk459179/common/libio.a: mk459179/common/CMakeFiles/io.dir/io.c.o
mk459179/common/libio.a: mk459179/common/CMakeFiles/io.dir/build.make
mk459179/common/libio.a: mk459179/common/CMakeFiles/io.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libio.a"
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && $(CMAKE_COMMAND) -P CMakeFiles/io.dir/cmake_clean_target.cmake
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/io.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mk459179/common/CMakeFiles/io.dir/build: mk459179/common/libio.a
.PHONY : mk459179/common/CMakeFiles/io.dir/build

mk459179/common/CMakeFiles/io.dir/clean:
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common && $(CMAKE_COMMAND) -P CMakeFiles/io.dir/cmake_clean.cmake
.PHONY : mk459179/common/CMakeFiles/io.dir/clean

mk459179/common/CMakeFiles/io.dir/depend:
	cd /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/mk459179/common /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common /home/maciej/MIMUW/ASD/CONCURRENT_COMBINATORICS/cmake-build-debug/mk459179/common/CMakeFiles/io.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : mk459179/common/CMakeFiles/io.dir/depend

