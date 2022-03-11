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
    || defined(__BORLANDC__) \
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

#  elif defined(BOOST_MSVC)

     // vc14.2:
#    define BOOST_LIB_TOOLSET "vc142"

#  elif defined(__BORLANDC__)

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

#elif defined(__BORLANDC__)

//
// figure out whether we want the debug builds or not:
//
#if __BORLANDC__ > 0x561
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
#         define BOOST_LIB_RT_OPT -y
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

#ifdef BOOST_AUTO_LINK_TAGGED
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT ".lib")
#  endif
#elif defined(BOOST_AUTO_LINK_SYSTEM)
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  endif
#elif defined(BOOST_AUTO_LINK_NOMANGLE)
#  pragma comment(lib, BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_STRINGIZE(BOOST_LIB_NAME) ".lib")
#  endif
#elif defined(BOOST_LIB_BUILDID)
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION "-" BOOST_STRINGIZE(BOOST_LIB_BUILDID) ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION "-" BOOST_STRINGIZE(BOOST_LIB_BUILDID) ".lib")
#  endif
#else
#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION ".lib")
#  ifdef BOOST_LIB_DIAGNOSTIC
#     pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_STRINGIZE(BOOST_LIB_NAME) "-" BOOST_LIB_TOOLSET BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_ARCH_AND_MODEL_OPT "-" BOOST_LIB_VERSION ".lib")
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



/* auto_link.hpp
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
*/