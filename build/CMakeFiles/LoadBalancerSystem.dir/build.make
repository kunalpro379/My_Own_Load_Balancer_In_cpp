# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\cmake-3.28.1-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = C:\cmake-3.28.1-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build"

# Include any dependencies generated for this target.
include CMakeFiles/LoadBalancerSystem.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LoadBalancerSystem.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LoadBalancerSystem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LoadBalancerSystem.dir/flags.make

CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj: CMakeFiles/LoadBalancerSystem.dir/flags.make
CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj: CMakeFiles/LoadBalancerSystem.dir/includes_CXX.rsp
CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj: C:/Users/kunal/OneDrive/CODE\ FOR\ LIFE/BuildFromScratch/LoadBalancerFromScratch/src/main.cpp
CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj: CMakeFiles/LoadBalancerSystem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj -MF CMakeFiles\LoadBalancerSystem.dir\src\main.cpp.obj.d -o CMakeFiles\LoadBalancerSystem.dir\src\main.cpp.obj -c "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\src\main.cpp"

CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\src\main.cpp" > CMakeFiles\LoadBalancerSystem.dir\src\main.cpp.i

CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\src\main.cpp" -o CMakeFiles\LoadBalancerSystem.dir\src\main.cpp.s

# Object files for target LoadBalancerSystem
LoadBalancerSystem_OBJECTS = \
"CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj"

# External object files for target LoadBalancerSystem
LoadBalancerSystem_EXTERNAL_OBJECTS =

LoadBalancerSystem.exe: CMakeFiles/LoadBalancerSystem.dir/src/main.cpp.obj
LoadBalancerSystem.exe: CMakeFiles/LoadBalancerSystem.dir/build.make
LoadBalancerSystem.exe: client/libclient.a
LoadBalancerSystem.exe: CMakeFiles/LoadBalancerSystem.dir/linkLibs.rsp
LoadBalancerSystem.exe: CMakeFiles/LoadBalancerSystem.dir/objects1.rsp
LoadBalancerSystem.exe: CMakeFiles/LoadBalancerSystem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LoadBalancerSystem.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LoadBalancerSystem.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LoadBalancerSystem.dir/build: LoadBalancerSystem.exe
.PHONY : CMakeFiles/LoadBalancerSystem.dir/build

CMakeFiles/LoadBalancerSystem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LoadBalancerSystem.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LoadBalancerSystem.dir/clean

CMakeFiles/LoadBalancerSystem.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch" "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch" "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build" "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build" "C:\Users\kunal\OneDrive\CODE FOR LIFE\BuildFromScratch\LoadBalancerFromScratch\build\CMakeFiles\LoadBalancerSystem.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/LoadBalancerSystem.dir/depend

