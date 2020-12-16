
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED
#define BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
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
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/at.hpp>
#   include <boost/mpl/size.hpp>
#   include <boost/mpl/aux_/nttp_decl.hpp>
#   include <boost/mpl/aux_/lambda_spec.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER unpack_args.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/repeat.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/forwarding.hpp>
#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>


namespace boost { namespace mpl {

// local macros, #undef-ined at the end of the header

#   define AUX778076_UNPACK(unused, i, Args) \
    , typename at_c<Args,i>::type \
    /**/

#   define AUX778076_UNPACKED_ARGS(n, Args) \
    BOOST_MPL_PP_REPEAT(n, AUX778076_UNPACK, Args) \
    /**/

namespace aux {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
template< int size, typename F, typename Args >
struct unpack_args_impl;
#else
template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};
#endif

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/unpack_args.hpp>))
#include BOOST_PP_ITERATE()

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        : aux::unpack_args_impl< size<Args>::value,F,Args >
#   else
        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >
#   endif
    {
#else // BOOST_MPL_CFG_NO_NESTED_FORWARDING
    {
        typedef typename aux::unpack_args_impl< 
              size<Args>::value
            , F
            , Args
            >::type type;
#endif
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

#   undef AUX778076_UNPACK
#   undef AUX778076_UNPACKED_ARGS

}}

#endif // BOOST_MPL_CFG_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_UNPACK_ARGS_HPP_INCLUDED

///// iteration, depth == 1

// For gcc 4.4 compatability, we must include the
// BOOST_PP_ITERATION_DEPTH test inside an #else clause.
#else // BOOST_PP_IS_ITERATING
#if BOOST_PP_ITERATION_DEPTH() == 1

#   define i_ BOOST_PP_FRAME_ITERATION(1)

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename F, typename Args >
struct unpack_args_impl<i_,F,Args>
    : BOOST_PP_CAT(apply,i_)<
          F
        AUX778076_UNPACKED_ARGS(i_, Args)
        >
{
};

#else

template<> struct unpack_args_impl<i_>
{
    template< typename F, typename Args > struct apply
        : BOOST_PP_CAT(apply,i_)<
              F
            AUX778076_UNPACKED_ARGS(i_, Args)
            >
    {
    };
};

#endif

#   undef i_

#endif // BOOST_PP_ITERATION_DEPTH()
#endif // BOOST_PP_IS_ITERATING

/* unpack_args.hpp
m7cTsyiKk8/nXOHzkKWbt3NkoR1ldIGeyoFuXkdkEZ+P5zRdvRmRmXdTxE+xq/D/3/9/LfmZ+q+k38UcEx1Q03Vify6OZouJQXUQ89rFmwuE3ThWUTlcTRcbxBC24+Ke5jh1AHk09Cazxf1fB+SV3q4svVa5W6ZsHW+/7WULpH1yTK/nsxfus17cTmZl9Wb2n88TF6sI36mjlcqzOmnKtc2XAhRx6TT2+jQIJHmhWcaLkF4E1oxWmq4w4j9Eb5onZ6iW9/KOj9hOfzbauu87lWgU0bkRxECamU/taWaeEJH5kYjMacKH2mG7Um7+fnuoINKek+4VdOLUqhKYPFM9uuIXJjecCiPv08FseeLrddTzICbTIMquv9GOFAvn+OYvsBG7XmaXm2lfVblBEVBJyKacxFk3YMFBbB5uSoqtcQ+qGRp4Kt4IDbZ6L/N38SahGz9R4B6q+5wBpB6uGjdTSUTQrPzGNy3n/Ckwt4slpojGzKw+n6q3JhOMDLOqB82yhoqynKYS/jxcBhCthle6vsQG6EEGTg5t3BWR4TTcNB/cy/TW0IfDMTa3aOUtKPb5O3uTMIH/OUo1lTwW3U264tAs2N8TmeECYg+HMUozW3s/4ef+CXzMg/xzuMDH/ZH6xcC9uQWYzeA6DzTSD7vpObQhBxcKWUEbMZ3zLfRujNjs16rNfi2XVws2izfxWcTENOXD6GBB+e700AUObLA1HVhRoHo5gqYej1v5syVN7ePtS/nNy0y1yOSSgv10SgI29jia8TBMkYw8A4FIisNaH5Hnr9QA6HeunaAO6rFXErvMRl8qdhbDw1MsMOX4esNGdjeILDoDexSHmoXeUDY8fmWm0Fun/hEpRiNFb0HBttipWyqOslaEKuzNVUHxxLR7bRENfG2ktYHfI5lhqxwAVhy9Z0C5GMjdC54qM2Ti13mC2itP5W4PfpTjL4T3CE+j70R889BEo1McO4kmKvt4u0XUXBpR8wI2RkdEitoi9jz7cQC3H98U4SrBujez0Tekmt0bls6s7OU9GpihYPx+hJVk5wGMmcz54yyuHhIJ7pYDoIM3/3CEifp/0c+0f3ZSlD1PvbBoUeHaYZjY2FHWQ0bnIakaYj2Cnl0Byyj1gR6MgXoxSh2uSd5E6mX9vX6Y+s5jfsgkt7kgtzRG3bx9MDe3chkSGZbbpbc+uVItYmV2IXFNXywMwCiEc/hyMXt9dJecyuqHsuZElFXMGx8xwwWOUao8pCqLSNVXpwrWpvrzQWc8jKcjHDLh/G7ek5G1qzUrbiNDf24yLrR7j0Gar4ZZ0mAtU8WP8ff02vWFkddQujptXKV08J8oiLj61cXbhh1Aq1KB3LNBEC7Rws5S5ZrUqEyyOP4jDR+azVzd1IgCjtfnUoXD1AWGLt5UpBwy7Kfykv+Jn3n/dYjUj3l1qMJqbul5J5luDIWGuRktmG2jgKN5b8wGNI3vP+W+0cYZW67RJ+BZCv6fzu6kersPJge1Q6ky08xViO3DG687pYEqvm3lQ0InmeqWuk6hFSJdmfG+C6MGOwcHkCi7qnyZKiUTsfrMwhHuLvQ25Gxn7Rm2FUQpVInjk36az07T/mU+69v52in9mJkaT8W8PYrf6D6ruCzWzyLLp32Gz8nzPtMuly8p3OJ9UNt2ylDc0AjV0KOVAwCYBfCmY/bOGGqdh1spAjsHM+3jUJljAxgRaVfyvKYVhcVFtO+6Rs+XT/IkDB0iYcgR5WLGTPW6MI8+O9E6j06BxzHhqp7plyXDIK8TGZ6JyJCJTuRjJnCL/96JqPdznx8Xcb7UoM/GG1hSiaOZFL6tK81SwZW1Pm/ad0KE77xcxEnG3ljcHVRQeT0=
*/