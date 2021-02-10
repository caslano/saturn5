
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
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

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

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
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

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
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
bIN/7mmkkb2ltI275NcQyT+spyhZf3K49/4dna4OQM8CVBUworc4sGyVhzViA4nf2pAwue+xkWKvzMZpUllqr9aGhI+x+H8CivG9/wBQSwMECgAAAAgALWdKUn4OfU2AAQAAFQMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q2MTFVVAUAAbZIJGCNUz1PwzAQ3f0rTkEZXdOFoTJZKAimlqbAWLnJhVp1PrCdlv57fElKJCgSSxzfvXt+93yWHp3PlMOESV0VdVj2eDrWNncJSx/WS9bUzvOPtvbIpBhzUvRwdsWuIEV7QMudzgPIYmNOAZArrxI2b8vyBHQKFNogFLUFi5UqsQsGnh4nxVDXEd4ZjZUfCLNuEyCuOyZhrvBNKDhvZWMx22G2T1iD1kCcru7mTyth9JaOEPS5mV5PGgPlPtcW4uXbXJj6fchMJyEY+EYakCSwNwBGAwbhIS36PMisLktV5QnjPHgDWWvNpte7oT3nTbu9kJiEMPAW4pf0fjUD/gwRH1y5JO53sMJjBOTDTIj4cZGun5azOE0fl4vVmtbNuYBMpwL/6YMaXTkMUugqv5VLavCf/tnyLzXk38gju7umfm6jHyqi/8wEhWkmzlffDcUrWl2cgOYFVOHRgt/1
*/