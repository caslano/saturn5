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