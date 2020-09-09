AC_INIT([lightdm-exec-greeter], [0.1], [jbraun@rangee.com])
AC_CONFIG_SRCDIR([src/main.c])
AM_INIT_AUTOMAKE([subdir-objects])
AC_PROG_CC
PKG_CHECK_MODULES(LIGHTDM, liblightdm-gobject-1 >= 1.26)
PKG_CHECK_MODULES(GLIB, gobject-2.0 >= 2.56.4)
AC_CONFIG_FILES([Makefile])
AC_OUTPUT