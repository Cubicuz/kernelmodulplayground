project(something)



add_executable(something main.cpp)
target_link_libraries(something nl-3 nl-genl-3)
target_include_directories(something PRIVATE /usr/include/libnl3/)