//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <complex> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/complex is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_COMPLEX
#  define BOOST_CONFIG_COMPLEX

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#  include <complex>

#  ifdef BOOST_CONFIG_NO_COMPLEX_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_COMPLEX_RECURSION
#  endif

#endif

/* complex.hpp
Bd6bY8eWRoZ54G7HbU/GcEdZc5sqZfwSYWQ77cEyZdw1l+FiUeFstq0VTcwrLG8fv8fdKolrCPkK7UWcOmluRHm+Imn0mj5khuhHUguZZty0R8y6kCb0/JohZZoTn0q+2lpvxbXTfF0n7r6PL+akvW34fhn7/ajn7aBV5rnK7usvsLoHahOO7rUzfUmuM6jS8EmDpDnX34ynykPWQl+oL/PKfRxnZWs62kl8zwfqYTaENrGa
*/