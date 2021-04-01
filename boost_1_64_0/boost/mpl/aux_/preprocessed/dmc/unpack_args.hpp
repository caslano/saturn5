
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
EWDLLAfjjduASBgZ2ljOsar79OVlQZCDRVEBsQEhcebGS99EyieGYZnD1463iil4T81aWV74uxK7nYVl6PNx7Sas33itrdXO+OaodsUf7hkHvSjlAWfaLgqZlsTdm+bqQRngOjjmU+2KoO9X6SXEOU0Z8fatHKMdHzCLtbkoj3UsZq3cdmYp9H6dv1COz42lGhLT+eGfolZ0C2P1Mfcinurn4rZO5DAIAy0jaPksSsV7zOmd4yILy0OgSn9MAwZYTpdGC5lh2ynOpxpYUjvaQrFKGn2Ew1bbK+pR1jCshHStn84WPAh2Fyb124jD68RMVVEEMLKPYQZnjxyfjXrrOW1a+ly4B+NWCbaYxNcY4YBtL4L+614kfrnsGYAx+QXR9LpXURdO8w1YjnclFtQcaflzG0QVSDLwuEwCjo31V8o1gYb3ASUBM/WzJhkn1T3CSP0WcxHvILH9r+bPq+iE3hkUS7rsoSCbvsHMXBrZR3zIGVIwigxVPJvSX8qDJKTeVKO5Q4y9BQRLQrwe2mB4OvffutQgNyAiY/y5fYcrKYaJU3bhf/dF9KjgwA==
*/