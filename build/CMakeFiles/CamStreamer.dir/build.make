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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/duoq/workplace/CamAndScreenStreamGstreamer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/duoq/workplace/CamAndScreenStreamGstreamer/build

# Include any dependencies generated for this target.
include CMakeFiles/CamStreamer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CamStreamer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CamStreamer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CamStreamer.dir/flags.make

CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o: CMakeFiles/CamStreamer.dir/flags.make
CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o: ../CamStreamer.cpp
CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o: CMakeFiles/CamStreamer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/duoq/workplace/CamAndScreenStreamGstreamer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o -MF CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o.d -o CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o -c /home/duoq/workplace/CamAndScreenStreamGstreamer/CamStreamer.cpp

CMakeFiles/CamStreamer.dir/CamStreamer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CamStreamer.dir/CamStreamer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/duoq/workplace/CamAndScreenStreamGstreamer/CamStreamer.cpp > CMakeFiles/CamStreamer.dir/CamStreamer.cpp.i

CMakeFiles/CamStreamer.dir/CamStreamer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CamStreamer.dir/CamStreamer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/duoq/workplace/CamAndScreenStreamGstreamer/CamStreamer.cpp -o CMakeFiles/CamStreamer.dir/CamStreamer.cpp.s

# Object files for target CamStreamer
CamStreamer_OBJECTS = \
"CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o"

# External object files for target CamStreamer
CamStreamer_EXTERNAL_OBJECTS =

CamStreamer: CMakeFiles/CamStreamer.dir/CamStreamer.cpp.o
CamStreamer: CMakeFiles/CamStreamer.dir/build.make
CamStreamer: CMakeFiles/CamStreamer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/duoq/workplace/CamAndScreenStreamGstreamer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable CamStreamer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CamStreamer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CamStreamer.dir/build: CamStreamer
.PHONY : CMakeFiles/CamStreamer.dir/build

CMakeFiles/CamStreamer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CamStreamer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CamStreamer.dir/clean

CMakeFiles/CamStreamer.dir/depend:
	cd /home/duoq/workplace/CamAndScreenStreamGstreamer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/duoq/workplace/CamAndScreenStreamGstreamer /home/duoq/workplace/CamAndScreenStreamGstreamer /home/duoq/workplace/CamAndScreenStreamGstreamer/build /home/duoq/workplace/CamAndScreenStreamGstreamer/build /home/duoq/workplace/CamAndScreenStreamGstreamer/build/CMakeFiles/CamStreamer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CamStreamer.dir/depend

