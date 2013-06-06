#ifndef ANTLR4_H
#define ANTLR4_H

#include "config.h"

#ifdef ANTLR4_STATIC
    #define ANTLR4_API
#else
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
#endif

#endif /* ANTLR4_H */
