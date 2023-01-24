//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <memory> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/memory is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_MEMORY
#  define BOOST_CONFIG_MEMORY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#  include <memory>

#  ifdef BOOST_CONFIG_NO_MEMORY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#endif

/* memory.hpp
dOr02oMTaw9E1pIUOX9cG50VUNCYQPhrfSk/OmS01Dtp+31RkS8r3z8XKbSjbgGym+HpUjgOb1ds+rUEDS3euDjtFWt3aMYFfl1UGbS0My9IunWT2tCCOtosNHNJoHQmoXv9t3gRdsGm5RTs56TrMa1D3pEtUvIwwryAfrhELFqpe5gTTsCXzRT7yoVx0jGhGY0f1w/PnBRAtSsahBOLNzsuLKlVSJiHzHWFPpjh6VbYUftku7Xt2vIy+b5lrJ2Ba8HRLq86qeGdpRZEkrtzP/6nb2zf+4zGv/MCMKwUlcr+2BROdhMJ5QbXz7hxU+QpJ0IFW9M73nAlG2eW47Ti48u0nwUmd/dNxa/s4x4bZuqgFnIbvqfl9in687fGdyBmmjV09mK1Mdj+xP7nL6UNksf6bJGv187XSTYnO/urU7Keeuz5DYgnuST3n/UXAt+wSQ5yE2ktmNGfM9W9pWu8H609tBcWs3cd78FPTr39y9BfRTNxZpAk1L0nLxHQJ4QhiI+3F2dTDBy7Qqb7TH899ecFepSWfd6h6yYMvu14o1bG5zxRBiEFkcFJgqRn5Uxg/Za/LiCjqyVxi5Sa4o6MjmjgLPORecr9JElD3kdJxJpfoakxfTL9DkAx1SmgxGTSYt/50RtiHm1zErzJYfdLcTLt91UdkUnh9ekUk8mk1OkHvEl8W2yjN+AYx36C+WSSgc3mXp/UL1+VORd/
*/