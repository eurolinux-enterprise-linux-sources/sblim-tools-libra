#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(SBLIM Common Ressource Access Layer for WBEM-SMT tasks, 1.0, sblim-devel@lists.sourceforge.net, sblim-tools-libra)
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

AC_CANONICAL_HOST
case $host_cpu in
     i*86) HW=INTEL;; 
     s390*) HW=S390;; 
     ppc*) HW=PPC;; 
     x86_64) HW=X86_64;; 
     ia64) HW=IA64;; 
     **) HW=GENERIC;;
esac


# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LIBTOOL


# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([stdlib.h string.h strings.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_REALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([memmove strchr strdup strpbrk])

AC_CONFIG_FILES([Makefile sblim-tools-libra.spec])

AC_OUTPUT

# Display configuration options
echo
echo "-------------------------------------------------------"
echo "Configuration for $PACKAGE complete."
echo ""
echo "The following configuration options have been selected:"
echo "CPPFLAGS:" $CPPFLAGS
echo "-------------------------------------------------------"
echo
echo "You may now run make"
echo
