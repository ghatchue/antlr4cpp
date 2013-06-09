#ifndef ANTLR4_H
#define ANTLR4_H

#ifndef _MSC_VER
#    include "config.h"
#endif

#if (defined _WIN32 || defined __CYGWIN__) && !defined __GNUC__
#    if defined ANTLR4_EXPORTS
#        define ANTLR4_API __declspec(dllexport)
#    else
#        define ANTLR4_API __declspec(dllimport)
#    endif
#else
#    define ANTLR4_API
#endif

#endif /* ANTLR4_H */
