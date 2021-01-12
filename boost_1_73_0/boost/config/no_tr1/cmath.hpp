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
yDndcSdxJ11mbfIUeMd73wjUlfB2/+g6hjTyZTtKWm5NWE962tfIsU4l35JOTOdJuuKrHCsWiv8UK1vb2hZJy2hPLnfTnYx9/gQX2KdZOdrmzv6NY9+Wz1aPsHZ0p/W9fao9yZtkL/HVsrf6Z3lE1jdpniPhnp8QM2Y05xsXi/2khNoJtDPc7MyUsd2ssoJw2m4UN0EzxuskabvAqk2aejFGyiSuncT1K3HXPuELpEs+4Qla
*/