
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

// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION!

#include <boost/mpl/aux_/preprocessor/params.hpp>

// local macros, #undef-ined at the end of the header
#define AUX778076_DTW_PARAMS(param) \
    BOOST_MPL_PP_PARAMS(AUX778076_MSVC_DTW_ARITY, param) \
/**/

#define AUX778076_DTW_ORIGINAL_NAME \
    AUX778076_MSVC_DTW_ORIGINAL_NAME \
/**/

// warning: not a well-formed C++
// workaround for MSVC 6.5's "dependent template typedef bug"

template< typename F>
struct AUX778076_MSVC_DTW_NAME
{
    template< bool > struct f_ : F {};
    template<> struct f_<true>
    {
#if AUX778076_MSVC_DTW_ARITY > 0
        template< AUX778076_DTW_PARAMS(typename P) > struct AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< AUX778076_DTW_PARAMS(typename T) > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template AUX778076_DTW_ORIGINAL_NAME< AUX778076_DTW_PARAMS(T) >
    {
    };
#else
        template< typename P = int > struct AUX778076_DTW_ORIGINAL_NAME
        {
            typedef int type;
        };
    };

    template< typename T = int > struct result_
        : f_< aux::msvc_never_true<F>::value >
            ::template AUX778076_DTW_ORIGINAL_NAME<>
    {
    };
#endif
};

#undef AUX778076_DTW_ORIGINAL_NAME
#undef AUX778076_DTW_PARAMS

#undef AUX778076_MSVC_DTW_NAME
#undef AUX778076_MSVC_DTW_ORIGINAL_NAME
#undef AUX778076_MSVC_DTW_ARITY

/* msvc_dtw.hpp
jX2UYM4lknSa6WGBc9msokPPHeZQIZtDPcrY/M74PU3BLaFW6DLK6VhkbLunFw+ze1qFxoLEIuPME1JCgnwWeiAm0d/IDTDjRJyEnGaOjorHmdx6cJPEvghKyDje04bDYcYCK+F56AJvpZSfbz1XiBjB0eRkXzo4be7vaXuaE4QcwQejEfbWQBPskyfgthVWRVaPuBT8sMnWyuEHiIV+IL5BlvEVWW1CvIVVlK1F7JCvNw/iZRu1a75iqpaXnPEFW4ZiKyXOyObuApdQQ7CNTYgXguTdQc7nt+FATtRtOYO207esimWlN9s6S1t136pan173c21riM8rtnXnKshbOr9fy3l1/2STFC7CKNpOjeJjxY2xwQ2whkBK7MNKhOgdhzGRkc1TblAEwb9DogyJoRbGOIrmB2C6ArMNgrEMBrCXeQ/OHPl7ZQ703HjxZ2SP/Dp71OiUiWBb9thGWOG+2WPHnP2wDFLYyCCF/84gu4X9C2aRwkYWKXyRRbZHU/4PiSYFeFm5jLdH07a9uHj/aNopZz8smoob0VS8TzTtEvYvGE3FjWgqPnBP3nHqeci+XFRxIdtuQNzrR1CdP4LC8jeqDx9FSfdIKpFHUVA8kn3wt9zOFlsY9JZHZE9RJQqlOHVy5qYdqOnGBIsp
*/