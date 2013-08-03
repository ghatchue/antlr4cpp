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
AM_CXXFLAGS = -Wall -Wextra -I$(srcdir)/include @AM_CXXFLAGS@ @PTHREAD_CFLAGS@
AM_LDFLAGS  = @PTHREAD_LIBS@ @AM_LDFLAGS@
dist_noinst_SCRIPTS = autogen.sh
test: check ;
TESTS =
check_PROGRAMS =

antlr4cpp_headers = \
    include/antlr4.h \
    include/antlr/ANTLRErrorListener.h \
    include/antlr/ANTLRErrorStrategy.h \
    include/antlr/ANTLRFileStream.h \
    include/antlr/ANTLRInputStream.h \
    include/antlr/BailErrorStrategy.h \
    include/antlr/BaseErrorListener.h \
    include/antlr/BufferedTokenStream.h \
    include/antlr/CharStream.h \
    include/antlr/CommonToken.h \
    include/antlr/CommonTokenFactory.h \
    include/antlr/CommonTokenStream.h \
    include/antlr/ConsoleErrorListener.h \
    include/antlr/DefaultErrorStrategy.h \
    include/antlr/Definitions.h \
    include/antlr/DiagnosticErrorListener.h \
    include/antlr/FailedPredicateException.h \
    include/antlr/InputMismatchException.h \
    include/antlr/IntStream.h \
    include/antlr/Lexer.h \
    include/antlr/LexerNoViableAltException.h \
    include/antlr/NoViableAltException.h \
    include/antlr/Parser.h \
    include/antlr/ParserRuleContext.h \
    include/antlr/ProxyErrorListener.h \
    include/antlr/RecognitionException.h \
    include/antlr/Recognizer.h \
    include/antlr/RuleContext.h \
    include/antlr/Token.h \
    include/antlr/TokenFactory.h \
    include/antlr/TokenSource.h \
    include/antlr/TokenStream.h \
    include/antlr/TokenStreamRewriter.h \
    include/antlr/UnbufferedCharStream.h \
    include/antlr/UnbufferedTokenStream.h \
    include/antlr/WritableToken.h \
    include/antlr/atn/ATN.h \
    include/antlr/atn/ATNConfig.h \
    include/antlr/atn/ATNConfigSet.h \
    include/antlr/atn/ATNSimulator.h \
    include/antlr/atn/ATNState.h \
    include/antlr/atn/ATNType.h \
    include/antlr/atn/ActionTransition.h \
    include/antlr/atn/ArrayPredictionContext.h \
    include/antlr/atn/AtomTransition.h \
    include/antlr/atn/BasicBlockStartState.h \
    include/antlr/atn/BasicState.h \
    include/antlr/atn/BlockEndState.h \
    include/antlr/atn/BlockStartState.h \
    include/antlr/atn/DecisionState.h \
    include/antlr/atn/EmptyPredictionContext.h \
    include/antlr/atn/EpsilonTransition.h \
    include/antlr/atn/LL1Analyzer.h \
    include/antlr/atn/LexerATNConfig.h \
    include/antlr/atn/LexerATNSimulator.h \
    include/antlr/atn/LoopEndState.h \
    include/antlr/atn/NotSetTransition.h \
    include/antlr/atn/OrderedATNConfigSet.h \
    include/antlr/atn/ParserATNSimulator.h \
    include/antlr/atn/PlusBlockStartState.h \
    include/antlr/atn/PlusLoopbackState.h \
    include/antlr/atn/PredicateTransition.h \
    include/antlr/atn/PredictionContext.h \
    include/antlr/atn/PredictionContextCache.h \
    include/antlr/atn/PredictionMode.h \
    include/antlr/atn/RangeTransition.h \
    include/antlr/atn/RuleStartState.h \
    include/antlr/atn/RuleStopState.h \
    include/antlr/atn/RuleTransition.h \
    include/antlr/atn/SemanticContext.h \
    include/antlr/atn/SetTransition.h \
    include/antlr/atn/SingletonPredictionContext.h \
    include/antlr/atn/StarBlockStartState.h \
    include/antlr/atn/StarLoopEntryState.h \
    include/antlr/atn/StarLoopbackState.h \
    include/antlr/atn/TokensStartState.h \
    include/antlr/atn/Transition.h \
    include/antlr/atn/WildcardTransition.h \
    include/antlr/dfa/DFA.h \
    include/antlr/dfa/DFASerializer.h \
    include/antlr/dfa/DFAState.h \
    include/antlr/dfa/LexerDFASerializer.h \
    include/antlr/misc/AbstractEqualityComparator.h \
    include/antlr/misc/Array2DHashSet.h \
    include/antlr/misc/DoubleKeyMap.h \
    include/antlr/misc/EqualityComparator.h \
    include/antlr/misc/FlexibleHashMap.h \
    include/antlr/misc/HashMap.h \
    include/antlr/misc/HashKeyHelper.h \
    include/antlr/misc/HashSet.h \
    include/antlr/misc/IntegerList.h \
    include/antlr/misc/IntegerStack.h \
    include/antlr/misc/Interval.h \
    include/antlr/misc/IntervalSet.h \
    include/antlr/misc/IntSet.h \
    include/antlr/misc/Key.h \
    include/antlr/misc/KeyPtr.h \
    include/antlr/misc/MultiMap.h \
    include/antlr/misc/MurmurHash.h \
    include/antlr/misc/Mutex.h \
    include/antlr/misc/MutexLock.h \
    include/antlr/misc/ObjectEqualityComparator.h \
    include/antlr/misc/OrderedHashSet.h \
    include/antlr/misc/Pair.h \
    include/antlr/misc/ParseCancellationException.h \
    include/antlr/misc/RuntimeException.h \
    include/antlr/misc/StdHashMap.h \
    include/antlr/misc/StdHashSet.h \
    include/antlr/misc/Traits.h \
    include/antlr/misc/Thread.h \
    include/antlr/misc/Triple.h \
    include/antlr/misc/Utils.h

