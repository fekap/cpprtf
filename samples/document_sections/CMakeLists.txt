include_directories(${TOP_SRC_DIR}/cpprtf-lib)
set(SOURCES main.cpp)
add_executable(document_sections ${SOURCES})
target_link_libraries(document_sections cpprtf)

