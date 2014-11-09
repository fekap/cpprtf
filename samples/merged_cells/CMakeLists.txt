include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(merged_cells ${SOURCES})
target_link_libraries(merged_cells cpprtf)