antlr4cpp_sources = \
    $(antlr4cpp_headers) \
    src/ANTLRErrorListener.cpp \
    src/ANTLRErrorStrategy.cpp \
    src/ANTLRFileStream.cpp \
    src/ANTLRInputStream.cpp \
    src/BailErrorStrategy.cpp \
    src/BaseErrorListener.cpp \
    src/BufferedTokenStream.cpp \
    src/CharStream.cpp \
    src/CommonToken.cpp \
    src/CommonTokenFactory.cpp \
    src/CommonTokenStream.cpp \
    src/ConsoleErrorListener.cpp \
    src/DefaultErrorStrategy.cpp \
    src/DiagnosticErrorListener.cpp \
    src/FailedPredicateException.cpp \
    src/InputMismatchException.cpp \
    src/IntStream.cpp \
    src/Lexer.cpp \
    src/LexerNoViableAltException.cpp \
    src/NoViableAltException.cpp \
    src/Parser.cpp \
    src/ParserRuleContext.cpp \
    src/ProxyErrorListener.cpp \
    src/RecognitionException.cpp \
    src/RuleContext.cpp \
    src/Token.cpp \
    src/TokenFactory.cpp \
    src/TokenSource.cpp \
    src/TokenStream.cpp \
    src/TokenStreamRewriter.cpp \
    src/UnbufferedCharStream.cpp \
    src/UnbufferedTokenStream.cpp \
    src/WritableToken.cpp \
    src/atn/ATN.cpp \
    src/atn/ATNConfig.cpp \
    src/atn/ATNConfigSet.cpp \
    src/atn/ATNSimulator.cpp \
    src/atn/ATNState.cpp \
    src/atn/ATNType.cpp \
    src/atn/ActionTransition.cpp \
    src/atn/ArrayPredictionContext.cpp \
    src/atn/AtomTransition.cpp \
    src/atn/BasicBlockStartState.cpp \
    src/atn/BasicState.cpp \
    src/atn/BlockEndState.cpp \
    src/atn/BlockStartState.cpp \
    src/atn/DecisionState.cpp \
    src/atn/EmptyPredictionContext.cpp \
    src/atn/EpsilonTransition.cpp \
    src/atn/LL1Analyzer.cpp \
    src/atn/LexerATNConfig.cpp \
    src/atn/LexerATNSimulator.cpp \
    src/atn/LoopEndState.cpp \
    src/atn/NotSetTransition.cpp \
    src/atn/OrderedATNConfigSet.cpp \
    src/atn/ParserATNSimulator.cpp \
    src/atn/PlusBlockStartState.cpp \
    src/atn/PlusLoopbackState.cpp \
    src/atn/PredicateTransition.cpp \
    src/atn/PredictionContext.cpp \
    src/atn/PredictionContextCache.cpp \
    src/atn/PredictionMode.cpp \
    src/atn/RangeTransition.cpp \
    src/atn/RuleStartState.cpp \
    src/atn/RuleStopState.cpp \
    src/atn/RuleTransition.cpp \
    src/atn/SemanticContext.cpp \
    src/atn/SetTransition.cpp \
    src/atn/SingletonPredictionContext.cpp \
    src/atn/StarBlockStartState.cpp \
    src/atn/StarLoopEntryState.cpp \
    src/atn/StarLoopbackState.cpp \
    src/atn/TokensStartState.cpp \
    src/atn/Transition.cpp \
    src/atn/WildcardTransition.cpp \
    src/dfa/DFA.cpp \
    src/dfa/DFASerializer.cpp \
    src/dfa/DFAState.cpp \
    src/dfa/LexerDFASerializer.cpp \
    src/misc/IntegerList.cpp \
    src/misc/IntegerStack.cpp \
    src/misc/IntervalSet.cpp \
    src/misc/Interval.cpp \
    src/misc/IntSet.cpp \
    src/misc/MurmurHash.cpp \
    src/misc/Mutex.cpp \
    src/misc/MutexLock.cpp \
    src/misc/ParseCancellationException.cpp \
    src/misc/RuntimeException.cpp \
    src/misc/Thread.cpp \
    src/misc/Utils.cpp

