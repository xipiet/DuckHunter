# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter"

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.o: main.cpp
CMakeFiles/main.dir/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/main.cpp.o -MF CMakeFiles/main.dir/main.cpp.o.d -o CMakeFiles/main.dir/main.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/main.cpp"

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/main.cpp" > CMakeFiles/main.dir/main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/main.cpp" -o CMakeFiles/main.dir/main.cpp.s

CMakeFiles/main.dir/gameloop.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/gameloop.cpp.o: gameloop.cpp
CMakeFiles/main.dir/gameloop.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/gameloop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/gameloop.cpp.o -MF CMakeFiles/main.dir/gameloop.cpp.o.d -o CMakeFiles/main.dir/gameloop.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gameloop.cpp"

CMakeFiles/main.dir/gameloop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/gameloop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gameloop.cpp" > CMakeFiles/main.dir/gameloop.cpp.i

CMakeFiles/main.dir/gameloop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/gameloop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gameloop.cpp" -o CMakeFiles/main.dir/gameloop.cpp.s

CMakeFiles/main.dir/vogel.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/vogel.cpp.o: vogel.cpp
CMakeFiles/main.dir/vogel.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/vogel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/vogel.cpp.o -MF CMakeFiles/main.dir/vogel.cpp.o.d -o CMakeFiles/main.dir/vogel.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/vogel.cpp"

CMakeFiles/main.dir/vogel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/vogel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/vogel.cpp" > CMakeFiles/main.dir/vogel.cpp.i

CMakeFiles/main.dir/vogel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/vogel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/vogel.cpp" -o CMakeFiles/main.dir/vogel.cpp.s

CMakeFiles/main.dir/msleep.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/msleep.cpp.o: msleep.cpp
CMakeFiles/main.dir/msleep.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/msleep.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/msleep.cpp.o -MF CMakeFiles/main.dir/msleep.cpp.o.d -o CMakeFiles/main.dir/msleep.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/msleep.cpp"

CMakeFiles/main.dir/msleep.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/msleep.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/msleep.cpp" > CMakeFiles/main.dir/msleep.cpp.i

CMakeFiles/main.dir/msleep.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/msleep.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/msleep.cpp" -o CMakeFiles/main.dir/msleep.cpp.s

CMakeFiles/main.dir/windmill.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/windmill.cpp.o: windmill.cpp
CMakeFiles/main.dir/windmill.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/windmill.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/windmill.cpp.o -MF CMakeFiles/main.dir/windmill.cpp.o.d -o CMakeFiles/main.dir/windmill.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/windmill.cpp"

CMakeFiles/main.dir/windmill.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/windmill.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/windmill.cpp" > CMakeFiles/main.dir/windmill.cpp.i

CMakeFiles/main.dir/windmill.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/windmill.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/windmill.cpp" -o CMakeFiles/main.dir/windmill.cpp.s

CMakeFiles/main.dir/gamestate.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/gamestate.cpp.o: gamestate.cpp
CMakeFiles/main.dir/gamestate.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/gamestate.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/gamestate.cpp.o -MF CMakeFiles/main.dir/gamestate.cpp.o.d -o CMakeFiles/main.dir/gamestate.cpp.o -c "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gamestate.cpp"

CMakeFiles/main.dir/gamestate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/gamestate.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gamestate.cpp" > CMakeFiles/main.dir/gamestate.cpp.i

CMakeFiles/main.dir/gamestate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/gamestate.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/gamestate.cpp" -o CMakeFiles/main.dir/gamestate.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.o" \
"CMakeFiles/main.dir/gameloop.cpp.o" \
"CMakeFiles/main.dir/vogel.cpp.o" \
"CMakeFiles/main.dir/msleep.cpp.o" \
"CMakeFiles/main.dir/windmill.cpp.o" \
"CMakeFiles/main.dir/gamestate.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/main.cpp.o
main: CMakeFiles/main.dir/gameloop.cpp.o
main: CMakeFiles/main.dir/vogel.cpp.o
main: CMakeFiles/main.dir/msleep.cpp.o
main: CMakeFiles/main.dir/windmill.cpp.o
main: CMakeFiles/main.dir/gamestate.cpp.o
main: CMakeFiles/main.dir/build.make
main: libasciigfx.a
main: /usr/lib/x86_64-linux-gnu/libcurses.so
main: /usr/lib/x86_64-linux-gnu/libform.so
main: /usr/lib/x86_64-linux-gnu/libSDLmain.a
main: /usr/lib/x86_64-linux-gnu/libSDL.so
main: /usr/lib/x86_64-linux-gnu/libSDL_mixer.so
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter" "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter" "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter" "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter" "/home/peter/Documents/Uni/Prog/02 Semester/Prog pr/DuckHunter/CMakeFiles/main.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

