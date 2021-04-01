
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
/dGyuax3Q3IwQS4sV+LSC6uXwhOIiUslxsP2ZxfUTqXbcH6NRvkhaMg3aWritJirzf10Ht3o9aRxOYcaWzC0w1b6ddCZopTZeFW8Li4QLx61lFkIygY3wKEZQlwYrk1/6H+VpEwpX1QYJc7RGtYV30ekYDmfDXg5QNTukk8hehmO4dbjhnLmkYzeO6cX3sSevZkdrOUJHJdXOTW7+T+SQfGcfjQiSy66o5JOn33Q6iKUBTDY0uyUT+35c/xJlD1OIExn2DfDlUERVfoo+LGCRt1UZtmbgCTgv9VZ+yGCnB5TIoTAjyupy8k/f68A47duLzAYsfbYbgkxC6Xf4HGqSFd4ckW+5F7eY3bz7hfH5BryDN8sgSmY50mVAyI616egt8iyChvvUfz3QEil8JQtiJdgVCTsQ5mIlRGwutBGW19w5Ze6sgeP5CCXwR/I2KhXMf/+tt3efN+lnSPzNnBdxcc7gMWsgJ0AFSUQ0o9b6XYUwfXZ8RfSk+Cbs6ZDrrkEifKOa4TbsWlG16WktiwR5tYPnsbEekzMhtsAzFUB5ZEF/r8O18hkIzwUfQ==
*/