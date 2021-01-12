//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <utility> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/utility is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_UTILITY
#  define BOOST_CONFIG_UTILITY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#  include <utility>

#  ifdef BOOST_CONFIG_NO_UTILITY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_UTILITY_RECURSION
#  endif

#endif

/* utility.hpp
HaA8ytPSm7QcsDLtTdYSX4GkIdvEGf1sN/FquY1wwifUZoR7ohWus+GSHvRaFnfpeMKJd2dUvEeId4OJN+Zdz9zzz9/luO9h3vNOljbRk6P5O3tj3vNMnSZLu7jEzqIfWGg9ao20Oxv/48X/JFI0Cvc8L6PStMVb6ltMegbjnn4zLfLdrZvpY8ZKGDnk0vRTJv+jxK6t5GdmcnR+6sLx94rfCs8R7fNU1kB4H+954r616kPu
*/