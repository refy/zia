# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/lespag_m/Documents/Tek3/ZIA/local

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lespag_m/Documents/Tek3/ZIA/local

# Include any dependencies generated for this target.
include modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/depend.make

# Include the progress variables for this target.
include modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/progress.make

# Include the compile flags for this target's objects.
include modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/flags.make

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/flags.make
modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o: modules/PreSendRequest/sources/PreSendRequest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/lespag_m/Documents/Tek3/ZIA/local/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o"
	cd /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o -c /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest/sources/PreSendRequest.cpp

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.i"
	cd /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest/sources/PreSendRequest.cpp > CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.i

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.s"
	cd /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest/sources/PreSendRequest.cpp -o CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.s

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.requires:
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.requires

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.provides: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.requires
	$(MAKE) -f modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/build.make modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.provides.build
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.provides

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.provides.build: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o

# Object files for target PreSendRequest
PreSendRequest_OBJECTS = \
"CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o"

# External object files for target PreSendRequest
PreSendRequest_EXTERNAL_OBJECTS =

modules/PreSendRequest/libPreSendRequest.so: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o
modules/PreSendRequest/libPreSendRequest.so: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/build.make
modules/PreSendRequest/libPreSendRequest.so: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libPreSendRequest.so"
	cd /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PreSendRequest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/build: modules/PreSendRequest/libPreSendRequest.so
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/build

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/requires: modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/sources/PreSendRequest.cpp.o.requires
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/requires

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/clean:
	cd /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest && $(CMAKE_COMMAND) -P CMakeFiles/PreSendRequest.dir/cmake_clean.cmake
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/clean

modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/depend:
	cd /home/lespag_m/Documents/Tek3/ZIA/local && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lespag_m/Documents/Tek3/ZIA/local /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest /home/lespag_m/Documents/Tek3/ZIA/local /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest /home/lespag_m/Documents/Tek3/ZIA/local/modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/PreSendRequest/CMakeFiles/PreSendRequest.dir/depend

