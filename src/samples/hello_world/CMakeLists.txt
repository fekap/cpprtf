include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(hello_world ${SOURCES})
target_link_libraries(hello_world cpprtf)