antlr4cpp_unit_test_sources = \
    test/gmock/gmock.h \
    test/gtest/gtest.h \
    test/gmock-gtest-all.cc \
    test/gmock_main.cc \
    test/BaseTest.h \
    test/BaseTest.cpp \
    test/misc/HashRangeKey.h \
    test/misc/IntKey.h \
    test/misc/StringKey.h \
    test/misc/TestArray2DHashSet.cpp \
    test/misc/TestDoubleKeyMap.cpp \
    test/misc/TestFlexibleHashMap.cpp \
    test/misc/TestHashMap.cpp \
    test/misc/TestHashSet.cpp \
    test/misc/TestIntegerList.cpp \
    test/misc/TestIntegerStack.cpp \
    test/misc/TestIntervalSet.cpp \
    test/misc/TestKeyPtr.cpp \
    test/misc/TestMultiMap.cpp \
    test/misc/TestOrderedHashSet.cpp \
    test/misc/TestPair.cpp \
    test/misc/TestTriple.cpp \
    test/misc/TestUtils.cpp \
    test/misc/ZeroKey.h



## Main library: libantlr4cpp
lib_LTLIBRARIES = lib/libantlr4cpp.la
lib_antlr4cpp_la_CXXFLAGS = $(AM_CXXFLAGS)
lib_libantlr4cpp_ladir = $(includedir)
lib_libantlr4cpp_la_HEADERS = $(antlr4cpp_headers)
lib_libantlr4cpp_la_SOURCES = $(antlr4cpp_sources)


## Unit tests
GTEST_CXXFLAGS =
if HAVE_PTHREAD
    GTEST_CXXFLAGS += -DGTEST_HAS_PTHREAD
endif
if ENABLE_STATIC
    TESTS += test/antlr4cpp_test
    check_PROGRAMS += test/antlr4cpp_test
    test_antlr4cpp_test_SOURCES = $(antlr4cpp_unit_test_sources)
    test_antlr4cpp_test_LDADD = lib/libantlr4cpp.la
    test_antlr4cpp_test_LDFLAGS = $(AM_LDFLAGS) -static
    test_antlr4cpp_test_CXXFLAGS = $(AM_CXXFLAGS) $(GTEST_CXXFLAGS) -I"$(srcdir)/test"
endif
if ENABLE_SHARED    
    TESTS += test/antlr4cpp_test_shared
    check_PROGRAMS += test/antlr4cpp_test_shared
    test_antlr4cpp_test_shared_SOURCES = $(antlr4cpp_unit_test_sources)
    test_antlr4cpp_test_shared_LDADD = lib/libantlr4cpp.la
    test_antlr4cpp_test_shared_LDFLAGS = $(AM_LDFLAGS)
    test_antlr4cpp_test_shared_CXXFLAGS = $(AM_CXXFLAGS) $(GTEST_CXXFLAGS) -I"$(srcdir)/test"
endif
