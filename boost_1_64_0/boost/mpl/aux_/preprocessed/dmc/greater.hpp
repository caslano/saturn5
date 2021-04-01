
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
gd3CmyDPYD+bv3hLDUsOLpsaaxJS6ofhIzfWQXGDVhPIKCx/t7q16pkl6cCnUhXwmf7K07DeVV2T2s4G1a2SZRBik1R6JO96p3/7tGuWLTznwwoMTwRoYK+Jw9XWxQKwF82QsKcuJQ6xjHvbJeshDq2ZVY/qNUpe8AvLgf+eXCDFDFS3FTQ0iSsa7frgBUiJPnQ12MWwtUO4YWQZYnMsn749jS+PaWZdzO/2ydb9MYRMWSbtVeJuT+PvrZmd6MIfpTdUM/6gCxZV1jvW8PJaajebvC/WsGqZqJ7zDh8CjHM7oCK4wVkHuMBT7Ismx9A5cbOY+PvUOdVhhbe3UIKpM6GzkM3hNFVEGDkAumIN/z5NAdksdSEchnkgtxnULWGfyJrEJNXTyDQhMfC+Bil0J03/QD8V5vOMBZW2d0CkEILqQBX0Jzq+sMqaE6D8kCY7k/9AbfxT1wcandBL6WvdSgBbdqFCnObbab1oMmnY3PhXy7yoke/cyMTvNn+OkBTAaZ3r8R87TW3TksYRK1uu5bcx8UpJcTKzKgC+xdzJnkMyjqoQjBdq1GjE/Q==
*/