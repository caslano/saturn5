
#ifndef BOOST_MPL_MIN_MAX_HPP_INCLUDED
#define BOOST_MPL_MIN_MAX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct min
    : if_< less<N1,N2>,N1,N2 >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct max
    : if_< less<N1,N2>,N2,N1 >
{
};

BOOST_MPL_AUX_NA_SPEC(2, min)
BOOST_MPL_AUX_NA_SPEC(2, max)

}}

#endif // BOOST_MPL_MIN_MAX_HPP_INCLUDED

/* min_max.hpp
6/fmzbjX7bNmK8Bm3G31WKfTHfTjDm8Hb5nRyKtaPfL2/e9Vf+t+AlBLAwQKAAAACAAtZ0pSKWBHuSsFAADBDgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2OVVUBQABtkgkYO1XW2/bNhR+F5D/wHrIS1dZviVpPDkAZbuxOzvxLQm8l4KmaEmxLLokFcf99TskfWvareiwAUUxJoh4O7fv3BhfMakokezK8ZNszuGzYJs1F6G8cjqTycD8QdftiZ2sBH/eHE3RzaTXRyRXsd1sJREwtBu+d2Dle5a78wsaM/HEhCuTkDm+YKt0Y7ZVnEgEv4KpXGQsRPNEACeZZJShNUMRUyjjVqpr+YdEEaulVy6WUa10gTAccJF8IirhGRqxj3kigJfaEqIlQ8sNChkRSK4lTblkJ87A8NSkLFMJJYrVjV0nzomDsxBteI5kzPM0REmUccGsslp8ESyzahgTWPalHS8tkNb+gwnlUql0ZEalVDoywwCRgZJNnilQz+2xLFJxHVUutHoPLKUcjAIDQTpioK1UxvitYpb5XlD5BV7GfWqzYm4ZNKYsedIaA5ski9CM0IU9rJw41m111E+o4JLPldvtjr2zYulL1aq1w94EyOtIsWflxWqZ/oZoTIRk
*/