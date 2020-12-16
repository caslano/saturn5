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
yjTwVlit0lQ/vD/rWhvvO0H4954r7uR3Hp6jt7QIf6smzSeW2u7NNHCZWl2WKhc4JL+Gy6UPY9Kl9w7ykxA9dgk/H2rWPh9UEP9u5C4fFWHdy3lGp7sP/crdh2fT3YdhW5PW7FTJxt5+UItR5VEAeYgYMyH41z7+Ij7DLNHLfK16uq3ZehHfm8g08JyoRjm0j6Hbtcv4OWoY49X+eFo3AyH1JB8/OmxA23h5jIzC//Hk6EjjlidKEapetNq1r3K9wId9Wh8f5u29lO7hH9OaKId0smH3QKgAqx3WBnGjeEy1KK7UP/ijy/llB/0QX6NttDdTBo0bMakA675Fp117nO/rxfBubc/8tQa6mM5OTzVTD/KN7w9UhOx39Cy79k4uhxeib6LvWz8w0EX6w3ydehjwac2SQ6mBy1RLCSSDy+zabD4m4Buob//dD3kshk79IPfUvHcO/NYEGWTgTzyRSjVs2rSUQGPCFXbtBVwGg/jvK1xcBpfoRzr4Lm9bE2WQqow3bMNfKkGZI3vsdO9nCMeIGVt2GK1cqB9Yafx0bm4TZdDQ0CRKEer8ELFrq7mtsA2j9dzz4QcNdIE+we8I3t7eRDmU8o278COXQLqAjbZrf+K6gMGZdu524q/4yoC+YgY/62htsgwa5oGnFKHaSyN27et8fsDO8IncJS810Iv1AteFjTObJ4fRODwE0rBbPkoRap/I27VdvE/sxPe6Hnhs1EDn6Ye4H+Ijzbk3yyuZHak0Wg5UhORXM2HXfsz7xbUYX3zjFn66cZG+bCbXhybOE6Px3EimYec9ShHqPYaX2bXruRyuw7dMHvjld/kqSu+ezuXQxPFhtKG7d0oRqj68AuLTcj8rlMeKb635hoHO1dFeYP40Lc2TA9zQa+CCikpQ9/dfbae9l13K3sscfay5ey+8ho3cd1GKUO9B3mLXfsXlgAGnP/TeA78x0Nn6sVXGT4fmNVUXGhhlQSlCPfu7y669hsvhxfDv7td/KMSjVukT3MesMK2pcsB4KY0WBJVBe7PvtGu3cjnEsc3v/xjfc5qp7+IxzT46q3lyKJXgaajGee5XlUHxRT9ip9jNw7i/9PXk342WztBTXdyebuK6AurY6DmTilBsqC/atTdwOSTwjZE/Dj5goNN1B9eHo020JUslfHGpYWcX1jLMO7EP2SnuyAi2/lPvTfKZUi908pGiuXJI7S4mGuY/pBRi3Yf7qV3bz2WBQvh97gfbuVOdfjMfKzubOFZCNUcbFnTEUgLNm7+ya0kugxR6WQ5s4P2ijdZY9zVxvY01zGQb5p4tlzHFs/FW/T5NeCbDjlTz5JDNN8xZRClCXXP/CTffDX3ARebIN3/BTyZa9DIfJ2+f3lR9GE83fHTAIixnmuAU0sL7xW5ccr05zr1l7HQf9HAT1xalUuMXWVSGbEf9w67t43IYQ/th5hdOGi3V9d5ZXB+auOYulRq/I0dlyOusZ+zam7gcMnhy+aF1c7m26I8s4esskMOCJsghm7gx3cP/adwSo6oUKf5Oi/Z6LgtMXe5+9FGNK0XnZcYPN/8PZFFqiixKapz5HS3aEi6LG/Fdu3+05flsYjvBR85Cc+LO8FqOx5ujGVSOut7Yacojq8jjmf+xPBqtHWo5ZGPubKGYI+Poi3vjB2NGi/9lO8TnkZ3NiUHzH+auPU7qKYrfszvvGbUpiVaREDa2tu1BCFEphCLENs3Mtqt9TDvbtkVUHimVJI9IUh5RiJIQQujhkRR5JZRCJYSQx71zz9yZ+1s+n/45Z30+u/127t32e3/fz32c1z1ncIX8kt43OhHTADjublzhEl1RpqhQMua412/Rvftg31MoZzfg5CBBJ1E=
*/