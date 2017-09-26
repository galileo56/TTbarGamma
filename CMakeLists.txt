cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)

project(RadiativeReturn CXX C)

## set correct path for external libraries
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

###############
## REQUIREMENTS & SETUP
## check whether this is a linux system
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(OperatingSystem "Linux")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	set(OperatingSystem "Mac OS X")
endif()
message(STATUS "Operating system: ${OperatingSystem}")

## set correct RPath for external (dynamic) libraries
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH true)

## find mathematica on the system
## Sascha Kratky's FindMathematica cmake module: https://github.com/sakra/FindMathematica/ [accessed 2015-03-06 01:00 AM]
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/tools")
find_package(Mathematica REQUIRED)

###############
## COMPILER FLAGS

## additional flags for c++ compiler - for c++ and clang++ (should also take effect for the C compiler)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(addition_cxx "-std=c++11")
## elseif ("" ... "") ## additional flags for other compilers
endif()

## let the flag changes take effect
set(CMAKE_CXX_FLAGS "${addition_cxx}" CACHE STRING "Flags used by the compiler during all build types." FORCE)

#-------------------------------------------------------------------------------
# find external packages
#-------------------------------------------------------------------------------

find_package(GSL REQUIRED)

###############
## LIBS

include_directories(include ${GSL_INCLUDE_DIRS} ${GSLCBLAS_INCLUDE_DIRS})

## include the information from ./lib/CmakeLists.txt
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

## find additional system libraries for example dynamic loader lib:
## find_library(DL_LIB dl)


###############
## EXE & LINKING

message(STATUS "Checking for mathlink library")
if(Mathematica_MathLink_LIBRARY)
	message(STATUS "Checking for mathlink library -- done")
	include_directories(${Mathematica_MathLink_INCLUDE_DIR})
	find_library(M_LIB m)
	find_library(DL_LIB dl)

	if("${OperatingSystem}" STREQUAL "Linux")
		find_library(UUID_LIB uuid)
		find_library(RT_LIB rt)
	endif()

	## build mathlink
	execute_process(COMMAND ${Mathematica_MathLink_MPREP_EXECUTABLE} -o ${CMAKE_CURRENT_SOURCE_DIR}/src/mathlink.tm.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/mathlink.tm ${CMAKE_CURRENT_SOURCE_DIR}/src/mathlink.cpp OUTPUT_QUIET)

	add_executable(mathlink src/mathlink.tm.cpp)
	target_link_libraries(mathlink ${GSL_LIBRARIES} libradiativereturn ${Mathematica_MathLink_LIBRARY} ${M_LIB} ${DL_LIB} ${UUID_LIB} ${RT_LIB})

else(Mathematica_MathLink_LIBRARY)
	message(STATUS "Checking for mathlink library -- not found, proceeding without mathlink")
endif()

add_executable(hello-world ${CMAKE_CURRENT_SOURCE_DIR}/src/hello-world.cpp)
target_link_libraries(hello-world libradiativereturn ${GSL_LIBRARIES})

## if additional system libraries are needed for example dynamic loader lib:
## target_link_libraries(executable_name libradiativereturn ${DL_LIB})

if(Mathematica_MathLink_LIBRARY)
	install(TARGETS mathlink DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

## the following line is dealing with a wrongly linked library in the mac executable. It might happen that at some point mathlink gets updated beyond Version 4.25 then one has to modify this line. We can discuss details at some other point
	if("${OperatingSystem}" STREQUAL "Mac OS X")
		install(CODE "execute_process(COMMAND install_name_tool -change /Volumes/Jenkins/workspace/MathLink.MacOSX-x86-64.release/scratch/CMake.build/lib/mathlink-libc++.framework/Versions/4.25/mathlink-libc++ ${Mathematica_MathLink_LIBRARY}/mathlink ${CMAKE_CURRENT_SOURCE_DIR}/bin/mathlink OUTPUT_QUIET)")
		install(CODE "execute_process(COMMAND install_name_tool -change /Volumes/Jenkins/workspace/MathLink.MacOSX-x86-64.10.0/scratch/CMake.build/lib/mathlink-libc++.framework/Versions/4.25/mathlink-libc++ ${Mathematica_MathLink_LIBRARY}/mathlink ${CMAKE_CURRENT_SOURCE_DIR}/bin/mathlink OUTPUT_QUIET)")
		install(CODE "execute_process(COMMAND install_name_tool -change @executable_path/../Frameworks/mathlink.framework/Versions/4.25/mathlink ${Mathematica_MathLink_LIBRARY}/mathlink ${CMAKE_CURRENT_SOURCE_DIR}/bin/mathlink OUTPUT_QUIET)")
		install(CODE "execute_process(COMMAND install_name_tool -change @executable_path/../Frameworks/mathlink.framework/Versions/4.36/mathlink ${Mathematica_MathLink_LIBRARY}/mathlink ${CMAKE_CURRENT_SOURCE_DIR}/bin/mathlink OUTPUT_QUIET)")
	endif()
endif()

install(TARGETS hello-world DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
