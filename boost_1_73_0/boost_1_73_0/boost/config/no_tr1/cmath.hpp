//  (C) Copyright John Maddock 2008.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <cmath> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/cmath is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_CMATH
#  define BOOST_CONFIG_CMATH

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#  include <cmath>

#  ifdef BOOST_CONFIG_NO_CMATH_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_CMATH_RECURSION
#  endif

#endif

/* cmath.hpp
wsENJtfpEwpAJd411+nYKnXbsExf9Uw394e8puILo1rxzB7gjpLb8Sa7C3XfrpXG3Y4tR7y7k93qaey7CarlUO6RHdrq9wC3Xh3qldM+N3hm2GQk2v5NzQRNGruLyTInYlbZQaeHRhvIHcFE6hiDYJU28oUg+OIf3PxER7a9WzCc51oSrVFz7RR+Mr03wQ7+t5hjWvB7x4T4LeauILmsyOnEdaVyN+5tkMEysQVcX2Jg5Pfb2eSYCnaQzw4tsGM=
*/