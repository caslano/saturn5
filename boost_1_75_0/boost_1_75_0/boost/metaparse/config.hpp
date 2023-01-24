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
6BAAJ7xzWAeTmunrveTYLF5AbD2qcOjdgg31m6vQ6xoKcbLE31CigvmAp3H8X7EP6JxVOKZ7qdoa2spiWdyXpAEPl2noA9fAZr2QyhiM9RpsBT561IosUAL2sZFa9zIQNRaU5t1bd9uvknqpVSYnsZ5fgpfdAO8KYXKsljKPBC9flro9OojaP3xgiFcVbgkisf+qu9Gyu8KTUMvok56xccf0QtlZQoHXBHME8o9tDqtbaQ7HN9vqWlqKkL7cTYc2dZ/J/+9G7gcMHgYOlfKBIx9TOWUfpbWfxubpo845RQF3zsszzrk3+py3lVv7zhucFM6yNO9CzjNQdY7IC/fAZ7STl3jB3msxPsbjrfmJ2Bbi8+Ji8U179UM7FNsqMOkSwqRbEVQYZ5UiR9OhfC8OBdIfw7n0bMVlA1G9GMrXQxGzm2Qvn02/OJuT6z2bq4ey6OuQt9O4Y2II62n379J++UHXxW+xOXO24ibOWeNTB2fA1md5EkW75z20I0f9WA5l+FB0Hy/3eBNqJnqrXJkNW2Xyeng7HcxBGe+X4qZ4lEon8KlpAyYUpN2tsR6ctlTMUKSvkVWhuaKzNjYFSL2R3n+fICO8CN0RjjyHYclDX56NT8WgyigbMJO/cbngOITjJoBicFxZHUCOzzZliDkGILXV34P8kFvYFxx3ACuqOzZeLiteRmBYI/49Kub8KOKW0OJK2BbX/3QW5OeP
*/