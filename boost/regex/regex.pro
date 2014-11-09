TARGET = boost-regex

DESTDIR = $$top_builddir/boost/regex

TEMPLATE = lib

SOURCES += \
    cpp_regex_traits.cpp \
    c_regex_traits.cpp \
    cregex.cpp \
    fileiter.cpp \
    instances.cpp \
    regex.cpp \
    regex_raw_buffer.cpp \
    regex_traits_defaults.cpp \
    static_mutex.cpp \
    w32_regex_traits.cpp \
