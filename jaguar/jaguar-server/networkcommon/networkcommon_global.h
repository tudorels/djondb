#ifndef NETWORKCOMMON_GLOBAL_H
#define NETWORKCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETWORKCOMMON_LIBRARY)
#  define NETWORKCOMMONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define NETWORKCOMMONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NETWORKCOMMON_GLOBAL_H