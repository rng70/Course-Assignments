# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = I:\JetBrains\ToolBox\apps\CLion\ch-0\193.6494.38\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = I:\JetBrains\ToolBox\apps\CLion\ch-0\193.6494.38\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/apsp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/apsp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/apsp.dir/flags.make

CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.obj: CMakeFiles/apsp.dir/flags.make
CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.obj: ../offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.obj"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\apsp.dir\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp.obj -c "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp"

CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.i"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp" > CMakeFiles\apsp.dir\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp.i

CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.s"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp" -o CMakeFiles\apsp.dir\offline_and_reports\Offline-3-Assignment_on_APSP\apsp.cpp.s

# Object files for target apsp
apsp_OBJECTS = \
"CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.obj"

# External object files for target apsp
apsp_EXTERNAL_OBJECTS =

apsp.exe: CMakeFiles/apsp.dir/offline_and_reports/Offline-3-Assignment_on_APSP/apsp.cpp.obj
apsp.exe: CMakeFiles/apsp.dir/build.make
apsp.exe: CMakeFiles/apsp.dir/linklibs.rsp
apsp.exe: CMakeFiles/apsp.dir/objects1.rsp
apsp.exe: CMakeFiles/apsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable apsp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\apsp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/apsp.dir/build: apsp.exe

.PHONY : CMakeFiles/apsp.dir/build

CMakeFiles/apsp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\apsp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/apsp.dir/clean

CMakeFiles/apsp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline" "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline" "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug" "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug" "D:\.assignments-And-Offlines-on-Data-Structure-and-Algorithms\cse208 - Data Structures and Algorithms Sessional\.clionProjectToDoOffline\cmake-build-debug\CMakeFiles\apsp.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/apsp.dir/depend
