# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server"

# Include any dependencies generated for this target.
include test/CMakeFiles/parse_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/parse_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/parse_test.dir/flags.make

test/CMakeFiles/parse_test.dir/parse_test.cpp.o: test/CMakeFiles/parse_test.dir/flags.make
test/CMakeFiles/parse_test.dir/parse_test.cpp.o: test/parse_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/parse_test.dir/parse_test.cpp.o"
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/parse_test.dir/parse_test.cpp.o -c "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test/parse_test.cpp"

test/CMakeFiles/parse_test.dir/parse_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/parse_test.dir/parse_test.cpp.i"
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test/parse_test.cpp" > CMakeFiles/parse_test.dir/parse_test.cpp.i

test/CMakeFiles/parse_test.dir/parse_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/parse_test.dir/parse_test.cpp.s"
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test/parse_test.cpp" -o CMakeFiles/parse_test.dir/parse_test.cpp.s

test/CMakeFiles/parse_test.dir/parse_test.cpp.o.requires:

.PHONY : test/CMakeFiles/parse_test.dir/parse_test.cpp.o.requires

test/CMakeFiles/parse_test.dir/parse_test.cpp.o.provides: test/CMakeFiles/parse_test.dir/parse_test.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/parse_test.dir/build.make test/CMakeFiles/parse_test.dir/parse_test.cpp.o.provides.build
.PHONY : test/CMakeFiles/parse_test.dir/parse_test.cpp.o.provides

test/CMakeFiles/parse_test.dir/parse_test.cpp.o.provides.build: test/CMakeFiles/parse_test.dir/parse_test.cpp.o


# Object files for target parse_test
parse_test_OBJECTS = \
"CMakeFiles/parse_test.dir/parse_test.cpp.o"

# External object files for target parse_test
parse_test_EXTERNAL_OBJECTS =

test/parse_test: test/CMakeFiles/parse_test.dir/parse_test.cpp.o
test/parse_test: test/CMakeFiles/parse_test.dir/build.make
test/parse_test: /opt/local/lib/libboost_regex-mt.dylib
test/parse_test: /opt/local/lib/libboost_system-mt.dylib
test/parse_test: /opt/local/lib/libboost_thread-mt.dylib
test/parse_test: /opt/local/lib/libboost_filesystem-mt.dylib
test/parse_test: /opt/local/lib/libboost_date_time-mt.dylib
test/parse_test: test/CMakeFiles/parse_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable parse_test"
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/parse_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/parse_test.dir/build: test/parse_test

.PHONY : test/CMakeFiles/parse_test.dir/build

test/CMakeFiles/parse_test.dir/requires: test/CMakeFiles/parse_test.dir/parse_test.cpp.o.requires

.PHONY : test/CMakeFiles/parse_test.dir/requires

test/CMakeFiles/parse_test.dir/clean:
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" && $(CMAKE_COMMAND) -P CMakeFiles/parse_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/parse_test.dir/clean

test/CMakeFiles/parse_test.dir/depend:
	cd "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server" "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server" "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test" "/Users/msdias/Documents/Universidade Federal de Minas Gerais/2016 1/Information Retrieval/TP3/Web-Search/server/test/CMakeFiles/parse_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : test/CMakeFiles/parse_test.dir/depend

