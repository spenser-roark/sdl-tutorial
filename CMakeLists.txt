cmake_minimum_required(VERSION 3.0)
project(csdl)

# See CMP0003 for policy details
# No need for the backwards compatibility for now so setting to new
cmake_policy(SET CMP0003 NEW)

# Adding this just in case we want the old stuff at some future date
if (COMMAND old_policy_0003)
cmake_policy(SET CMP0003 OLD)
endif(COMMAND old_policy_0003)

# Non compilation directories we need to include
# headers, image files, etc
include_directories(include)

set(INCLUDE_LIBS ${INCLUDE_LIBS} res_path)
set(INCLUDE_LIBS ${INCLUDE_LIBS} sdl_utils)
set(INCLUDE_LIBS ${INCLUDE_LIBS} errors)
set(INCLUDE_LIBS ${INCLUDE_LIBS} DestroySdlObjects)
set(INCLUDE_LIBS ${INCLUDE_LIBS} splash)
set(INCLUDE_LIBS ${INCLUDE_LIBS} SDL2)
set(INCLUDE_LIBS ${INCLUDE_LIBS} SDL2_image)


set(CSDL_VERSION_MAJOR 1)
set(CSDL_VERSION_MINOR 0)

# At some point I'd like to move this to a user readable config file, but this works for now
set(SCREEN_WIDTH 1024)
set(SCREEN_HEIGHT 768)


# Source code subdirectories
add_subdirectory(src)

# Set flags here
set(CPP_FLAGS ${CPP_FLAGS} "-std=c++11")

# This configures the file, IMMEDIATELY, so do it after everything else it depends on is done
# This changes the variable names SCREEN_WIDTH and HEIGHT in the file to the ones set above
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config/settings.h.in"
  "${PROJECT_SOURCE_DIR}/include/settings.h"
  )

# Add executables here
add_executable(ResourcePathTest l0/TestResourcePath.cpp)
add_executable(lesson1 l1/main.cpp)
add_executable(lesson2 l2/main.cpp)
add_executable(lesson3 l3/main.cpp)
add_executable(lesson4 l4/main.cpp)
add_executable(lesson5 l5/main.cpp)
add_executable(lesson6 l6/main.cpp)

# this is the -l so in compilation it becomes -lSDL2 which was the requirement
# going from the top level the command we needed to run was
# g++ l0/TestResourcePath.cpp -Iinclude -lSDL2

target_link_libraries(ResourcePathTest ${INCLUDE_LIBS})

target_link_libraries(lesson1 ${INCLUDE_LIBS})
set_Target_properties(lesson1 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(lesson2 ${INCLUDE_LIBS})
set_Target_properties(lesson2 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(lesson3 ${INCLUDE_LIBS})
set_Target_properties(lesson3 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(lesson4 ${INCLUDE_LIBS})
set_Target_properties(lesson4 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(lesson5 ${INCLUDE_LIBS})
set_Target_properties(lesson5 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(lesson6 ${INCLUDE_LIBS})
set_Target_properties(lesson6 PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})
