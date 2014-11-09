
DEFINES += SRC_PATH=\\\"$$top_srcdir/samples/\\\"
#message("$$top_builddir/cpprtf-lib")
INCLUDEPATH += "$$top_srcdir/cpprtf-lib"
LIBS += -L"$$OUT_PWD/../../cpprtf-lib" -lcpprtf
