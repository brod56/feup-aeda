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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug"

# Include any dependencies generated for this target.
include lib/googletest-master/googletest/CMakeFiles/gtest.dir/depend.make

# Include the progress variables for this target.
include lib/googletest-master/googletest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include lib/googletest-master/googletest/CMakeFiles/gtest.dir/flags.make

lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: lib/googletest-master/googletest/CMakeFiles/gtest.dir/flags.make
lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: ../lib/googletest-master/googletest/src/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/lib/googletest-master/googletest/src/gtest-all.cc"

lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/lib/googletest-master/googletest/src/gtest-all.cc" > CMakeFiles/gtest.dir/src/gtest-all.cc.i

lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/lib/googletest-master/googletest/src/gtest-all.cc" -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

lib/libgtestd.a: lib/googletest-master/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
lib/libgtestd.a: lib/googletest-master/googletest/CMakeFiles/gtest.dir/build.make
lib/libgtestd.a: lib/googletest-master/googletest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../libgtestd.a"
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/googletest-master/googletest/CMakeFiles/gtest.dir/build: lib/libgtestd.a

.PHONY : lib/googletest-master/googletest/CMakeFiles/gtest.dir/build

lib/googletest-master/googletest/CMakeFiles/gtest.dir/clean:
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : lib/googletest-master/googletest/CMakeFiles/gtest.dir/clean

lib/googletest-master/googletest/CMakeFiles/gtest.dir/depend:
	cd "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02" "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/lib/googletest-master/googletest" "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug" "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest" "/mnt/c/Users/brod5/OneDrive/Faculdade/2 ano/1 semestre/AEDA/Praticas/aeda2021_p02/cmake-build-debug/lib/googletest-master/googletest/CMakeFiles/gtest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : lib/googletest-master/googletest/CMakeFiles/gtest.dir/depend

