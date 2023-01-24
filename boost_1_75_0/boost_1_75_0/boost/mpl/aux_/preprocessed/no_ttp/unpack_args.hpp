
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
c/xsOPN5XAceeLygP0DbU4fiP54Vo21xn19f4PTrEsyoXwcgnC5G3tB7dBO4IOtXuF33XM2Eex+o9fF82OO3eWde8Y7fML75Fz8uz/vAGI71GPegB1sRcvEYmgjG1/R560wrPKjk7gfOBFgE7/HcB/In0X0RC/evZ/Wu/TNesmVqBPrUczSlvptYlrPvKjEPyekUl2twla1oGpULGwFp1o9vDdGI5drW0hOf/IjBc3W+Cz0E9VIOVG2ao4YZRiYldkQKTapcFWa6GGXIY6OXPt/jzClXJx9EuYj4SvQR/dva0/yobbGmnGyQKvPwGs5+dsmy5L85Nqd0sGOudCCvIry7Otl/0xV++76JuAEoAN48Jy++m2ZbehhvJPfwnTqSbnzkIwmnuYSmabQTNA/u6+WTfjvmmsuicqICiJPG2GSrMT6Jd/S2xLRPXWJXpss3RwK+GCwbLyRkKA3TpzrK4t1CNYUZ0hQoxMjznubkVa0s6A6eOUPXWy85Ggl3Fg5k8VRMWA4INrSbk06sWiKvPb7yB5NjX1w3fY2otlwV6xAVHN9P0ShOMxd2E2xhrTLnefkDjKMUGC2snJv3l3GSJM6sD794boFMXoe0d4bMIUdak/G1yQxteDPvHObKqy0XjKGYxXoP5Low8Gv9pFiwO2kA+VXzD1DU8hOFkIRIUMsj7jMRR0uUZ+/MjqJTqNLf7gTr+KK5PdNWbrCP
*/