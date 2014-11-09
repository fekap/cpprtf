include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(chess_tournament ${SOURCES})
target_link_libraries(chess_tournament cpprtf)
