## Process this file with automake to produce Makefile.in

# Cleanup
DISTCLEANFILES = config.sub depcomp missing aclocal.m4 \
                    config.guess configure install-sh \
                    Makefile.in* config.h.in* ltmain.sh \
                    INSTALL

DISTCLEANFILES += m4/libtool.m4 m4/ltoptions.m4 m4/ltsugar.m4 \
                      m4/ltversion.m4 m4/lt~obsolete.m4

distclean-local:
	-rm -rf autom4te.cache lib test/.libs

## General options
ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects
AM_CXXFLAGS = -Wall -Wextra -I$(srcdir)/include @AM_CXXFLAGS@
dist_noinst_SCRIPTS = autogen.sh
test: check ;
TESTS =
check_PROGRAMS =

antlr4cpp_headers = \
    include/antlr4.h \
    include/Antlr4Definitions.h \
    include/IntStream.h \
    include/Lexer.h \
    include/Token.h \
    include/misc/Interval.h \
    include/misc/IntervalSet.h \
    include/misc/IntSet.h \
    include/misc/MurmurHash.h \
    include/misc/Pair.h \
    include/misc/Utils.h

antlr4cpp_sources = \
    $(antlr4cpp_headers) \
    src/IntStream.cpp \
    src/Lexer.cpp \
    src/Token.cpp \
    src/misc/IntervalSet.cpp \
    src/misc/Interval.cpp \
    src/misc/IntSet.cpp \
    src/misc/MurmurHash.cpp \
    src/misc/Utils.cpp

antlr4cpp_unit_test_sources = \
    test/gmock/gmock.h \
    test/gtest/gtest.h \
    test/gmock-gtest-all.cc \
    test/gmock_main.cc \
    test/BaseTest.h \
    test/BaseTest.cpp \
    test/TestIntervalSet.cpp \
    test/TestPair.cpp


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
