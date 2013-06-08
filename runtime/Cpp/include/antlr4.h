#ifndef ANTLR4_H
#define ANTLR4_H

#ifndef _MSC_VER
	#include "config.h"
#endif

#ifdef ANTLR4_SHARED
    #if defined _WIN32 || defined __CYGWIN__
        #ifdef ANTLR4_EXPORTS
            #ifdef __GNUC__
                #define ANTLR4_API __attribute__((dllexport))
            #else
                #define ANTLR4_API __declspec(dllexport)
            #endif
        #else
            #ifdef __GNUC__
                #define ANTLR4_API __attribute__((dllimport))
            #else
                #define ANTLR4_API __declspec(dllimport)
            #endif
        #endif
    #else
        #if __GNUC__ >= 4
            #define ANTLR4_API __attribute__((visibility("default")))
        #else
            #define ANTLR4_API
        #endif
    #endif
#else
    #define ANTLR4_API
#endif

#endif /* ANTLR4_H */
