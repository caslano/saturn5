
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

template< BOOST_MPL_AUX_NTTP_DECL(int, size) > struct unpack_args_impl
{
    template< typename F, typename Args > struct apply;
};

template<> struct unpack_args_impl<0>
{
    template< typename F, typename Args > struct apply
        : apply0<
              F
            >
    {
    };
};

template<> struct unpack_args_impl<1>
{
    template< typename F, typename Args > struct apply
        : apply1<
              F
            , typename at_c< Args,0 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<2>
{
    template< typename F, typename Args > struct apply
        : apply2<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<3>
{
    template< typename F, typename Args > struct apply
        : apply3<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<4>
{
    template< typename F, typename Args > struct apply
        : apply4<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            >
    {
    };
};

template<> struct unpack_args_impl<5>
{
    template< typename F, typename Args > struct apply
        : apply5<
              F
            , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
            , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
            , typename at_c< Args,4 >::type
            >
    {
    };
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value >
            ::template apply< F,Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
vYg6kmfUCMU2XEm5qtG3UvHV/hqruDDe03B8K6ZfvYELgCCZks1DPcFFJTmxyJBJPurSU409H7T72vgdM+jh4amfUWe+BqJMMrGaklMtPgseDSv0J26omlkYZk7Bg4P8Z0RSwtwR8gai3d/rpCU1zsyVuPKw0FhlGUvOV7pfiGMJr9Ssy07X0Wy3DVhLtiwpgvkfFg2KH7/gGg+b6RgrAC194jcb9hBfy90MbCjAy8xh/2rM/WDZdARlwYAl0+VAVQ0dKqwuaH/s2cs+5Kv90ItxjvjuKfLRVimIyVdyB9Y9zSANZEDPSXTgvx7XQnyjntrp2d2qiLtJC9gfvCHmpPqCUpD8+Glhh4U3ls+Oz17dtwL8NDdRVu0xsVlLnBwI8m2354pLHqKhVW6Ncx2zNXy22J5DWJdVxgA+GdIKEPrYGJAV1eMMaivPr6tG+F92C6gTxrUxdQy3+lVOiW2jXDeD6yBzchUB6OSbqOKeqRJ07DyRuR6rPbwOJke+56PTmqAgs75P61vo12GCqh+mBgpGJOuXz+OlOmxmkyansE+sDNm01l1aXUT61A==
*/