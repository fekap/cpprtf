include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(lists ${SOURCES})
target_link_libraries(lists cpprtf)
