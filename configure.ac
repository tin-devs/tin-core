#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([tincore], [0.1.0], [jfreegman@gmail.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

# Remember externally set CFLAGS
EXTERNAL_CFLAGS="$CFLAGS"

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_STDC
AC_PROG_CPP

# Reset externally set CFLAGS after calling AC_PROG*
CFLAGS="$EXTERNAL_CFLAGS"

# Use C language and compiler for the following checks
AC_LANG([C])

# Checks for libraries.
PKG_CHECK_MODULES([TOXCORE], [libtoxcore], [have_libtoxcore=yes], [have_libtoxcore=no])
AM_CONDITIONAL([TOXCORE], [test "$have_libtoxcore" = "yes"])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h stdint.h stdbool.h string.h unistd.h])

# Add debug support
AC_ARG_ENABLE(debug,
  AS_HELP_STRING(
    [--enable-debug],
    [enable debugging, default: no]),
    [case "${enableval}" in
      yes) debug=true ;;
      no)  debug=false ;;
      *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
    esac],
    [debug=false])
AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_COND_IF(DEBUG,
    AC_DEFINE(DEBUG, 1, [Define to 0 if this is a release build]),
    AC_DEFINE(DEBUG, 0, [Define to 1 or higher if this is a debug build]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_C_BIGENDIAN

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
