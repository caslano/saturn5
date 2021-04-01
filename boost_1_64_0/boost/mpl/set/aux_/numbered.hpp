
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_TAIL(set, i_, T) \
    typename BOOST_PP_CAT(set,i_)< \
          BOOST_PP_ENUM_PARAMS(i_, T) \
        >::item_                           \
    /**/

#if i_ > 0
template<
      BOOST_PP_ENUM_PARAMS(i_, typename T)
    >
struct BOOST_PP_CAT(set,i_)
    : s_item<
          BOOST_PP_CAT(T,BOOST_PP_DEC(i_))
        , AUX778076_SET_TAIL(set,BOOST_PP_DEC(i_),T)
        >
{
    typedef BOOST_PP_CAT(set,i_) type;
};
#endif

#   undef AUX778076_SET_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered.hpp
DXsp5sN3H71rp18kaN4Lf7AXUGVfRKtCRULNSXdLySnbj6uTaeAlBfI2+XlAQdTCOkJ5pDArxuUau/7V86l6+P3loMqsvzOTwAQ8FYlHnCRFDsaDYtyzT15MMEWpL+tlxDNaGm1tJhsFMwkMgFqSMhRFl6QSJUp0otce4taqdTW9Tycmj/TVtH0mreUPJXd1ZeXmbKTlRzuLnjAwIcxavdVKYlpC86dfxR5Kj5kQsOCZQ+m7s0gULVKD6cP+Hxi87jkTDnP7Kr9mKlx8pm6Iln3/+Au7yi/I30YrG0Xv/8W9DBJ2sruNnMgdQNr1x5zSYTIl0Q4izPIQzEJFpcBVp80FemVCIhcBQIVORp/WfrWW+6zJVMcoir7TV7abkosLxZPi2OxHGsbDn5dJYRq5LheyIxJ5qyhSn8plXEDNSBUExczv4H+TRDChzPDCDcYDv3Xj6LMr2KIwZzgX9QdXIpBhPmLfjvPhxzXXiEd+GWo65IMhjUbMA1H72nCYz7usK/dQD7cMB3Aww6fWxeycW2MnPv5zcMrGCTSQLBjFFK+or7RzONl4TrbzpA==
*/