## Process this file with automake to produce Makefile.in

# Cleanup
DISTCLEANFILES = config.sub depcomp missing aclocal.m4 \
                    config.guess configure install-sh \
                    Makefile.in* config.h.in* ltmain.sh \
                    INSTALL
distclean-local:
	-rm -rf autom4te.cache lib test/.libs

## General options
AUTOMAKE_OPTIONS = subdir-objects
AM_CXXFLAGS = -Wall -Wextra -I$(srcdir)/include @AM_CXXFLAGS@
dist_noinst_SCRIPTS = autogen.sh
test: check ;
TESTS =
check_PROGRAMS =

antlr4cpp_headers = \
    include/antlr4.h \
    include/Antlr4Definitions.h \
    include/misc/IntSet.h \
    include/misc/Utils.h \
    include/Test.h

antlr4cpp_sources = \
    $(antlr4cpp_headers) \
    src/Test.cpp

antlr4cpp_unit_test_sources = \
    test/gmock/gmock.h \
    test/gtest/gtest.h \
    test/gmock-gtest-all.cc \
    test/gmock_main.cc \
    test/TestTests.cpp


## Main library: libantlr4cpp
lib_LTLIBRARIES = lib/libantlr4cpp.la
lib_antlr4cpp_la_CXXFLAGS = $(AM_CXXFLAGS)
lib_libantlr4cpp_ladir = $(includedir)
lib_libantlr4cpp_la_HEADERS = $(antlr4cpp_headers)
lib_libantlr4cpp_la_SOURCES = $(antlr4cpp_sources)


## Unit tests
if ENABLE_STATIC
    TESTS += test/antlr4cpp_test
    check_PROGRAMS += test/antlr4cpp_test
    test_antlr4cpp_test_SOURCES = $(antlr4cpp_unit_test_sources)
    test_antlr4cpp_test_LDADD = lib/libantlr4cpp.la
    test_antlr4cpp_test_LDFLAGS = -static
    test_antlr4cpp_test_CXXFLAGS = $(AM_CXXFLAGS) -I"$(srcdir)/test"
endif
if ENABLE_SHARED    
    TESTS += test/antlr4cpp_test_shared
    check_PROGRAMS += test/antlr4cpp_test_shared
    test_antlr4cpp_test_shared_SOURCES = $(antlr4cpp_unit_test_sources)
    test_antlr4cpp_test_shared_LDADD = lib/libantlr4cpp.la
    test_antlr4cpp_test_shared_CXXFLAGS = $(AM_CXXFLAGS) -I"$(srcdir)/test"
endif
