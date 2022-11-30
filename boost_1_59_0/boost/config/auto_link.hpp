//  (C) Copyright John Maddock 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         auto_link.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Automatic library inclusion for Borland/Microsoft compilers.
  */

/*************************************************************************

USAGE:
~~~~~~

Before including this header you must define one or more of define the following macros:

BOOST_LIB_NAME:           Required: A string containing the basename of the library,
                          for example boost_regex.
BOOST_LIB_TOOLSET:        Optional: the base name of the toolset.
BOOST_DYN_LINK:           Optional: when set link to dll rather than static library.
BOOST_LIB_DIAGNOSTIC:     Optional: when set the header will print out the name
                          of the library selected (useful for debugging).
BOOST_AUTO_LINK_NOMANGLE: Specifies that we should link to BOOST_LIB_NAME.lib,
                          rather than a mangled-name version.
BOOST_AUTO_LINK_TAGGED:   Specifies that we link to libraries built with the --layout=tagged option.
                          This is essentially the same as the default name-mangled version, but without
                          the compiler name and version, or the Boost version.  Just the build options.
BOOST_AUTO_LINK_SYSTEM:   Specifies that we link to libraries built with the --layout=system option.
                          This is essentially the same as the non-name-mangled version, but with
                          the prefix to differentiate static and dll builds

These macros will be undef'ed at the end of the header, further this header
has no include guards - so be sure to include it only once from your library!

Algorithm:
~~~~~~~~~~

Libraries for Borland and Microsoft compilers are automatically
selected here, the name of the lib is selected according to the following
formula:

BOOST_LIB_PREFIX
   + BOOST_LIB_NAME
   + "_"
   + BOOST_LIB_TOOLSET
   + BOOST_LIB_THREAD_OPT
   + BOOST_LIB_RT_OPT
   + BOOST_LIB_ARCH_AND_MODEL_OPT
   "-"
   + BOOST_LIB_VERSION
   + BOOST_LIB_SUFFIX

These are defined as:

BOOST_LIB_PREFIX:     "lib" for static libraries otherwise "".

BOOST_LIB_NAME:       The base name of the lib ( for example boost_regex).

BOOST_LIB_TOOLSET:    The compiler toolset name (vc6, vc7, bcb5 etc).

BOOST_LIB_THREAD_OPT: "-mt" for multithread builds, otherwise nothing.

BOOST_LIB_RT_OPT:     A suffix that indicates the runtime library used,
                      contains one or more of the following letters after
                      a hyphen:

                      s      static runtime (dynamic if not present).
                      g      debug/diagnostic runtime (release if not present).
                      y      Python debug/diagnostic runtime (release if not present).
                      d      debug build (release if not present).
                      p      STLport build.
                      n      STLport build without its IOStreams.

BOOST_LIB_ARCH_AND_MODEL_OPT: The architecture and address model
                              (-x32 or -x64 for x86/32 and x86/64 respectively)

BOOST_LIB_VERSION:    The Boost version, in the form x_y, for Boost version x.y.

BOOST_LIB_SUFFIX:     Static/import libraries extension (".lib", ".a") for the compiler.

***************************************************************************/

#ifdef __cplusplus
#  ifndef BOOST_CONFIG_HPP
#     include <boost/config.hpp>
#  endif
#elif defined(_MSC_VER) && !defined(__MWERKS__) && !defined(__EDG_VERSION__)
//
// C language compatability (no, honestly)
//
#  define BOOST_MSVC _MSC_VER
#  define BOOST_STRINGIZE(X) BOOST_DO_STRINGIZE(X)
#  define BOOST_DO_STRINGIZE(X) #X
#endif
//
// Only include what follows for known and supported compilers:
//
#if defined(BOOST_MSVC) \
    || defined(BOOST_EMBTC_WINDOWS) \
    || defined(BOOST_BORLANDC) \
    || (defined(__MWERKS__) && defined(_WIN32) && (__MWERKS__ >= 0x3000)) \
    || (defined(__ICL) && defined(_MSC_EXTENSIONS) && (_MSC_VER >= 1200)) \
    || (defined(BOOST_CLANG) && defined(BOOST_WINDOWS) && defined(_MSC_VER) && (__clang_major__ >= 4))

#ifndef BOOST_VERSION_HPP
#  include <boost/version.hpp>
#endif

#ifndef BOOST_LIB_NAME
#  error "Macro BOOST_LIB_NAME not set (internal error)"
#endif

//
// error check:
//
#if defined(__MSVC_RUNTIME_CHECKS) && !defined(_DEBUG)
#  pragma message("Using the /RTC option without specifying a debug runtime will lead to linker errors")
#  pragma message("Hint: go to the code generation options and switch to one of the debugging runtimes")
#  error "Incompatible build options"
#endif
//
// select toolset if not defined already:
//
#ifndef BOOST_LIB_TOOLSET
#  if defined(BOOST_MSVC) && (BOOST_MSVC < 1200)
    // Note: no compilers before 1200 are supported
#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1300)

#    ifdef UNDER_CE
       // eVC4:
