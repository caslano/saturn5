//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2002. 
//  (C) Copyright Jens Maurer 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// locate which platform we are on and define BOOST_PLATFORM_CONFIG as needed.
// Note that we define the headers to include using "header_name" not
// <header_name> in order to prevent macro expansion within the header
// name (for example "linux" is a macro on linux systems).

#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
// linux, also other platforms (Hurd etc) that use GLIBC, should these really have their own config headers though?
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/linux.hpp"

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__)
// BSD:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/bsd.hpp"

#elif defined(sun) || defined(__sun)
// solaris:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/solaris.hpp"

#elif defined(__sgi)
// SGI Irix:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/irix.hpp"

#elif defined(__hpux)
// hp unix:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/hpux.hpp"

#elif defined(__CYGWIN__)
// cygwin is not win32:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/cygwin.hpp"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
// win32:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/win32.hpp"

#elif defined(__HAIKU__)
// Haiku
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/haiku.hpp"

#elif defined(__BEOS__)
// BeOS
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/beos.hpp"

#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
// MacOS
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/macos.hpp"

#elif defined(__TOS_MVS__)
// IBM z/OS
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/zos.hpp"

#elif defined(__IBMCPP__) || defined(_AIX)
// IBM AIX
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/aix.hpp"

#elif defined(__amigaos__)
// AmigaOS
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/amigaos.hpp"

#elif defined(__QNXNTO__)
// QNX:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/qnxnto.hpp"

#elif defined(__VXWORKS__)
// vxWorks:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/vxworks.hpp"

#elif defined(__SYMBIAN32__) 
// Symbian: 
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/symbian.hpp" 

#elif defined(_CRAYC)
// Cray:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/cray.hpp" 

#elif defined(__VMS) 
// VMS:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/vms.hpp" 

#elif defined(__CloudABI__)
// Nuxi CloudABI:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/cloudabi.hpp"

#elif defined (__wasm__)
// Web assembly:
#  define BOOST_PLATFORM_CONFIG "boost/config/platform/wasm.hpp"

#else

#  if defined(unix) \
      || defined(__unix) \
      || defined(_XOPEN_SOURCE) \
      || defined(_POSIX_SOURCE)

   // generic unix platform:

#  ifndef BOOST_HAS_UNISTD_H
#     define BOOST_HAS_UNISTD_H
#  endif

#  include <boost/config/detail/posix_features.hpp>

#  endif

#  if defined (BOOST_ASSERT_CONFIG)
      // this must come last - generate an error if we don't
      // recognise the platform:
#     error "Unknown platform - please configure and report the results to boost.org"
#  endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "boost/config/platform/linux.hpp"
#  include "boost/config/platform/bsd.hpp"
#  include "boost/config/platform/solaris.hpp"
#  include "boost/config/platform/irix.hpp"
#  include "boost/config/platform/hpux.hpp"
#  include "boost/config/platform/cygwin.hpp"
#  include "boost/config/platform/win32.hpp"
#  include "boost/config/platform/beos.hpp"
#  include "boost/config/platform/macos.hpp"
#  include "boost/config/platform/zos.hpp"
#  include "boost/config/platform/aix.hpp"
#  include "boost/config/platform/amigaos.hpp"
#  include "boost/config/platform/qnxnto.hpp"
#  include "boost/config/platform/vxworks.hpp"
#  include "boost/config/platform/symbian.hpp" 
#  include "boost/config/platform/cray.hpp" 
#  include "boost/config/platform/vms.hpp" 
#  include <boost/config/detail/posix_features.hpp>



#endif


/* select_platform_config.hpp
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
*/