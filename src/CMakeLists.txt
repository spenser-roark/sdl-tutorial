# Flags
set(CPP_FLAGS ${CPP_FLAGS} "-std=c++11")

#Cleanup fun
add_library(DestroySdlObjects cleanup/DestroySdlObjects.cpp)

# Utility definitions
add_library(res_path utilities/res_path.cpp)
add_library(sdl_utils utilities/sdl_utils.cpp)

# Error definitions
add_library(errors utilities/errors.cpp)

# Widgets!
add_library(splash widgets/splash.cpp)


set_target_properties(DestroySdlObjects PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})
set_target_properties(splash PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})
set_target_properties(sdl_utils PROPERTIES COMPILE_FLAGS ${CPP_FLAGS})

target_link_libraries(splash res_path)