cmake_minimum_required(VERSION 3.10.0)
project(lab2 VERSION 0.1.0 LANGUAGES C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if (MSVC)
    add_compile_options(/W3)
    add_compile_options(/std:c++23preview)
    add_compile_options(/EHsc)
    add_compile_options(/utf-8)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
    # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Od /DNDEBUG")
else()
    add_compile_options(-Wall)
    add_compile_options(-std=c++23)
    add_compile_options(-fexceptions)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O0 -DNDEBUG")
endif()


add_executable(lab2
    main.cpp 
    Benchmark.cpp
    DatasetManager.cpp
    Operations.cpp
)

