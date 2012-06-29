AC_INIT([onvif-apps], [1.0.0-git], [varphone@qq.com])
VERSION_MAJOR=1
VERSION_MINOR=0
VERSION_REVISION=0
VERSION_EXTRA=0
VERSION_DEV=git

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC_C99
AC_CONFIG_MACRO_DIR(m4)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
Makefile
contrib/Makefile
contrib/gsoap2/Makefile
contrib/onvif/Makefile
src/Makefile
])

LT_INIT([dlopen win32-dll shared disable-static])
LT_LANG([C++])
LT_LANG([Windows Resource])

dnl
dnl  Check the operating system
dnl
HAVE_WIN64="0"
case "${host_os}" in
  "")
    SYS=unknown
    ;;
  linux*)
    SYS=linux
    ;;
  *mingw32* | *cygwin* | *wince* | *mingwce*)
    AC_CHECK_TOOL(WINDRES, windres, :)
    AC_CHECK_TOOL(OBJCOPY, objcopy, :)
    AC_DEFINE([_WIN32_WINNT], 0x0502, [Define to '0x0502' for Windows XP SP2 APIs.])
    AC_DEFINE([_WIN32_IE], 0x0600, [Define to '0x0600' for IE 6.0 (and shell) APIs.])

    case "${host_os}" in
      *wince* | *mingwce* | *mingw32ce*)
        SYS=mingwce
        dnl Sadly CeGCC still needs non-wince macros
        ;;
      *mingw32*)
        SYS=mingw32
        ;;
      *cygwin*)
        dnl Check if we are using the mno-cygwin mode in which case we are
        dnl actually dealing with a mingw32 compiler.
        AC_EGREP_CPP(yes,
            [#ifdef WIN32
             yes
             #endif],
            SYS=mingw32, AC_MSG_ERROR([ONVIF-APPS requires -mno-cygwin]))
        ;;
    esac

    if test "${SYS}" = "mingw32"; then
        dnl ONVIF-APPS_ADD_LIBS([libonvifcore],[-lws2_32])
        dnl ONVIF-APPS_ADD_LDFLAGS([],[-mwindows])

        dnl
        dnl NSIS Installer prefix and WIN64
        dnl
        case "${host}" in
            amd64*|x86_64*)
                HAVE_WIN64="1"
                PROGRAMFILES="PROGRAMFILES64"
            ;;
            *)
                PROGRAMFILES="PROGRAMFILES"
            ;;
        esac
        AC_SUBST(PROGRAMFILES)

    fi
    ;;
  *)
    SYS="${host_os}"
    ;;
esac
AM_CONDITIONAL(HAVE_LINUX,   test "${SYS}" = "linux")
AM_CONDITIONAL(HAVE_WIN32,   test "${SYS}" = "mingw32")
AM_CONDITIONAL(HAVE_WIN64,   test "${HAVE_WIN64}" = "1")
AM_CONDITIONAL(HAVE_WINCE,   test "${SYS}" = "mingwce")

dnl
dnl  Check for the contrib directory
dnl
AC_ARG_WITH(contrib,
  [AS_HELP_STRING([--with-contrib[=DIR]],
    [search for 3rd party libraries in DIR/include and DIR/lib])
])
AC_MSG_CHECKING([for 3rd party libraries path])
AS_IF([test -z "${with_contrib}" || test "${with_contrib}" = "yes"], [
  CONTRIB_DIR="${srcdir}/contrib/${host}"
  AS_IF([test ! -d "${CONTRIB_DIR}"], [
    echo "${CONTRIB_DIR} not found" >&AS_MESSAGE_LOG_FD
    CONTRIB_DIR="${srcdir}/contrib/`$CC -dumpmachine`"
    AS_IF([test ! -d "${CONTRIB_DIR}"], [
      echo "${CONTRIB_DIR} not found" >&AS_MESSAGE_LOG_FD
      CONTRIB_DIR=""
      AC_MSG_RESULT([not found])
    ])
  ])
], [
  AS_IF([test "${with_contrib}" != "no"], [
    CONTRIB_DIR="${with_contrib}"
  ], [
    CONTRIB_DIR=""
    AC_MSG_RESULT([disabled])
  ])
])
AS_IF([test -n "${CONTRIB_DIR}"], [
  AS_IF([test -d "${CONTRIB_DIR}/lib"],[
    CONTRIB_DIR=`cd "${CONTRIB_DIR}" && pwd`
  ], [
    echo "${CONTRIB_DIR}/lib not found" >&AS_MESSAGE_LOG_FD
    CONTRIB_DIR=""
    AC_MSG_RESULT([not usable])
  ])
])
AS_IF([test -n "${CONTRIB_DIR}"], [
  AC_MSG_RESULT([${CONTRIB_DIR}])
  export PATH=${CONTRIB_DIR}/bin:$PATH
  CPPFLAGS="${CPPFLAGS} -I${CONTRIB_DIR}/include"
  CFLAGS="${CFLAGS} -I${CONTRIB_DIR}/include"
  CXXFLAGS="${CXXFLAGS} -I${CONTRIB_DIR}/include"
  OBJCFLAGS="${OBJCFLAGS} -I${CONTRIB_DIR}/include"
  AS_IF([test "$build" = "$host" -o "$PKG_CONFIG_LIBDIR"], [
    export PKG_CONFIG_PATH="${CONTRIB_DIR}/lib/pkgconfig:$PKG_CONFIG_PATH"
  ], [
    export PKG_CONFIG_LIBDIR="${CONTRIB_DIR}/lib/pkgconfig"
  ])
  LDFLAGS="${LDFLAGS} -L${CONTRIB_DIR}/lib"
], [
  AS_IF([test -n "${with_contrib}" && test "${with_contrib}" != "no"], [
    AC_MSG_ERROR([Third party libraries not found!])
  ])
])
AC_SUBST(CONTRIB_DIR)

dnl
dnl Sadly autoconf does not think about testing foo.exe when ask to test
dnl for program foo on win32

case "${build_os}" in
    cygwin|msys)
        ac_executable_extensions=".exe"
    ;;
    *)
    ;;
esac

AM_CONDITIONAL(HAVE_LINUX,   test "${SYS}" = "linux")
AM_CONDITIONAL(HAVE_WIN32,   test "${SYS}" = "mingw32")
AM_CONDITIONAL(HAVE_WIN64,   test "${HAVE_WIN64}" = "1")
AM_CONDITIONAL(HAVE_WINCE,   test "${SYS}" = "mingwce")

AC_ARG_ENABLE(ns-onvif1,
  [  --enable-ns-onvif1        Namespace onvif1 support (default enabled)])

AC_ARG_ENABLE(ns-wsa,
  [  --enable-ns-wsa           Namespace wsa support (default enabled)])

AC_OUTPUT

