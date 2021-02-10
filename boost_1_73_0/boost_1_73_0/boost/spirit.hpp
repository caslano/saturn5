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
6NT/fWfE+BONXqss8YSGrme0nCb+aKfU92/w66HWCjHYWozdKFUKy5Y+/Zpw/3QeZ+3xzpfHM1Qj7fx01tzeOWvuOuUM5VhmsaVtnIWQL788NmpOP5qoXPkbgv/K0E07BWzEf2k4fNIMvtFSnOnAX8mPMCJ7oukh8f6KdBUDWuTQfRoFSCq+ecV+NYUt6G7gTCuYOBh+VtixNqmbJYmI0ippTlDsytNMWYgXZqh6VY2XqyBMCK5+PP5xbscq9s2PpQL3kJKJZnp/yfyf1cn7KmUeg7LotfasSufeWnlb7cG1crFarqyXRdiW6+UjKuaiUZx0EckFq/PTCMbtvymk37HoGdL9PwtfAcB7cPn5NjeYg02uXOWpEspYPdrCo1dGtmfe8ZCtsjTO0sf3BNM0/+s48wGwVobHBMeW6BGPB5wz++7RGqdifnuTmpGaD7p8Kh+LsnWYF7XKvOyL8zfe2jA9N8cvjVcc11NzbE5gOPJDsa4JdS5FddSL5/f8bNqgv1Yd7lEDV9xulifHwn2V+HchJOJfmUzQTe683bt1fs+PqvzQ+dFpmfdsRc4JH/4Q/v8AUEsDBAoAAAAIAC1nSlJFD0RHHRMAADRyAAAXAAkAY3VybC1tYXN0ZXIvTWFrZWZpbGUuYW1VVAUA
*/