# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /snap/cmake/1429/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1429/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build

# Include any dependencies generated for this target.
include CMakeFiles/MyApplication.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyApplication.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyApplication.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyApplication.dir/flags.make

CMakeFiles/MyApplication.dir/codegen:
.PHONY : CMakeFiles/MyApplication.dir/codegen

CMakeFiles/MyApplication.dir/src/main.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/main.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/main.c
CMakeFiles/MyApplication.dir/src/main.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyApplication.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/main.c.o -MF CMakeFiles/MyApplication.dir/src/main.c.o.d -o CMakeFiles/MyApplication.dir/src/main.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/main.c

CMakeFiles/MyApplication.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/main.c > CMakeFiles/MyApplication.dir/src/main.c.i

CMakeFiles/MyApplication.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/main.c -o CMakeFiles/MyApplication.dir/src/main.c.s

CMakeFiles/MyApplication.dir/src/threads_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/threads_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/threads_manager.c
CMakeFiles/MyApplication.dir/src/threads_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MyApplication.dir/src/threads_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/threads_manager.c.o -MF CMakeFiles/MyApplication.dir/src/threads_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/threads_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/threads_manager.c

CMakeFiles/MyApplication.dir/src/threads_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/threads_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/threads_manager.c > CMakeFiles/MyApplication.dir/src/threads_manager.c.i

CMakeFiles/MyApplication.dir/src/threads_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/threads_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/threads_manager.c -o CMakeFiles/MyApplication.dir/src/threads_manager.c.s

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_manager.c
CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o -MF CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_manager.c

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_manager.c > CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.i

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_manager.c -o CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.s

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_simulation.c
CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o -MF CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o.d -o CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_simulation.c

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_simulation.c > CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.i

CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/water_tank/water_tank_simulation.c -o CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.s

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_manager.c
CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o -MF CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_manager.c

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_manager.c > CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.i

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_manager.c -o CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.s

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_simulation.c
CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o -MF CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o.d -o CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_simulation.c

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_simulation.c > CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.i

CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/fuel_tank/fuel_tank_simulation.c -o CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.s

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gui.c
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o -MF CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o.d -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gui.c

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gui.c > CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.i

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gui.c -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.s

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_config.c
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o -MF CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o.d -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_config.c

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_config.c > CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.i

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_config.c -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.s

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gauge.c
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o -MF CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o.d -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gauge.c

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gauge.c > CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.i

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_gauge.c -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.s

CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/central_manager.c
CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o -MF CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/central_manager.c

CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/central_manager.c > CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.i

CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/central_manager.c -o CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.s

CMakeFiles/MyApplication.dir/src/pipes_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/pipes_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/pipes_manager.c
CMakeFiles/MyApplication.dir/src/pipes_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/MyApplication.dir/src/pipes_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/pipes_manager.c.o -MF CMakeFiles/MyApplication.dir/src/pipes_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/pipes_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/pipes_manager.c

CMakeFiles/MyApplication.dir/src/pipes_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/pipes_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/pipes_manager.c > CMakeFiles/MyApplication.dir/src/pipes_manager.c.i

CMakeFiles/MyApplication.dir/src/pipes_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/pipes_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/pipes_manager.c -o CMakeFiles/MyApplication.dir/src/pipes_manager.c.s

CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/values_average.c
CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o -MF CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o.d -o CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/values_average.c

CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/values_average.c > CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.i

CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/central_manager/values_average.c -o CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.s

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o: CMakeFiles/MyApplication.dir/flags.make
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o: /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_manager.c
CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o: CMakeFiles/MyApplication.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o -MF CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o.d -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o -c /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_manager.c

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_manager.c > CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.i

CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/src/control_panel/control_panel_manager.c -o CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.s

# Object files for target MyApplication
MyApplication_OBJECTS = \
"CMakeFiles/MyApplication.dir/src/main.c.o" \
"CMakeFiles/MyApplication.dir/src/threads_manager.c.o" \
"CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o" \
"CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o" \
"CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o" \
"CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o" \
"CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o" \
"CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o" \
"CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o" \
"CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o" \
"CMakeFiles/MyApplication.dir/src/pipes_manager.c.o" \
"CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o" \
"CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o"

# External object files for target MyApplication
MyApplication_EXTERNAL_OBJECTS =

MyApplication: CMakeFiles/MyApplication.dir/src/main.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/threads_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/water_tank/water_tank_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/water_tank/water_tank_simulation.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/fuel_tank/fuel_tank_simulation.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gui.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/control_panel/control_panel_config.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/control_panel/control_panel_gauge.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/central_manager/central_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/pipes_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/central_manager/values_average.c.o
MyApplication: CMakeFiles/MyApplication.dir/src/control_panel/control_panel_manager.c.o
MyApplication: CMakeFiles/MyApplication.dir/build.make
MyApplication: CMakeFiles/MyApplication.dir/compiler_depend.ts
MyApplication: /usr/lib/x86_64-linux-gnu/libSDL2.so
MyApplication: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
MyApplication: CMakeFiles/MyApplication.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C executable MyApplication"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyApplication.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyApplication.dir/build: MyApplication
.PHONY : CMakeFiles/MyApplication.dir/build

CMakeFiles/MyApplication.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyApplication.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyApplication.dir/clean

CMakeFiles/MyApplication.dir/depend:
	cd /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build /home/gregoire/ENSSAT/IAI-2/Systemes-TempsReel/Projet/build/CMakeFiles/MyApplication.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyApplication.dir/depend

