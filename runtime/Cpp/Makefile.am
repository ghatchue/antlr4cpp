## Process this file with automake to produce Makefile.in

# keep object files in their sudirs
AUTOMAKE_OPTIONS = subdir-objects

# additional distclean files
DISTCLEANFILES = config.sub depcomp missing aclocal.m4 \
                    config.guess configure install-sh \
                    Makefile.in* config.h.in* ltmain.sh \
                    INSTALL

distclean-local:
	-rm -rf autom4te.cache lib test/.libs

# additional compiler options
AM_CXXFLAGS = -Wall -Wextra -DANTLR4_SHARED -DANTLR4_EXPORTS -I$(srcdir)/include @AM_CXXFLAGS@

## The main antlr4cpp library
lib_LTLIBRARIES = lib/libantlr4cpp.la

# where to install the headers on the system
lib_libantlr4cpp_ladir = $(includedir)

# the list of header files that belong to the library (to be installed later)
lib_libantlr4cpp_la_HEADERS = \
    include/Test.h

# the sources to add to the library and to add to the source distribution
lib_libantlr4cpp_la_SOURCES = \
    $(libantlr4cpp_a_HEADERS) \
    src/Test.cpp

## The main unit tests
TESTS =
check_PROGRAMS =

TESTS += test/antlr4cpp_test
check_PROGRAMS += test/antlr4cpp_test
test_antlr4cpp_test_SOURCES = \
    test/gmock/gmock.h \
    test/gtest/gtest.h \
    test/gmock-gtest-all.cc \
    test/gmock_main.cc \
    tests/TestTests.cpp
test_antlr4cpp_test_LDADD =
test_antlr4cpp_test_CPPFLAGS = -I"$(srcdir)/test"


## Utility rules, documentation, etc.

# A compatibility line, the old build system worked with 'make test'
test: check ;

dist_noinst_SCRIPTS = autogen.sh


## end Makefile.am
