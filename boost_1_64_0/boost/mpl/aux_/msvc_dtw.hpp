
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
P1c45qiI4BqWuwTwIFbIIZckuBIRrgwdh7dE7l4vR5xXAKJfq+uBoL/gv2jShkdKJjqK9N8bopxb45LQMCO65v9z9gBoLM+5l8GyKUveUaNIHMEnyxDVyN5/NpxNum2QdT9mUHgKaXN66S5lhOmC2tjy6ZGE56v2ZDH8KmZ5ZBpnPJDuTdixQ0+P4JNZqUWimOV+6piBr+9Yj04NpP6GtNxFxmLCWBrjn2vTkTG/9nvwHq2roOiQuDw7OS6mxoTUezuDWdEF5zkHwt/LHIgXD5ZMuo3rBZXGisz2/InMNIL54tGVIXtGwFXOQgaATzU/x6laagIk28iNbGX75L4GaWNEIf7PKqo9Gl3FSPJVARfhoFbvtAN6p/bM7DZyJ7HmQPVgWD6MC8Mde5CN5Sg6Wgdki9SchxOCoy2pK/cPVTfpBspM1AapJc5vdq9ga6HYNnjv9R7zMPKvqr6p3/Exq2+bvMa3eeg80qa/wV9WL7QGVe5YE9fCj8veFUKbUhMvOTSRi0idEe9HHFSXTsyGaKI1KjlARIs48KsCwA+YTceSCBRGYTiRRFT3Zw==
*/