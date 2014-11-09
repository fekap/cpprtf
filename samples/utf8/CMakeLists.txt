include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(utf8 ${SOURCES})
target_link_libraries(utf8 cpprtf)
