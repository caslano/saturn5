
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

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value ==
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* equal_to.hpp
bXDiq4lzc+FcE9IlegX47ulNdxAEfeIeNcniphfkFy7ZrkGbLAOS6+2sMUG5GZmtbZTqk35gfyb9NZnPbIf0+2Sm6c8zMtc/2gFZrO1vpNsmdIbvwTX5QuyYDBdkHNgZGaIVayL1+ZLYKRlOyGJmR5r2iM213N/KF+v0dBfPMUsCFXbgsK1jNGQ55Dw7KNJ2gwVwAQEHuqb5mypWJd4Yr01QZZamGOcC3yXbhW+NWopoyyJFdfxkRbs88VDDszhVsMdRwjA1JCqsRQn4gq8KITeO0KhtyFtPQt5qNLQxSSCBCoZpgxpQtIx1TJOXymUSuYJL7qvaaDQ3j+qNn0/zZxi2WxrD6lQC99Foqooc16giKt8zbDHMO8CEFvUdlq1N4WP1unf/yer/vzb/cW3++qlepbdlbqbdO+gWJV0NwbK+kaHsFmdGqFSK7BsS5wPnsc6TTCK7Js6MOFoenTSQqyQtn1FsPgxHrU4TYz4fG2/m8+nI8NgyC4xyTFvmjg2shK7Y2dPRzX2fCbmrjX2t6kDfCjyJy9GOcmYpCGgv4nCvDcQZ5XOBw4pnAvg6gZDj/NJ8BzpI+A2AXRAdWNE7VvQ0/dGBlBuWYfRYyvCBXa57fTX+Oug7Q/zUuCCT/qmbiVhrK29RIq+AKNSM
*/