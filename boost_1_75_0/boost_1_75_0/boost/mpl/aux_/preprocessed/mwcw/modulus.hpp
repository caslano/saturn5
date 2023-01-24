
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
ePinUUKr5pRcPUpGXLysatixRh3meYz3oYxwvCX2YTGuXB3QStVJNSHiiO5z22QvJY3ey1ej07plZUG5pXiAO0g/bB5LXvvPX6m1QxhVPJJJC/3aA3+r/+4UM1ox9Zzd1wR8fzkQc5LcXpTcJrkJHjCU32bcUj3D3sfW9MUt/OxNcWuo6fvBW3JbpvWN98Me7hncPFr9AVsPw1utSa/qOdYwsgSoXfWcwFF8xX2Fd2ZygC45DOfx1V4OOiZMjnn5bTE9mdkn7urG4LRJ/Ib6zU3eZ80HgiDftknCpIDXtnr51lXC1s4pCaDbVyn9PI9EZ2OR1+NQvX1IcHT98ZhDIZ/ThlVG9rCmX5Bt8/Qq3tuo8GdqXtsv3J+0cfNcbJ/+tmH7LnCw7G6xdjfnmWTi4DZKuXFl7CeAGt0xkbSO5xjdET2T/OrR6rYEhkePmjwIv7GYeJ1J76ztPB+KtSUPsLg4RS88Af+uL44m7x19GasU7b/rC6cn716svtEfdZ5W8ekzzVVOenE3qLBY27u2pGSSALfrXIoLGjPMhL0uD8LjzLadwj2H843YihA594Y0alOxl4XeafSrgL52vMoC+ZWvOj1/QlUNqilIMng04NcIhnfqcyPJhkwffnuiP7LyTi+oEVCYyfCgUky/m/yuEiUkQO7J7b9bbUgHSuXyDuLtGb/jIgvAM/yxfl4plL3I6p5hQDU77XExnrkm
*/