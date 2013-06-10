## Process this file with autoconf to produce configure

# General project information
AC_INIT([antlr4cpp], [1.0])
AC_PREREQ([2.59])

# check for C compiler
AC_PROG_CC

# check for C++ preprocessor and compiler and the library compiler
AC_PROG_CXXCPP
AC_PROG_CXX

# shared library support
AC_DISABLE_SHARED
AC_PROG_LIBTOOL

# automake initialisation and check for minimal automake API version 1.10
AM_INIT_AUTOMAKE([1.10 -Wall])

# use the C++ compiler for the following checks
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([inttypes.h])
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# distribute additional compiler and linker flags
# --> set these variables instead of CXXFLAGS or LDFLAGS
AC_SUBST([AM_CXXFLAGS])
AC_SUBST([AM_LDFLAGS])

# files to generate via autotools (.am or .in source files)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# conditionals indicating if building static or shared
AM_CONDITIONAL([ENABLE_STATIC], [test "$enable_static" = "yes"])
AM_CONDITIONAL([ENABLE_SHARED], [test "$enable_shared" = "yes"])

# generate the final Makefile etc.
AC_OUTPUT
