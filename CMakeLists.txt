cmake_minimum_required(VERSION 3.12)
project(tiny_printf)
set(CMAKE_CXX_STANDARD 17)
set(SRC_FOLDER src)


file(GLOB_RECURSE SRC_CXX_FILES CMAKE_CONFIGURE_DEPENDS ${SRC_FOLDER}/*.cpp)
file(GLOB_RECURSE SRC_C_FILES CMAKE_CONFIGURE_DEPENDS ${SRC_FOLDER}/*.c)
add_subdirectory(googletest)
add_executable(${PROJECT_NAME} ${SRC_CXX_FILES} ${SRC_C_FILES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)


#set(GCC_X_COVERAGE_COMPILE_FLAGS "-Werror -Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wstrict-prototypes -Wundef -Wold-style-definition -Wno-misleading-indentation")
set(GCC_X_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wstrict-prototypes -Wundef -Wold-style-definition -Wno-misleading-indentation -Os")
#set(GCC_CXX_COVERAGE_COMPILE_FLAGS "-Werror -Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wundef -Wno-misleading-indentation")
set(GCC_CXX_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wpointer-arith -Wcast-align -Wwrite-strings -Wswitch-default -Wunreachable-code -Winit-self -Wmissing-field-initializers -Wno-unknown-pragmas -Wundef -Wno-misleading-indentation -Os")
set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS} ${GCC_X_COVERAGE_COMPILE_FLAGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${GCC_CXX_COVERAGE_COMPILE_FLAGS})