#!/bin/sh

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
autoreconf -fvi "$srcdir" &&
    (test -n "$NOCONFIGURE" || "$srcdir/configure" "$@")
