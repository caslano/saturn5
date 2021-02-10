
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
9rim+e5qNAmGY/edHnI8ug3M+TKO85lkyTKmCiNz6g+/m39oCx876t/N3PSc/0bB5jkUYACdKxSgFggFF7CgEu4QUziTC67OiPdQymoFKAQXIY+0QZZW96zoSRXxpVb9+TWJ3GJCWSpdKJPtkAGLsUCgqvlIxigSJiXjpZBYrasM70twI/jchU6n84FM2L+bPkVqWM6FdUmmGv6nSo2jEeGcLmNFvgq+zNx9LQFLninqZQIaHYCWazdK21SebZojVrDKRX5YCJp1CE4DgyZA880waNQwCBcJj+w6DoZR5ec4OI5Tx6F5cQgQ/qIp2DbYlmtZNRAE/tAuKGCua0mfp0q7nEuM1yQSLJgsFYJ2yWUcaR99QMieAChm+soxDkqZvY+yxs7SNar8nLJ2u30cygZ4pw0DuDgVyvRMT4kyax9lzRdGm9+UMj3TE6Ls0z7GnBpjhjEps/qJMcuy65Q51qf2IUj7RnOtTGe3ab/J/nCxD4bWDgyyzMFPMNi29dvA0KnBgEmm8lmxnD/qU96e0LuzW7Z3d8tDnpps27XqUBzDjU/HQds1Skoy1PqlZDRbvyAbZVDVOazUAZ9XIfZsC8bZCRHWqhEWs/T+hTvgQTynOGZCuwgiTv2sLfOktC6g4geqbZfHFXZIVOrX
*/