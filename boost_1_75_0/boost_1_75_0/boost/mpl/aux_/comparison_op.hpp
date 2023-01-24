
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/bool.hpp>
#   include <boost/mpl/aux_/value_wknd.hpp>
#endif

#if !defined(AUX778076_OP_PREFIX)
#   define AUX778076_OP_PREFIX AUX778076_OP_NAME
#endif

#define AUX778076_OP_ARITY 2

#include <boost/mpl/aux_/numeric_op.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER AUX778076_OP_PREFIX.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/aux_/config/integral.hpp>
#   include <boost/preprocessor/cat.hpp>

namespace boost { namespace mpl {

// MSVC workaround: implement less in terms of greater
#if 0 AUX778076_OP_TOKEN 1 && !(1 AUX778076_OP_TOKEN 0) && !(0 AUX778076_OP_TOKEN 0)
#   define AUX778076_OP(N1, N2) \
    ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) \
/**/
#else
#   define AUX778076_OP(N1, N2) \
    ( BOOST_MPL_AUX_VALUE_WKND(N1)::value \
          AUX778076_OP_TOKEN BOOST_MPL_AUX_VALUE_WKND(N2)::value \
        ) \
/**/
#endif

template<>
struct AUX778076_OP_IMPL_NAME<integral_c_tag,integral_c_tag>
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
        : bool_< AUX778076_OP(N1, N2) >
    {
#else
    {
        BOOST_STATIC_CONSTANT(bool, value = AUX778076_OP(N1, N2));
        typedef bool_<value> type;
#endif
    };
};

#undef AUX778076_OP

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#undef AUX778076_OP_TAG_NAME
#undef AUX778076_OP_IMPL_NAME
#undef AUX778076_OP_ARITY
#undef AUX778076_OP_PREFIX
#undef AUX778076_OP_NAME
#undef AUX778076_OP_TOKEN

/* comparison_op.hpp
UqCyGKZHYN5jCI8oN7zo4rVSih+tqr3m1duCV51N2ZuA/a0pwEg+OOoL3n3eKaiWzJS6aE5FF8myO+Gkf0Ds88V1k6zY12W36L1lQzpobsy4Dxvga5IhXd0+v6m+6h2Ad3h/Pvvv8Dc4sW2nH09Uh9YHUvJK0TpK8tR0c0xxfUC8O3htD3eD39AARh4ORHVe3HKruoZ4Ue+Y3ebQFNZ5QTTlyRM6JtGb3D+slzIn8qwSGv/otNdTARCzFnSG2AiXGWULCR5dCqSrxmhGaibMBRfnh7c2Dal84mF3au77y20/nwAW3oDyEjreN2pzF8Jfm5zeb1ZMWRdqhjMN6mFu7/fNE9dRTkxp19C8+rSXkMQeRW4H3ougDLigUIXImBEzmGLpauPLmh+aYH/ysBdP7EdhBXjWW+EXy67gBOBLU3zOFh/sC05xq1/HPHMBlk8h+30IE4gSiM8PpI9mOYkoQym5G0NCtczKBzhFGGzhtqOfI7O7D1Bh9ONTBP9JETqb3yeg+Jm2uRdtCaVt4F07iVA+NlXwXyRNgRQRBAKo1psf6fIhexd7Gi3+YHLTJu7ttlymNIF7z3BZcHDucrxKITCs6pKrC8Xkk12vUbHP1tJjV7mgPvmpj50cGJpnD5n17b2/4f07/I3lSPXZj/qgVQyPZJPGHzNX8prz02546oNJtcypTK2L4I+67U6W/X0at3Af1DFsEPZN+3Md
*/