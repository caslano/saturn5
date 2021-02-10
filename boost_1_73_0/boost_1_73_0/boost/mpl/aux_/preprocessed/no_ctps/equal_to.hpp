
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
YLHUgQNiHQLDn0SI5mO0Vnq1CUJ4YlhBvJGnhnUDRS6Vm54ao9VqVn6w2cVyZdAHOh+Ga+HcVPuJknfFg1d2vppMmci0b5R+Gpa5N2eZ1Ql47BLULahaGrhgWAqSsMBtyxVaVKeazXqTdRrHjKMpqYIPQgcyZgt4nwUKXJbmqRPKFA6MylKP8UQ4PqBeu946Zj8NhMqD+Gc2G83MTr1Zbx0YM3KwRgYh1iXqPWaHeJVIeIHDFIgwOjn0giiCEp8CFEvbjmrr9PAz2iL9d4qE0oHRl0hirGurIsE9DXfa9HUU/s4cX6gU9EmQytrLl93fas1SOAaHUOix7dUPjBWxh39Ibhk25ApLhIegmhWYO4rxT4HOVIzgbQKFUZgGMUZPDswDjQYq/moldSURzUaj+WVk6K0yw/tHBXNBqM9fm63CxXR1eb56w3mf0+Ph94Be+meeN+ROt8mvLgdece7w++esw9ceL+h13pii3pzPcxu1hnzo2a/4MOfLub3iwyGf0/rVnC/pR9vjV7l9zfsdLub4ffaG/8ntkI+u+MSzMz5CL3Ke0v6a2wkfTfnV3A5o7XJbkt4/6pfPycmezwnEnvZ7rN0hjkZQsEJmR2VW7LBgUjFPMpGL4smWqwpv5GtHapolCfJc4ruGPX05
*/