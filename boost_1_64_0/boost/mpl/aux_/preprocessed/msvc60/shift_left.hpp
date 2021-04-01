
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_left_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_left_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_left_impl<
              typename shift_left_tag<N1>::type
            , typename shift_left_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
Jv0Wh56SJ7K2tANAKmXyllU2757Klx8/k8VtqiMwkYYCToBW5FY4dOnq+C/LsqeqLC4Z50ACN7q/iVphOOvFh+vQIiKdU415sRkC13tHKWGSrY/HdroPCeeUNa+GIw6dB5Q3icrQ/RgsxepIqiMcSQxsCbenzMRKK1nwst+V7Q4ls0GhHp6UolxMGK5y0zd8iNdW7DsG0bOEKrurUyrXQtReVZA00jcrSRFcE74r8MyywaK8/BilG550GoM3MKa46AaFeNcQ9NxgVhpAio7rVnkyRHpmBI4ikkWSyh6f764pPbrpZu4Z0vTYVml4XfV4V/r97gdzbBbG6m8Mf6Jt3yHyQ1Eme5BqXpt5ViYDX7B+TBjMwsbN/O0Kkmrottn/3wBYY8+GV7e/p+1o5o0tB1ms9qYmpbstpApBuzzSsXvEzfHz/Smh+vNXNaMaEHZ0zPlK189pOepALRBITii90krx57nHJMhcIc3XzNd/Bzp/xkASeEyis2FzWKe0DJkSwwjqOZw88E1miQUntgWA4Rmt7SQY70sT4n0bwtuELfcT6R8/LqZrIAtdxQ==
*/