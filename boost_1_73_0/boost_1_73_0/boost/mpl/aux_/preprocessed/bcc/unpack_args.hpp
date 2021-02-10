
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "unpack_args.hpp" header
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
    {
        typedef typename aux::unpack_args_impl<
              size<Args>::value
            , F
            , Args
            >::type type;

    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
ZlH0RpDABYNaUYIavltltqrG0cVMRLNEC1MLZrQGZ3EjumP+0BnUTVHtPELFemVJqvxarg/SByRPq041RlqGmVbUUCFD0zyOIX+KVg/b19Pv+Ve0B9sPSO/U7god5Suq8OKYh3/Fbhua9QSR/3oavi9PBvwMtuEAB+BDn85UT3GUZl8vzRy2jCjauiA9caN57EeaCYeASy0PgHmb9Vc01tL0dGqBTehZmAf6SQ4fvgfEAEnmWq4B8wpFI5BAXZSeXYHZKOAIp2nBaMTRASTAfED08hqkr2jmgJ9G/JqW2gOiOBCKavBHd8PqYUphaN9CXQU4gg8d3H0eEF8L7VyzQXryAYR7N4nCAA6QQp5LCu/Wxt7NNN/NytfUiBLwwjSadI1ptLAf5D8Yw53GgJQvVI2o39lexT9Yw/ls4bPG3lmeRJd1HcW5ryW3seoMC32g4XL+UfMOcB2QoGpN4jvA967cKc7O4Mx31nfuJNpp32jWGLyFXTr3mlcDnkSyF5K4ai+C72zOgzSpN5u7AdJcT43EjTO4RaYvVLU7fC86m8HUh4bzWj3LL11gabmftbB74dkM5v/1uoHFMO0vH26a150Sq9YL1sLeoW5kThSAnxPBBewmZ5Zq88TuERfeN4IbZ2Yff50OGl+YKtiN
*/