include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(footnotes ${SOURCES})
target_link_libraries(footnotes cpprtf)
