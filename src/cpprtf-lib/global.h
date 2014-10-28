#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CPPRTF_LIBRARY)
#  define CPPRTFSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CPPRTFSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H
