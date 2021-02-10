
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
4h0shd4JHZoiE4RpUZcH3M245Z6DRh8iuOz1YPYFzN6kpTKC3HErYki24j30hvCodoiIehD14/4wRuznh4R43hicyNA0E7rmz4KMlbRC2vCrkBubxxBFhKxK7l+CyvzhjL6IQY3jsnARXmPaTBDgSUckt7ZG+HEKTPJKePWwmIyjj1eD0B5qAWulq1oZW8gN7AubQ7o1VlVwVJQgCMOpjweWqqriMvMnxJR2p2jj/TzuOur5bJHQPZeWXg4GEE7ARd1kXBaihHAKnb9ZnQ2/bON5B6W+EuPvSzaY5ZPQxfoALn3gays02Fw0/kHODayEkNAxubJIsWuwzgSri7rmGikM/RmefL7z8HcvHP64oKcxFClWaiszrg8354nOQqmrSquP1VpZlapyRFw/QuvesdECMsXyxPDG6IB8w/KGtxv0Ksay6ZJ2nz4tlvezx4DcpqmocfmCXgRvu6t/1S7+U4prOJtCQAJy2rCW+a4w2FmFLZSMgVvL07zC9WvfFR03dhyX74//cTpWRlurGH2tNW0v/B9QSwMECgAAAAgALWdKUo7UlwHpAQAAOAMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNzhVVAUAAbZIJGCFU8Fu2zAMvQvwPxAdcunmKAmK
*/