#      define BOOST_LIB_TOOLSET "evc4"
#    else
       // vc6:
#      define BOOST_LIB_TOOLSET "vc6"
#    endif

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1310)

     // vc7:
#    define BOOST_LIB_TOOLSET "vc7"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1400)

     // vc71:
#    define BOOST_LIB_TOOLSET "vc71"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1500)

     // vc80:
#    define BOOST_LIB_TOOLSET "vc80"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1600)

     // vc90:
#    define BOOST_LIB_TOOLSET "vc90"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1700)

     // vc10:
#    define BOOST_LIB_TOOLSET "vc100"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1800)

     // vc11:
#    define BOOST_LIB_TOOLSET "vc110"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1900)

     // vc12:
#    define BOOST_LIB_TOOLSET "vc120"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1910)

     // vc14:
#    define BOOST_LIB_TOOLSET "vc140"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1920)

     // vc14.1:
#    define BOOST_LIB_TOOLSET "vc141"

#  elif defined(BOOST_MSVC) && (BOOST_MSVC < 1930)

     // vc14.2:
#    define BOOST_LIB_TOOLSET "vc142"

#  elif defined(BOOST_MSVC)

     // vc14.3:
#    define BOOST_LIB_TOOLSET "vc143"

#  elif defined(BOOST_EMBTC_WINDOWS)

     // Embarcadero Clang based compilers:
#    define BOOST_LIB_TOOLSET "embtc"

#  elif defined(BOOST_BORLANDC)

     // CBuilder 6:
#    define BOOST_LIB_TOOLSET "bcb"

#  elif defined(__ICL)

     // Intel C++, no version number:
#    define BOOST_LIB_TOOLSET "iw"

#  elif defined(__MWERKS__) && (__MWERKS__ <= 0x31FF )

     // Metrowerks CodeWarrior 8.x
#    define BOOST_LIB_TOOLSET "cw8"

#  elif defined(__MWERKS__) && (__MWERKS__ <= 0x32FF )

     // Metrowerks CodeWarrior 9.x
#    define BOOST_LIB_TOOLSET "cw9"

#  elif defined(BOOST_CLANG) && defined(BOOST_WINDOWS) && defined(_MSC_VER) && (__clang_major__ >= 4)

     // Clang on Windows
#    define BOOST_LIB_TOOLSET "clangw" BOOST_STRINGIZE(__clang_major__)

#  endif
#endif // BOOST_LIB_TOOLSET

//
// select thread opt:
//
#if defined(_MT) || defined(__MT__)
#  define BOOST_LIB_THREAD_OPT "-mt"
#else
#  define BOOST_LIB_THREAD_OPT
#endif

#if defined(_MSC_VER) || defined(__MWERKS__)

#  ifdef _DLL

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-gydp"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-gdp"
#        elif defined(_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-gydp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gdp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-p"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-gydpn"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-gdpn"
#        elif defined(_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-gydpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gdpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-pn"
#        endif

#     else

#        if defined(_DEBUG) && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-gyd"
#        elif defined(_DEBUG)
#            define BOOST_LIB_RT_OPT "-gd"
#        else
#            define BOOST_LIB_RT_OPT
#        endif

#     endif

#  else

#     if (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)) && (defined(_STLP_OWN_IOSTREAMS) || defined(__STL_OWN_IOSTREAMS))

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-sgydp"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-sgdp"
#        elif defined(_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#             define BOOST_LIB_RT_OPT "-sgydp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgdp"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-sp"
#        endif

#     elif defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)

#        if defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#            define BOOST_LIB_RT_OPT "-sgydpn"
#        elif defined(_DEBUG) && (defined(__STL_DEBUG) || defined(_STLP_DEBUG))
#            define BOOST_LIB_RT_OPT "-sgdpn"
#        elif defined(_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#             define BOOST_LIB_RT_OPT "-sgydpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        elif defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgdpn"
#            pragma message("warning: STLport debug versions are built with /D_STLP_DEBUG=1")
#            error "Build options aren't compatible with pre-built libraries"
#        else
#            define BOOST_LIB_RT_OPT "-spn"
#        endif

#     else

#        if defined(_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#             define BOOST_LIB_RT_OPT "-sgyd"
#        elif defined(_DEBUG)
#             define BOOST_LIB_RT_OPT "-sgd"
#        else
#            define BOOST_LIB_RT_OPT "-s"
#        endif

#     endif

#  endif

#elif defined(BOOST_EMBTC_WINDOWS)

#  ifdef _RTLDLL

#     if defined(_DEBUG)
#         define BOOST_LIB_RT_OPT "-d"
#     else
#         define BOOST_LIB_RT_OPT
#     endif

#  else

#     if defined(_DEBUG)
#         define BOOST_LIB_RT_OPT "-sd"
#     else
#         define BOOST_LIB_RT_OPT "-s"
#     endif

#  endif

#elif defined(BOOST_BORLANDC)

//
// figure out whether we want the debug builds or not:
//
#if BOOST_BORLANDC > 0x561
#pragma defineonoption BOOST_BORLAND_DEBUG -v
#endif
//
// sanity check:
//
#if defined(__STL_DEBUG) || defined(_STLP_DEBUG)
#error "Pre-built versions of the Boost libraries are not provided in STLport-debug form"
#endif

