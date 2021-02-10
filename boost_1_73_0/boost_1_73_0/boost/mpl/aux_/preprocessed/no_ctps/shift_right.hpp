
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
lFUaoWKsQY00raVJN+Bl8uILNUvsyHa79t9zTtqVwst4XRQp8efvznff3TlyaF3OLQ5YJFWh6XOP6wdthB2wL9mEXSZpxqZxNmUPshQ5N6LiLp+zwtWltK7mxqJhUbizisLWEeuyLqRolmiOrBTIIoN1uSaC4I5DpQV+DByuXOBtPOa/Gw6ZXpQSlduY5s2CCLZxOPDnE3u7ipzW5YCV8u59v0d4u4wUr7BJA7bBg9APqtRcwBHkc65+ooBCNSm9hpMV1GgKbSp4OVNyBT55MGhrrSwekt/WYZTrquJKNFGcheHBaJxmyeTsgE6ajKdZWCzKcn1rZbUouUMRzq6Sb+GrY7dy5OPRmH43WbHufzwkzTUaWayh0ZEXDg24OYIvJcy5hTtEBYGdaxewaNlw6TQ0RpucVB+wN3T2H8suZKN4GkM6Gs8uh3A1zuBzDEGa/IiDF0CxglYIwSyNp+HkPE3Ja22007kX2aPE0Wpd6YXtME8A0uUTrnhVl3hM+RJ6M+ywi5sh/CVNC3p9OiyepNcdln2fxHDeaRpvD0s6TR9S2ah13m63dtDJv9C7PQir2q1vC0kxkXJ7Ww1I5dkDra5Qk7DGN2m764MNn0MiX2cJBRWFuzpG1gm9oGbM5tI2foA6aFEKaqkl+sGo
*/