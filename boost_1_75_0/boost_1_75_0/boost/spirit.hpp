/*=============================================================================
  Copyright (c) 2001-2008 Joel de Guzman
  Copyright (c) 2001-2008 Hartmut Kaiser
  http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT
#define BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT

#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message ("Warning: This header is deprecated. Please use: boost/spirit/include/classic.hpp")
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning "This header is deprecated. Please use: boost/spirit/include/classic.hpp"
#endif
#endif

#if !defined(BOOST_SPIRIT_USE_OLD_NAMESPACE)
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif
#include <boost/spirit/include/classic.hpp>

#endif

/* spirit.hpp
vGSbc7ew6z+UQ7vZdbP7QQj3qVkUQOd5EBDO2IP59L1eS+M0KRaV6ZpWDIKjFLTkjLa45FqfsKNw3iVukMzBqwm7qfVh5U5ftsefV8VnHRHSj9iZ6fDGbvwdFg2HfGV9VrDrJwEEZ7WGKbjD5GuAsEkACH1FNqqEtVEO7lZY7p5sMjnUCH3MO6/I/ZTN515r4iI0gmWzAN2TG57NwwngWj+0onfI3nMalLCpF354rlhyw1hwo20UIgi7ns/dCqVdE7LEmcJxtKLSR+Za1Wibwr4Jq0LeRZY42XlJyN1qh948wqdf5p3F0z3+lS80f19wFS/+1gwW4NOOo1HNPsiCvPb19a/rwm6GVU2GrFAAfPyFQE5TjeDEFnrX6BKFU1A7b9nJI5s578miJL9LCkqAc0IC7IM4f2ehMZV42FFsEBhfV+911npzjyEHLrcYKkROkvY08p+OIO9rGAM97hfKheMEBxBGHdP64VNuoslZyyHzqSVvmiuWLBC4Cm+C0XxnyQyzb8nLQvohrfOE9jRx9Ph0ZEx4w0dB5lPEUnseWWrQSJiIEbrYQlhPu5NS8GssOwuz6qjxa8IEVHI9Ir1MCHAz9JY0GILJdb/3jtYIXyHHbyd5RNCwa3+twUkuWA4JVUCzYippoV+lbzuQk6zbiJbxFWINibjCyJD/TESKZbcCuvsrm1AxWaZH+19HShSJSYXMfHou+qX6w0/U
*/