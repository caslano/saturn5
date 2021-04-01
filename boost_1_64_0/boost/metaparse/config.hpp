#ifndef BOOST_METAPARSE_CONFIG_HPP
#define BOOST_METAPARSE_CONFIG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

/*
 * Compiler workarounds
 */

// BOOST_NO_CXX11_CONSTEXPR is not defined in gcc 4.6
#if \
  defined BOOST_NO_CXX11_CONSTEXPR || defined BOOST_NO_CONSTEXPR || ( \
    !defined __clang__ && defined __GNUC__ \
    && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)) \
  )

#  define BOOST_NO_CONSTEXPR_C_STR

#endif

/*
 * C++ standard to use
 */

// Allow overriding this
#ifndef BOOST_METAPARSE_STD

// special-case MSCV >= 1900 as its constexpr support is good enough for
// Metaparse
#  if \
    !defined BOOST_NO_CXX11_VARIADIC_TEMPLATES \
    && !defined BOOST_NO_VARIADIC_TEMPLATES \
    && ( \
      (!defined BOOST_NO_CONSTEXPR && !defined BOOST_NO_CXX11_CONSTEXPR) \
      || (defined _MSC_VER && _MSC_VER >= 1900) \
    ) \
    && (!defined BOOST_GCC || BOOST_GCC >= 40700)

#    if !defined BOOST_NO_CXX14_CONSTEXPR

#      define BOOST_METAPARSE_STD 2014

#    else

#      define BOOST_METAPARSE_STD 2011

#    endif

#  else

#    define BOOST_METAPARSE_STD 1998

#  endif

#endif

/*
 * Metaparse config
 */

#if BOOST_METAPARSE_STD >= 2011
#  define BOOST_METAPARSE_VARIADIC_STRING
#endif

#endif


/* config.hpp
sFfS31TvImBodhXOVZ/PMpdOwLBkgsmoJxO8pncMIgtvPz8vsCXy6JbpNvdjaDr1/dWk27G/eHFwcD/Rf6ZR18lshvdYPLDhPNyBctqZCMYFum4cMAJ5+iRytkl6NsK7k06EzeYwcHGfi1Z6ZDzB5OU7rdOWsZ2RiHiyEwz3wLWy2V23ETj1Osdp+CTKKdZV/qyePvQtCMaeWPWc80pVlUYy92rWAeHagadsbyE83HUkNCrpNjvKTOkNgYVzV6ACP9i8qwfEbJX2u5VQU0CKRDDJFeY4ljD7cQWhReI2rYdCHfjZkv8UtaukJQQnBwAQbCDcrkf7sOc1gscztT4mrE3Qmx/yCap8Ezox84TB7xkh+fwjL7+gCXOj2KCDAbsZ+4UJOjnwhccj7+SkKEZHF/9vpg+H97wmWECy5sR9y73p166enhz6L7HZ8/h7gvI/gGyzH/TDUGG2nArZD3ldiZpH9mV08P9hZqBeFIiFecRgDqswN3IU1Ypp4aZ1FN7nX3Do2PO9/Hrd9EzlH9CupiSPwL07N5szRvS5R8uAkalvNJbHPQ/bthJ9zw==
*/