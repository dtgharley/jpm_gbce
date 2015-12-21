#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([jpm-GBCE], [0.0.0.1], [dth.tss@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([src/rsStocks.cpp])
AC_CONFIG_SRCDIR([test/src/codePriceTest.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile test/src/Makefile])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([boost/format.hpp], [], [AC_MSG_ERROR(You need the Boost string format libraries.)])
AC_CHECK_HEADERS([boost/algorithm/string.hpp], [], [AC_MSG_ERROR(You need the Boost string algorithm libraries.)])
AC_CHECK_HEADERS([boost/regex.hpp], [], [AC_MSG_ERROR(You need the Boost regex libraries.)])
AC_CHECK_HEADERS([boost/test/unit_test.hpp], [], [AC_MSG_ERROR(You need the Boost unit test libraries.)])
AC_LANG_POP([C++])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_LANG_PUSH([C++])
AC_TYPE_SIZE_T
AC_LANG_POP([C++])

# Checks for library functions.
AC_LANG_PUSH([C++])
AC_CHECK_FUNCS([pow])
AC_LANG_POP([C++])

AC_OUTPUT
