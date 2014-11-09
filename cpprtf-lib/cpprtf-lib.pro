TARGET = cpprtf

DESTDIR = $$top_builddir

TEMPLATE = lib

DEFINES += CPPRTF_LIBRARY
INCLUDEPATH += "$$top_srcdir/boost/regex"
LIBS += -L"$$top_builddir/boost/regex" -lboost_regex

HEADERS += \
    global.h \
    cpprtf.h \
    container/base.h \
    container/header.h \
    container/footer.h \
    container.h \
    container/section.h \
    font.h \
    dochead/colortable.h \
    dochead/fonttable.h \
    dochead/note.h \
    endnote.h \
    footnote.h \
    parformat.h \
    tools/stringtools.h \
    border/format.h \
    unit.h \
    border.h \
    element.h \
    utf8.h \
    writer/interface.h \
    writer/string.h \
    element/plain.h \
    element/hyperlink.h \
    table/cell.h \
    table.h \
    table/nested.h \
    table/row.h \
    table/column.h \
    image.h \
    lists/enumeration.h \
    lists/numbering.h \
    formfield.h \
    formfield/checkbox.h \
    formfield/dropdown.h \
    formfield/text.h \
    paper/paper_format.h \
    tools/addon.h \
    streamoutput.h \
    container/baseelement.h \
    list.h \
    iconv.hpp

OTHER_FILES += \
    CppRtf

SOURCES += \
    cpprtf.cpp \
    container.cpp \
    container/base.cpp \
    container/section.cpp \
    container/header.cpp \
    container/footer.cpp \
    font.cpp \
    dochead/colortable.cpp \
    dochead/fonttable.cpp \
    dochead/note.cpp \
    footnote.cpp \
    endnote.cpp \
    parformat.cpp \
    tools/stringtools.cpp \
    border/format.cpp \
    unit.cpp \
    border.cpp \
    element.cpp \
    utf8.cpp \
    writer/string.cpp \
    element/plain.cpp \
    element/hyperlink.cpp \
    table.cpp \
    table/cell.cpp \
    table/nested.cpp \
    table/row.cpp \
    table/column.cpp \
    image.cpp \
    lists/numbering.cpp \
    lists/enumeration.cpp \
    formfield.cpp \
    formfield/checkbox.cpp \
    formfield/dropdown.cpp \
    formfield/text.cpp \
    paper/paper_format.cpp \
    streamoutput.cpp \
    container/baseelement.cpp \
    list.cpp
