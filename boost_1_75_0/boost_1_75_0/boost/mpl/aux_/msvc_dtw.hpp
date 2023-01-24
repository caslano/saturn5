
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
/aFq4ATVJe0sKUAMfnJ8wq1bdWxNRF7tBtUAdyQCRNnvB+pRAx6qvm42A9PFgtYqSDLKyev69j6RVHr1/L4pYqTsH8/VW1u/xEddfFWaVmHQHSLgVRtEgy/vuvSTKA2bsWiH7NVBITxWpTPbXKhArB5ENSVIv+Xz1E/TZJwrsr6TNaNV6uTx1mR/qvQXZju13hobuwFCfz9hRI2xURjCx7mg4/jClAOpV9KRuLhGIxKh9tyNHXo5urWPG6n0hSfy7mj2+bMfDYfZK3/Nv01LLZU1tL6X12qV8PBtaww+DSbx3IkBz21vtPnf52QLgxwz0zoFxZqG+XzkfwdyNftatJUYAWtd85ycSKwkNFpakKoXtFfXzqZTqqyWcahHWhJMkYAITeyk0okmzM+tZ1msn8f15sh1icdUWFlLPIpQ7i523/l8945p1V7sOMB53AlS37ajwCmw0smhyWUUMC7edQU+qKzCsoBILE71H5rD9pxkTTqPQ6sVVi/onP3guFNAlMD+u2r2pTZ+x7XrX/yzM0eEVda75OWP5cmBZ1+nLAsnvLJxDRKudVzXpoy1eZeKZJpuJ46hKQ9hHsNfsyuNTG+IwyBUG/YQMb42Ksf4TYxdmNCX27+ZFBX9n3rALAxhQu4cvBj2XRuQ/6G/2112H+QSJwss6iuXmxsLOfAN3B/jWCBXophqFWlsCz4uHws4F3ub686dr6RVxpNV
*/