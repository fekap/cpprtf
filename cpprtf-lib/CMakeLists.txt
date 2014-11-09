project(cpprtf)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(HEADERS
    cpprtf.h 
    container/base.h 
    container/header.h 
    container/footer.h 
    container.h 
    container/section.h 
    font.h 
    dochead/colortable.h 
    dochead/fonttable.h 
    dochead/note.h 
    endnote.h 
    footnote.h 
    parformat.h 
    tools/stringtools.h 
    border/format.h 
    unit.h 
    border.h 
    element.h 
    utf8.h 
    writer/interface.h 
    writer/string.h 
    element/plain.h 
    element/hyperlink.h 
    table/cell.h 
    table.h 
    table/nested.h 
    table/row.h 
    table/column.h 
    image.h 
    lists/enumeration.h 
    lists/numbering.h 
    formfield.h 
    formfield/checkbox.h 
    formfield/dropdown.h 
    formfield/text.h 
    paper/paper_format.h 
    tools/addon.h 
    streamoutput.h 
    container/baseelement.h 
    list.h
    CppRtf)

 set(SOURCES cpprtf.cpp 
    container.cpp 
    container/base.cpp 
    container/section.cpp 
    container/header.cpp 
    container/footer.cpp 
    font.cpp 
    dochead/colortable.cpp 
    dochead/fonttable.cpp 
    dochead/note.cpp 
    footnote.cpp 
    endnote.cpp 
    parformat.cpp 
    tools/stringtools.cpp 
    border/format.cpp 
    unit.cpp 
    border.cpp 
    element.cpp 
    utf8.cpp 
    writer/string.cpp 
    element/plain.cpp 
    element/hyperlink.cpp 
    table.cpp 
    table/cell.cpp 
    table/nested.cpp 
    table/row.cpp 
    table/column.cpp 
    image.cpp 
    lists/numbering.cpp 
    lists/enumeration.cpp 
    formfield.cpp 
    formfield/checkbox.cpp 
    formfield/dropdown.cpp 
    formfield/text.cpp 
    paper/paper_format.cpp 
    streamoutput.cpp 
    container/baseelement.cpp 
    list.cpp)

INCLUDE_DIRECTORIES(../../boost)
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} boost_regex)
#set_target_properties(${PROJECT_NAME} PROPERTIES
#        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../bin")
