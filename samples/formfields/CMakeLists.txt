include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(formfields ${SOURCES})
target_link_libraries(formfields cpprtf)
