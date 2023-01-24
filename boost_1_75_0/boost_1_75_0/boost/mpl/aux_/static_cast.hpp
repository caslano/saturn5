
#ifndef BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3) \
 || BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_STATIC_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_STATIC_CAST_HPP_INCLUDED

/* static_cast.hpp
UUCUEfM3TnL5JWdtHHVHKuxj7xzXN3WdrTo6OQHtKtV9Xn+zLrV5iAOKNeiQnMi6fcqJ5SjK1bTjn9LMv7vDY26R30z9Olgg4eW+o1MQPJWczbrUDlli/cs27kd8frqzjoHs+HK3sGJw8rII+Lu3llcABXyuUo5Umy3UYlkqcYbrOF1V24s/Yqe0yGVRyHuh5EEdsZJjAKyvQre1ALhoJcytkSSG9eHh7zZwfuKIL1ebgkLL5BF8+E+3jJkrGCgp3We+eD3E7lq8a2JnXptkXGpreFysaiqgqvEYMTZ0lH33yokujc1oVINpRZluebOa9ORFm4Yc9eRFVeNlJAnOy+tHMHZYVpYzOuqQVFpeUTFgPRclZYWGmrXG8pf5lT05KAM0XA1g4smcoCZkF2pX/vNg/N/fME1e/LngC9pfYlMsyL7+MiR/Dj31IP6H2BTtv8amuDh4uf7yL+noYGnjDPxHHiemrwbETfROb5BycdBUMvDio+QfH0xrwnrp3tXQLuEAP/AU05BbyCxiG3xnaVVV75GX3210VSac+Phmra2AiaXG0qYDCR0oNDy0XEGrDJhhsXlsZAUepAJP26Z+L/DJg+DgzruRutqw05u7lWWT84fsu7N2k/3tHJ9zQR3v598wndicrCdkkgQ+dYrOJLYCRj0LCZDSbijB0VO2qxCQsCQgzR80Ux2IulcpATYTgX7aR+mRMMWpIRLA
*/