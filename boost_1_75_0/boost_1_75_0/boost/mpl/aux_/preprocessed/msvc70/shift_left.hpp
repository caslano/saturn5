
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
    : tag< T,na >
{
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
5w6JzinRc7pM6xEMMpqz9FlTvKTmDVqDARqQixDdQgIJrTLeJ4XJZhrS0ZaCi9ePhckVlkNOU1Equb9aOCjIGya3/Dix46TN7c8ufNoTob5u0z0VFXjz99n833OSc76ThnZraBw8rbD7iEMFhEM0EkqguzI77Lc6UtfGVN/Xdia4fhveZRV+4oiV0etXmLuYBb0sxWrlwM9abLQUlw5WXsrHyNnHxsO78oOydOtwXMtnrgBcidiPHmlox9XCyaYUFbNPskSbXKZZGLJBFqTPwxyO3euzxeghs2PGJRxUw/mzHcSCrO3WD/aDCoA0qUbEbVdkP4fFk42K2ZcmmSTRLBM1Hg0+tfSz6UFmgtIdqGokL1opHi4Q/xYf+xKRH9CoYP6BCHmCVg8nSaGcLQuhVeKBoJwvVTFdvpxYr2ot6jTJUOE2SS3bXf0zb/1UVLkbQzzywsA+SRsQpw83eKjxxL3H2jrlKjqspqnrFF98NpzulwxBUbXfgXaFU2qEkRocUq4AxYXUWR3WwtNVmaqVIuuErdWKXeuKNQIJQamJdF/xAHJXlC3uPZCVYruurLKvRTmS/VKpH14/Mr4WXd7CWtajhyiS/QHqmXZsOPerU+m/pbi+urKAwXQkZnav7V5TU7VUlr5ok+Hb6+81LZrY1C+fsKumrIzE7oki3lheanBVk+YczWnJvuZtr6QFqzbXoJf7s8cayj8sVvjH
*/