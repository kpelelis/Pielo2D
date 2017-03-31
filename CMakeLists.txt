cmake_minimum_required(VERSION 2.8.12)

project(Pielo2D)

if (NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ext/sfml/src)
    message(FATAL_ERROR
        "Seems like some of the required dependencies are missing. "
        "This can happen if you did not clone the project with the --recursive flag. "
        "It is possible to recover by calling \"git submodule update --init --recursive\""
    )
endif()

include(CheckCXXCompilerFlag)

# add_definitions(-DUSE_DEBUG)

add_subdirectory("${PROJECT_SOURCE_DIR}/ext/sfml")

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif (HAS_CPP11_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
        message(FATAL_ERROR "Unsupported compiler. At least C++11 support is required.")
    endif()

	if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
endif()


file(GLOB_RECURSE Pielo2D_FILES
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/ext/lua/*.c"
    "${PROJECT_SOURCE_DIR}/ext/pugixml/*.cpp"
)

add_executable(Pielo2D ${Pielo2D_FILES})

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lpthread -ldl")
target_link_libraries(Pielo2D sfml-system sfml-window sfml-graphics)

target_include_directories(Pielo2D PRIVATE 
    "${PROJECT_SOURCE_DIR}/ext/sfml/include"
    "${PROJECT_SOURCE_DIR}/ext/pugixml"
    "${PROJECT_SOURCE_DIR}/ext"
    "${PROJECT_SOURCE_DIR}/include"
)
