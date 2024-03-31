cmake_minimum_required(VERSION 3.10)
project(PwGencc)

find_package(Boost REQUIRED COMPONENTS random program_options)

include_directories(${Boost_INCLUDE_DIRS})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(pwgencc main.cc pwgencc.cc)
target_link_libraries(pwgencc ${Boost_LIBRARIES})