#  ifdef _RTLDLL

#     if defined(BOOST_BORLAND_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#         define BOOST_LIB_RT_OPT "-yd"
#     elif defined(BOOST_BORLAND_DEBUG)
#         define BOOST_LIB_RT_OPT "-d"
#     elif defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#         define BOOST_LIB_RT_OPT "-y"
#     else
#         define BOOST_LIB_RT_OPT
#     endif

#  else

#     if defined(BOOST_BORLAND_DEBUG)\
               && defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#         define BOOST_LIB_RT_OPT "-syd"
#     elif defined(BOOST_BORLAND_DEBUG)
#         define BOOST_LIB_RT_OPT "-sd"
#     elif defined(BOOST_DEBUG_PYTHON) && defined(BOOST_LINKING_PYTHON)
#         define BOOST_LIB_RT_OPT "-sy"
#     else
#         define BOOST_LIB_RT_OPT "-s"
#     endif

#  endif

#endif

//
// BOOST_LIB_ARCH_AND_MODEL_OPT
//

#if defined( _M_IX86 )
#  define BOOST_LIB_ARCH_AND_MODEL_OPT "-x32"
#elif defined( _M_X64 )
#  define BOOST_LIB_ARCH_AND_MODEL_OPT "-x64"
#elif defined( _M_ARM )
#  define BOOST_LIB_ARCH_AND_MODEL_OPT "-a32"
#elif defined( _M_ARM64 )
#  define BOOST_LIB_ARCH_AND_MODEL_OPT "-a64"
#endif

//
// select linkage opt:
//
#if (defined(_DLL) || defined(_RTLDLL)) && defined(BOOST_DYN_LINK)
#  define BOOST_LIB_PREFIX
#elif defined(BOOST_DYN_LINK)
#  error "Mixing a dll boost library with a static runtime is a really bad idea..."
#else
#  define BOOST_LIB_PREFIX "lib"
#endif

//
// now include the lib:
//
#if defined(BOOST_LIB_NAME) \
      && defined(BOOST_LIB_PREFIX) \
      && defined(BOOST_LIB_TOOLSET) \
      && defined(BOOST_LIB_THREAD_OPT) \
      && defined(BOOST_LIB_RT_OPT) \
      && defined(BOOST_LIB_ARCH_AND_MODEL_OPT) \
      && defined(BOOST_LIB_VERSION)

#if defined(BOOST_EMBTC_WIN64)
#  define BOOST_LIB_SUFFIX ".a"
#else
#  define BOOST_LIB_SUFFIX ".lib"
#endif

#ifdef BOOST_AUTO_LINK_NOMANGLE
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_SUFFIX)
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_SUFFIX)
#  endif
#elif defined(BOOST_AUTO_LINK_TAGGED)
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT BOOST_LIB_SUFFIX)
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT BOOST_LIB_SUFFIX)
#  endif
#elif defined(BOOST_AUTO_LINK_SYSTEM)
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_SUFFIX)
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_SUFFIX)
#  endif
#elif defined(BOOST_LIB_BUILDID)
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION "-" BOOST_STRINGIZE(BOOST_LIB_BUILDID) BOOST_LIB_SUFFIX)
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION "-" BOOST_STRINGIZE(BOOST_LIB_BUILDID) BOOST_LIB_SUFFIX)
#  endif
#else
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION BOOST_LIB_SUFFIX)
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION BOOST_LIB_SUFFIX)
#  endif
#endif

#else
#  error "some required macros where not defined (internal logic error)."
#endif


#endif // _MSC_VER || __BORLANDC__

//
// finally undef any macros we may have set:
//
#ifdef BOOST_LIB_PREFIX
#  undef BOOST_LIB_PREFIX
#endif
#if defined(BOOST_LIB_NAME)
#  undef BOOST_LIB_NAME
#endif
// Don't undef this one: it can be set by the user and should be the 
// same for all libraries:
//#if defined(BOOST_LIB_TOOLSET)
//#  undef BOOST_LIB_TOOLSET
//#endif
#if defined(BOOST_LIB_THREAD_OPT)
#  undef BOOST_LIB_THREAD_OPT
#endif
#if defined(BOOST_LIB_RT_OPT)
#  undef BOOST_LIB_RT_OPT
#endif
#if defined(BOOST_LIB_ARCH_AND_MODEL_OPT)
#  undef BOOST_LIB_ARCH_AND_MODEL_OPT
#endif
#if defined(BOOST_LIB_LINK_OPT)
#  undef BOOST_LIB_LINK_OPT
#endif
#if defined(BOOST_LIB_DEBUG_OPT)
#  undef BOOST_LIB_DEBUG_OPT
#endif
#if defined(BOOST_DYN_LINK)
#  undef BOOST_DYN_LINK
#endif
#if defined(BOOST_LIB_SUFFIX)
#  undef BOOST_LIB_SUFFIX
#endif

/* auto_link.hpp
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
*/